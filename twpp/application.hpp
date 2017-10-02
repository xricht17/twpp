/*

The MIT License (MIT)

Copyright (c) 2015-2017 Martin Richter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef TWPP_DETAIL_FILE_APPLICATION_HPP
#define TWPP_DETAIL_FILE_APPLICATION_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

struct ManagerData {

    ManagerData(const Identity& appId) noexcept :
        m_appId(appId){}

    Identity m_appId;
    DsmState m_state = DsmState::PreSession;
    Detail::DsmLib m_lib;
    Detail::DsmEntry m_entry = nullptr;

#if defined(TWPP_DETAIL_OS_WIN)
    Handle m_rootWindow;
    bool m_ownRootWindow;
#elif defined(TWPP_DETAIL_OS_MAC)
    Detail::NSAutoreleasePool m_autoreleasePool;
#elif !defined(TWPP_DETAIL_OS_LINUX)
#   error "ManagerData for your platform here"
#endif

};

struct SourceData {

    SourceData(ManagerData* mgr, const Identity& srcIdent) noexcept :
        m_mgr(mgr), m_srcId(srcIdent){}

    ManagerData* m_mgr;
    std::function<void()> m_devEvent;
    Handle m_uiHandle;
    Identity m_srcId;
    DsState m_state = DsState::Closed;
    Msg m_readyMsg = Msg::Null;

#if defined(TWPP_DETAIL_OS_LINUX)
    std::mutex m_cbMutex;
    std::condition_variable m_cbCond;
#elif !defined(TWPP_DETAIL_OS_WIN) && !defined(TWPP_DETAIL_OS_MAC)
#   error "SourceData for your platform here"
#endif

};

}

class Manager;

/// A single TWAIN source.
/// Source must belong to a manager in order to perform operations on it.
/// Any valid source instance must be destroyed or at least cleaned by `cleanup`
/// before parent manager is itself destroyed.
///
/// `call` vs <name-method>
/// They are ultimately the same:
/// `call` is more suitable for cases that need fixed number of arguments.
/// <name-method> is better for user-defined calls.
class Source {

    friend class Manager;

public:
    typedef std::function<void()> EventCallBack;

    /// Creates an invalid source.
    /// Calling any method on such source results in
    /// undefined behaviour, and possibly segfault.
    /// Only isValid() and operator bool() may be called.
    Source() noexcept{}

    ~Source(){
        if (isValid()){
            cleanup();
        }
    }

    Source(Source&&) = default;
    Source& operator=(Source&& o) noexcept{
        if (&o != this){
            if (isValid()){
                cleanup();
            }

            m_data = std::move(o.m_data);
        }

        return *this;
    }

    /// Performs explicit cleanup.
    /// Ultimately closes the source.
    void cleanup() noexcept{
        assert(isValid());

        PendingXfers xfers;

        switch (d()->m_state){
            case DsState::Xferring:
                pendingXfers(Msg::EndXfer, xfers);
                // fallthrough
            case DsState::XferReady:
                if (d()->m_state == DsState::XferReady){ // EndXfer might have moved to DsState::Enabled
                    pendingXfers(Msg::Reset, xfers);
                }

                // fallthrough
            case DsState::Enabled:
                disable();
                // fallthrough
            case DsState::Open:
                close();
                // reset the ref even if close() fails somehow
                Static<void>::g_openSource = nullptr;
                // fallthrough
            case DsState::Closed:
                break;
        }
    }

    /// TWAIN state of the source.
    DsState state() const noexcept{
        assert(isValid());

        return d()->m_state;
    }

    /// Whether the source is valid.
    /// Valid source was created by manager.
    /// Invalid source was created using default constructor.
    bool isValid() const noexcept{
        return static_cast<bool>(m_data);
    }

    operator bool() const noexcept{
        return isValid();
    }

    /// Identity of the source.
    const Identity& identity() const noexcept{
        assert(isValid());

        return d()->m_srcId;
    }

    /// Sets function (object) to receive device event notifications.
    ///
    /// {In state 5 (enabled), the function should only set a flag and return immediately.
    /// `waitReady()` then returns CheckStatus, and the device event may be processed in
    /// the main thread. Call `waitReady()` again once you are done.}
    void setEventCallBack(EventCallBack devEvent){
        assert(isValid());

        d()->m_devEvent = std::move(devEvent);
    }


    // Control ->

    /// Opens the source.
    /// Only up to 1 source may be opened at the same time.
    /// \throw std::bad_alloc
    ReturnCode open(){
        assert(Static<void>::g_openSource == nullptr);

        auto rc = dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::OpenDs, d()->m_srcId);
        if (success(rc)){
            d()->m_state = DsState::Open;

            // TWAIN manual is rather confusing on this topic.
            // Their example sends the registration to DSM, operation tripet documentation mentions DS as destination.
            // Looking at some other applications, Windows seems to send this to DS, MacOS to DSM.
            Detail::CallBack cb1(callBack<void>, static_cast<Detail::CallBackConstant>(0), Msg::Null);

#if defined(TWPP_DETAIL_OS_WIN) || defined(TWPP_DETAIL_OS_LINUX)
            Detail::CallBack2 cb2(callBack<void>, 0, Msg::Null);

            bool usesCb = success(dsm(DataGroup::Control, Dat::Callback2, Msg::RegisterCallback, cb2)) ||
                    success(dsm(DataGroup::Control, Dat::Callback, Msg::RegisterCallback, cb1));
#elif defined(TWPP_DETAIL_OS_MAC)
            bool usesCb = success(dsm(nullptr, DataGroup::Control, Dat::Callback, Msg::RegisterCallback, cb1));
#else
#   error "callback setup for your platform here"
#endif

#if defined(TWPP_DETAIL_OS_WIN)
            Detail::unused(usesCb);
#elif defined(TWPP_DETAIL_OS_MAC) || defined(TWPP_DETAIL_OS_LINUX)
            if (!usesCb){
                close();
                return ReturnCode::Failure;
            }
#else
#   error "source open setup for your platform here"
#endif
            Static<void>::g_openSource = d();
        }

        return rc;
    }

    /// Closes the source.
    ReturnCode close(){
        ReturnCode rc = dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::CloseDs, d()->m_srcId);
        if (success(rc)){
            Static<void>::g_openSource = nullptr;
            d()->m_state = DsState::Closed;
        }

        return rc;
    }

    /// Enables the source, showing its GUI if requested.
    /// A call to `waitReady` must follow, advanced users may look at `processEvent` on Windows.
    /// \param ui GUI settings.
    /// \param uiOnly Whether the GUI should only be used to change values, not scan.
    ReturnCode enable(const UserInterface& ui, bool uiOnly = false) noexcept{
        auto uiTmp = ui; // allow ui to be const, dsm doesnt take const
        ReturnCode rc = dsm(DataGroup::Control, Dat::UserInterface, uiOnly ? Msg::EnableDsUiOnly : Msg::EnableDs, uiTmp);
        if (success(rc) || (!uiOnly && rc == ReturnCode::CheckStatus)){
            d()->m_readyMsg = Msg::Null;
            d()->m_uiHandle = ui.parent();
            d()->m_state = DsState::Enabled;
        }

        return rc;
    }

    /// Disables this source.
    ReturnCode disable(){
        assert(isValid());

        UserInterface ui(false, false, d()->m_uiHandle);
        auto rc = dsm(DataGroup::Control, Dat::UserInterface, Msg::DisableDs, ui);
        if (success(rc)){
            d()->m_state = DsState::Open;
        }

        return rc;
    }

    /// Waits on source GUI, blocking.
    /// This method is meant for CMD applications, see `processEvent()` for GUI-friendly version.
    /// The state is moved to XferReady, when Success is returned, and the source is enabled with full UI (uiOnly = false).
    /// On Windows and Mac OS, call this method from the main thread, GUI events are processed here.
    /// On Linux, this method may be called from any thread, GUI events are NOT processed.
    /// Call this again after processing device event.
    /// \return {Failure on error, Cancel on CANCEL button, Success on SAVE or SCAN button,
    ///          CheckStatus on device event.}
    ReturnCode waitReady(){
        assert(isValid());

        if (d()->m_state != DsState::Enabled){
            return ReturnCode::Failure;
        }

#if defined(TWPP_DETAIL_OS_WIN)
        MSG msg;
        memset(&msg, 0, sizeof(msg));

        Event event(&msg, Msg::Null);
        while (d()->m_readyMsg == Msg::Null){
            auto val = GetMessage(&msg, nullptr, 0, 0);
            if (val == 0 || val == -1){ // 0 ... WM_QUIT; -1 ... error; otherwise ... success
                return ReturnCode::Failure;
            }

            auto rc = dsm(DataGroup::Control, Dat::Event, Msg::ProcessEvent, event);
            switch (rc){
                case ReturnCode::NotDsEvent:
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    // fallthrough
                case ReturnCode::DsEvent:
                    if (d()->m_readyMsg == Msg::Null){
                        d()->m_readyMsg = event.message();
                    }

                    break;

                default:
                    return rc;
            }
        }
#elif defined(TWPP_DETAIL_OS_MAC)
        Detail::NSAutoreleasePool pool;

        while(d()->m_readyMsg == Msg::Null) {
            Detail::NSLoop::processEvent();
        }

        pool.release();

#elif defined(TWPP_DETAIL_OS_LINUX)
        std::unique_lock<std::mutex> lock(d()->m_cbMutex);
        while (d()->m_readyMsg == Msg::Null){
            d()->m_cbCond.wait(lock);
        }
#else
#   error "waitReady for your platform here"
#endif

        switch (d()->m_readyMsg){
            case Msg::XferReady: // ok/scan button <=> Msg::EnableDs
                d()->m_state = DsState::XferReady;
            case Msg::CloseDsOk: // ok/scan button <=> Msg::EnableDsUiOnly
                return ReturnCode::Success;

            case Msg::CloseDsReq: // cancel button
                return ReturnCode::Cancel;

            case Msg::DeviceEvent:
                d()->m_readyMsg = Msg::Null;
                return ReturnCode::CheckStatus;

            default:
                return ReturnCode::Failure;
        }
    }

    /// Processes a single GUI event without blocking.
    /// Can be used instead of `waitReady()` to process a single event.
    /// Windows users must pass events from GUI loop to this method to be sent to DS.
    /// \return {Failure on error, Cancel on CANCEL button, Success on SAVE or SCAN button,
    ///          CheckStatus on device event. NotDsEvent OR DsEvent when not ready yet.}
#if defined (TWPP_DETAIL_OS_WIN)
    ReturnCode processEvent(MSG* event){
        Event twEvent(event, Msg::Null);
        auto rc = dsm(DataGroup::Control, Dat::Event, Msg::ProcessEvent, twEvent);
        switch (rc){
            case ReturnCode::DsEvent:
            case ReturnCode::NotDsEvent:
                if (d()->m_readyMsg == Msg::Null){
                    d()->m_readyMsg = twEvent.message();
                }

                break;

            default:
                return rc;
        }

        auto msg = d()->m_readyMsg;

#elif defined(TWPP_DETAIL_OS_LINUX) || defined(TWPP_DETAIL_OS_MAC)
    ReturnCode processEvent(){
        assert(isValid());
        auto rc = ReturnCode::NotDsEvent;

#   if defined(TWPP_DETAIL_OS_MAC)
        auto msg = d()->m_readyMsg;
#   else
        std::unique_lock<std::mutex> lock(d()->m_cbMutex);
        auto msg = d()->m_readyMsg;
        lock.unlock();
#   endif

#else
#   error "processEvent for your platform here"
#endif
        switch (msg){
            case Msg::XferReady: // ok/scan button <=> Msg::EnableDs
                d()->m_state = DsState::XferReady;
                // fallthrough
            case Msg::CloseDsOk: // ok/scan button <=> Msg::EnableDsUiOnly
                return ReturnCode::Success;

            case Msg::CloseDsReq: // cancel button
                return ReturnCode::Cancel;

            case Msg::DeviceEvent:
                d()->m_readyMsg = Msg::Null;
                return ReturnCode::CheckStatus;

            case Msg::Null:
                return rc;

            default:
                return ReturnCode::Failure;
        }
    }

    /// Sends custom, user-defined data to the source.
    /// This operation is unsafe, there is no way to discover
    /// possible connection state changes.
    /// \tparam T Data type.
    /// \param dg Data group.
    /// \param dat Custom data type identifier. Dat::CustomBase and greater.
    /// \param msg Message, action to perform.
    /// \param data Custom data.
    template<typename T>
    ReturnCode customBase(DataGroup dg, Dat dat, Msg msg, T& data){
        return dsm(dg, dat, msg, data);
    }

    /// Sends custom, user-defined data to the source.
    /// This operation is unsafe, there is no way to discover
    /// possible connection state changes.
    /// \param dg Data group.
    /// \param dat Custom data type identifier. Dat::CustomBase and greater.
    /// \param msg Message, action to perform.
    /// \param data Custom data.
    ReturnCode customBase(DataGroup dg, Dat dat, Msg msg, void* data){
        return dsmPtr(dg, dat, msg, data);
    }

    ReturnCode capability(Msg msg, Capability& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    /// \throw CapTypeException When input capability type does not match the
    ///                         capability type of this template class.
    /// \throw CapItemTypeException When input capability item type does not match
    ///                             the expected item type of the capability.
    template<CapType cap>
    ReturnCode capability(Msg msg, Cap<cap>& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    ReturnCode customData(Msg msg, CustomData& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    ReturnCode deviceEvent(DeviceEvent& out){
        return call(DataGroup::Control, Msg::Get, out);
    }

    ReturnCode fileSystem(Msg msg, FileSystem& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    ReturnCode passThrough(PassThrough& inOut){
        return call(DataGroup::Control, Msg::PassThrough, inOut);
    }

    ReturnCode pendingXfers(Msg msg, PendingXfers& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    ReturnCode setupFileXfer(Msg msg, SetupFileXfer& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    ReturnCode setupMemXfer(SetupMemXfer& out){
        return call(DataGroup::Control, Msg::Get, out);
    }

    ReturnCode xferGroup(Msg msg, DataGroup& inOut){
        return call(DataGroup::Control, msg, inOut);
    }

    ReturnCode status(Status& out){
        return call(DataGroup::Control, Msg::Get, out);
    }

    ReturnCode statusUtf8(StatusUtf8& inOut){
        return call(DataGroup::Control, Msg::Get, inOut);
    }
    // <- Control


    // Image ->
    // TODO CieColor
    /*
    ReturnCode cieColor(CieColor& out){
        return call(DataGroup::Image, Msg::Get, out);
    }*/

    ReturnCode extImageInfo(ExtImageInfo& inOut){
        return call(DataGroup::Image, Msg::Get, inOut);
    }

    ReturnCode grayResponse(Msg msg, GrayResponse& inOut){
        return call(DataGroup::Image, msg, inOut);
    }

    ReturnCode iccProfile(IccProfileMemory& out){
        return call(DataGroup::Image, Msg::Get, out);
    }

    ReturnCode imageFileXfer(){
        return call(DataGroup::Image, Msg::Get, ImageFileXfer());
    }

    ReturnCode imageInfo(ImageInfo& out){
        return call(DataGroup::Image, Msg::Get, out);
    }

    ReturnCode imageLayout(Msg msg, ImageLayout& inOut){
        return call(DataGroup::Image, msg, inOut);
    }

    ReturnCode imageMemFileXfer(ImageMemFileXfer& inOut){
        return call(DataGroup::Image, Msg::Get, inOut);
    }

    ReturnCode imageMemXfer(ImageMemXfer& inOut){
        return call(DataGroup::Image, Msg::Get, inOut);
    }

    ReturnCode imageNativeXfer(ImageNativeXfer& out){
        return call(DataGroup::Image, Msg::Get, out);
    }

    ReturnCode jpegCompression(Msg msg, JpegCompression& inOut){
        return call(DataGroup::Image, msg, inOut);
    }

    ReturnCode palette8(Msg msg, Palette8& inOut){
        return call(DataGroup::Image, msg, inOut);
    }

    ReturnCode rgbResponse(Msg msg, RgbResponse& inOut){
        return call(DataGroup::Image, msg, inOut);
    }
    // <- Image


    // Audio ->
    ReturnCode audioFileXfer(){
        return call(DataGroup::Audio, Msg::Get, AudioFileXfer());
    }

    ReturnCode audioInfo(AudioInfo& out){
        return call(DataGroup::Audio, Msg::Get, out);
    }

    ReturnCode audioNativeXfer(AudioNativeXfer& out){
        return call(DataGroup::Audio, Msg::Get, out);
    }
    // <- Audio


    // Raw ->

    // dg:: control follows
    ReturnCode call(DataGroup dg, Msg msg, Capability& data){
        return dsm(dg, Dat::Capability, msg, data);
    }

    /// \throw CapTypeException When input capability type does not match the
    ///                         capability type of this template class.
    /// \throw CapItemTypeException When input capability item type does not match
    ///                             the expected item type of the capability.
    template<CapType cap>
    ReturnCode call(DataGroup dg, Msg msg, Cap<cap>& data){
        auto rc = call(dg, msg, data.m_cap);
        data.checkTypes();
        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, CustomData& data){
        return dsm(dg, Dat::CustomData, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, DeviceEvent& data){
        return dsm(dg, Dat::DeviceEvent, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, FileSystem& data){
        return dsm(dg, Dat::FileSystem, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, PassThrough& data){
        return dsm(dg, Dat::PassThrough, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, PendingXfers& data){
        auto rc = dsm(dg, Dat::PendingXfers, msg, data);
        if (success(rc)){
            // FIXME: unsure about audio state transitions
            DataGroup xg = DataGroup::Image;
            switch (msg){
                case Msg::EndXfer:
                    xferGroup(Msg::Get, xg);
                    if (xg == DataGroup::Image && data.count() == 0){
                        d()->m_state = DsState::Enabled;
                    } else {
                        d()->m_state = DsState::XferReady;
                    }

                    break;

                case Msg::Reset:
                    xferGroup(Msg::Get, xg);
                    if (xg == DataGroup::Image){
                        d()->m_state = DsState::Enabled;
                    }

                    break;

                default:
                    break;
            }


        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, SetupFileXfer& data){
        return dsm(dg, Dat::SetupFileXfer, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, SetupMemXfer& data){
        return dsm(dg, Dat::SetupMemXfer, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, DataGroup& data){
        return dsm(dg, Dat::XferGroup, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, Status& data){
        return dsm(dg, Dat::Status, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, StatusUtf8& data){
        return dsm(dg, Dat::StatusUtf8, msg, data);
    }

    // dg::image follows
    // TODO CieColor
    /*
    ReturnCode call(DataGroup dg, Msg msg, CieColor& data){
        return dsm(dg, Dat::CieColor, msg, data);
    }*/

    ReturnCode call(DataGroup dg, Msg msg, ExtImageInfo& data){
        char* raw = *Detail::alias_cast<char**>(&data); // ExtImageInfo is just an envelope; raw ~ ExtImageInfo.m_data
        return dsmPtr(dg, Dat::ExtImageInfo, msg, raw);
    }

    ReturnCode call(DataGroup dg, Msg msg, GrayResponse& data){
        return dsmPtr(dg, Dat::GrayResponse, msg, data.data());
    }

    ReturnCode call(DataGroup dg, Msg msg, IccProfileMemory& data){
        Memory mem; // DS allocates and owns the memory
        ReturnCode rc = dsm(dg, Dat::IccProfile, msg, mem);
        if (success(rc)){
            data = std::move(mem);
        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, const ImageFileXfer&){
        ReturnCode rc = dsmPtr(dg, Dat::ImageFileXfer, msg, nullptr);
        if (success(rc)){
            d()->m_state = DsState::Xferring;
        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, ImageInfo& data){
        return dsm(dg, Dat::ImageInfo, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, ImageLayout& data){
        return dsm(dg, Dat::ImageLayout, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, ImageMemFileXfer& data){
        ReturnCode rc = dsm(dg, Dat::ImageMemFileXfer, msg, data);
        if (success(rc) || rc == ReturnCode::XferDone){
            d()->m_state = DsState::Xferring;
        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, ImageMemXfer& data){
        ReturnCode rc = dsm(dg, Dat::ImageMemXfer, msg, data);
        if (success(rc) || rc == ReturnCode::XferDone){
            d()->m_state = DsState::Xferring;
        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, ImageNativeXfer& data){
        Handle h;
        ReturnCode rc = dsm(dg, Dat::ImageNativeXfer, msg, h);
        if (rc == ReturnCode::XferDone){
            d()->m_state = DsState::Xferring;
        }

        if (h){
            data = ImageNativeXfer(h);
        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, JpegCompression& data){
        return dsm(dg, Dat::JpegCompression, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, Palette8& data){
        return dsm(dg, Dat::Palette8, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, RgbResponse& data){
        return dsmPtr(dg, Dat::RgbResponse, msg, data.data());
    }

    // dg::audio follows
    ReturnCode call(DataGroup dg, Msg msg, const AudioFileXfer&){
        // FIXME: unsure about state transitions
        ReturnCode rc = dsmPtr(dg, Dat::AudioFileXfer, msg, nullptr);
        if (rc == ReturnCode::XferDone){
            d()->m_state = DsState::Xferring;
        }

        return rc;
    }

    ReturnCode call(DataGroup dg, Msg msg, AudioInfo& data){
        return dsm(dg, Dat::AudioInfo, msg, data);
    }

    ReturnCode call(DataGroup dg, Msg msg, AudioNativeXfer& data){
        Handle h;
        ReturnCode rc = dsm(dg, Dat::AudioNativeXfer, msg, h);
        if (success(rc)){
            d()->m_state = DsState::Xferring;
        }

        if (h){
            data = AudioNativeXfer(h);
        }

        return rc;
    }
    // <- Raw

private:
    Source(Detail::ManagerData* mgr, const Identity& srcId) :
        m_data(new Detail::SourceData(mgr, srcId)){}

    Detail::SourceData* d() noexcept{
        return m_data.get();
    }

    const Detail::SourceData* d() const noexcept{
        return m_data.get();
    }

    template<typename T>
    ReturnCode dsm(Identity* dest, DataGroup dg, Dat dat, Msg msg, T& data) noexcept{
        return dsmPtr(dest, dg, dat, msg, &data);
    }

    ReturnCode dsmPtr(Identity* dest, DataGroup dg, Dat dat, Msg msg, void* data) noexcept{
        assert(isValid());

        auto mgr = d()->m_mgr;
        return mgr->m_entry(&mgr->m_appId, dest, dg, dat, msg, data);
    }

    template<typename T>
    ReturnCode dsm(DataGroup dg, Dat dat, Msg msg, T& data) noexcept{
        return dsm(&d()->m_srcId, dg, dat, msg, data);
    }

    ReturnCode dsmPtr(DataGroup dg, Dat dat, Msg msg, void* data) noexcept{
        return dsmPtr(&d()->m_srcId, dg, dat, msg, data);
    }

    // header-only, yet we need static variables
    // templates behave as if defined in at most one source file
    template<typename>
    struct Static {
        static Detail::SourceData* g_openSource;
    };

    template<typename>
    static ReturnCode TWPP_DETAIL_CALLSTYLE callBack(
            Identity*,
            Identity*,
            DataGroup,
            Dat,
            Msg msg,
            void*
    ) noexcept{
        Detail::SourceData* src = Static<void>::g_openSource;
        if (src == nullptr){
            return ReturnCode::Failure;
        }

#if defined(TWPP_DETAIL_OS_LINUX)
        std::unique_lock<std::mutex> lock(src->m_cbMutex);
        if (src->m_state != DsState::Enabled){
            lock.unlock();
        }
#elif !defined(TWPP_DETAIL_OS_WIN) && !defined(TWPP_DETAIL_OS_MAC)
#   error "callBack preparation for your platform here"
#endif
        if (msg == Msg::DeviceEvent){
            if (!src->m_devEvent){
                return ReturnCode::Failure;
            }

            src->m_devEvent();
        }

        if (src->m_state == DsState::Enabled){
            src->m_readyMsg = msg;

#if defined(TWPP_DETAIL_OS_WIN)
            PostMessageA(static_cast<HWND>(src->m_mgr->m_rootWindow.raw()), WM_NULL, 0, 0);
#elif defined(TWPP_DETAIL_OS_LINUX)
            src->m_cbCond.notify_one();
#elif defined(TWPP_DETAIL_OS_MAC)
            Detail::NSLoop::postDummy();
#else
#   error "callBack for your platform here"
#endif
        }


        return ReturnCode::Success;
    }

    std::unique_ptr<Detail::SourceData> m_data;

};

template<typename Dummy>
Detail::SourceData* Source::Static<Dummy>::g_openSource = nullptr;

/// TWAIN data source manager.
/// At most one valid instance may exist at all times.
/// All corresponding valid sources must be destroyed or cleaned up
/// BEFORE their parent valid manager is closed (destroyed/cleaned up).
class Manager {

public:
    /// Creates an invalid manager.
    Manager() noexcept{}

    /// Creates a valid, unloaded manager.
    /// \param appIdentity Application identity.
    explicit Manager(const Identity& appIdentity) :
        m_data(new Detail::ManagerData(appIdentity)){}

    ~Manager(){
        if (isValid()){
            cleanup();
        }
    }

    Manager(Manager&&) = default;
    Manager& operator=(Manager&& o) noexcept{
        if (&o != this){
            if (isValid()){
                cleanup();
            }

            m_data = std::move(o.m_data);
        }

        return *this;
    }

    /// Explicitly cleanes the manager, ultimately closing it.
    void cleanup() noexcept{
        assert(isValid());

        switch (d()->m_state){
            case DsmState::Open:
                close();
                // fallthrough
            case DsmState::Loaded:
                unload();
                // fallthrough
            case DsmState::PreSession:
                // nothing to do now
                break;
        }
    }

    /// Loads the manager library.
    /// Not a TWAIN call.
    /// \param preferOld {Whether to prefer old DSM (TWAIN_32) instead
    ///                   of the new one (TWAINDSM) on 32bit Windows.
    ///                   Has no effect anywhere else.}
    /// \return Whether this call loaded the library.
    bool load(bool preferOld = false) noexcept{
        assert(isValid());

        if (d()->m_state != DsmState::PreSession){
            return false;
        }

        if (!d()->m_lib.load(preferOld)){
            return false;
        }

        d()->m_state = DsmState::Loaded;
        d()->m_entry = d()->m_lib.resolve();
        bool resolved = d()->m_entry != nullptr;
        if (!resolved){
            unload();
        }

        return resolved;
    }

    /// Unloads the manager library.
    /// Not a TWAIN call.
    /// \return Whether this call unloaded the library.
    bool unload() noexcept{
        assert(isValid());

        if (d()->m_state != DsmState::Loaded){
            return false;
        }

        closeRootWindow();
        d()->m_lib.unload();
        d()->m_state = DsmState::PreSession;
        return true;
    }

    /// Opens the manager.
    ReturnCode open(Handle rootWindow = Handle()) noexcept{
        assert(isValid());

        if (d()->m_state != DsmState::Loaded){
            return ReturnCode::Failure;
        }

#if defined(TWPP_DETAIL_OS_WIN)
        if (rootWindow){
            closeRootWindow();
            d()->m_rootWindow = rootWindow;
            d()->m_ownRootWindow = false;
        } else {
            if (!d()->m_rootWindow || !d()->m_ownRootWindow){
                d()->m_rootWindow = Handle(CreateWindowA("STATIC", nullptr, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr));
                if (!d()->m_rootWindow){
                    return ReturnCode::Failure;
                }
            }

            d()->m_ownRootWindow = true;
            rootWindow = d()->m_rootWindow;
        }
#elif !defined(TWPP_DETAIL_OS_MAC) && !defined(TWPP_DETAIL_OS_LINUX)
#   error "manager open setup for your platform here"
#endif

        auto rc = dsm(nullptr, DataGroup::Control, Dat::Parent, Msg::OpenDsm, rootWindow);
        if (success(rc)){
            Detail::resetMemFuncs();
            if (d()->m_appId.isDsmV2()){
                Detail::EntryPoint e;
                if (success(dsm(nullptr, DataGroup::Control, Dat::EntryPoint, Msg::Get, e))){
                    Detail::setMemFuncs(e.m_alloc, e.m_free, e.m_lock, e.m_unlock);
                }
            }

            d()->m_state = DsmState::Open;
        }

        return rc;
    }

    /// Closes the manager.
    ReturnCode close() noexcept{
        assert(isValid());

        // no need to check state, dsm will do it for us

#if defined(TWPP_DETAIL_OS_WIN)
        Handle rootWindow = d()->m_rootWindow;
#elif defined(TWPP_DETAIL_OS_MAC) || defined(TWPP_DETAIL_OS_LINUX)
        Handle rootWindow;
#else
#   error "close manager for your platform here"
#endif

        auto rc = dsm(nullptr, DataGroup::Control, Dat::Parent, Msg::CloseDsm, rootWindow);
        if (success(rc)){
            d()->m_state = DsmState::Loaded;
        }

        return rc;
    }

    /// Creates a valid closed source.
    /// Whether the source may be opened depends whether
    /// a source with the supplied product name and manufacturer exists.
    /// \throw std::bad_alloc
    Source createSource(const Str32& productName, const Str32& manufacturer){
        assert(isValid());

        return Source(d(), Identity(Version(), DataGroup::Control, manufacturer, Str32(), productName));
    }

    /// Creates a valid closed default source.
    /// It is almost certain the source may be opened.
    /// \throw std::bad_alloc
    ReturnCode defaultSource(Source& out){
        Identity id;
        auto rc = dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::GetDefault, id);
        if (success(rc)){
            out = Source(d(), id);
        }

        return rc;
    }

    /// Sets default source.
    ReturnCode setDefaultSource(Source& in) noexcept{
        return dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::Set, in.d()->m_srcId);
    }

    /// Lists all available sources.
    /// \tparam Container Container type, usually std::vector<Source>.
    /// \param out The container to be filled with sources.
    /// \return {RC::Success if one source, RC::EndOfList if more sources, RC::Failure if error.}
    template<typename Container>
    ReturnCode sources(Container& out){
        Identity id;
        auto rc = dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::GetFirst, id);
        if (success(rc)){
            do {
                out.push_back(Source(d(), id));

                rc = dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::GetNext, id);
            } while(success(rc));
        }

        return rc;
    }

    /// Shows a source-selection dialog.
    /// Available only on Windows and MacOS.
    ReturnCode showSourceDialog(Source& out){
        Identity id;
        ReturnCode rc = dsm(nullptr, DataGroup::Control, Dat::Identity, Msg::UserSelect, id);
        if (success(rc)){
            out = Source(d(), id);
        }

        return rc;
    }

    /// Obtains the last manager status.
    ReturnCode status(Status& status) noexcept{
        return dsm(nullptr, DataGroup::Control, Dat::Status, Msg::Get, status);
    }

    /// The current manager TWAIN state.
    DsmState state() const noexcept{
        assert(isValid());

        return d()->m_state;
    }

    /// Application identity the manager was/will be open with.
    const Identity& identity() const noexcept{
        assert(isValid());

        return d()->m_appId;
    }

    /// Whether this object is a valid manager.
    /// Valid manager object is created using constructor with at least one parameter.
    /// Using constructor without any parameters results in invalid manager.
    bool isValid() const noexcept{
        return static_cast<bool>(m_data);
    }

    operator bool() noexcept{
        return isValid();
    }

private:
    void closeRootWindow() noexcept{
#if defined(TWPP_DETAIL_OS_WIN)
        if (d()->m_rootWindow && d()->m_ownRootWindow){
            DestroyWindow(static_cast<HWND>(d()->m_rootWindow.raw()));
            d()->m_ownRootWindow = Handle();
        }
#elif !defined(TWPP_DETAIL_OS_MAC) && !defined(TWPP_DETAIL_OS_LINUX)
#   error "closeRootWindow for your platform here"
#endif
    }

    Detail::ManagerData* d() noexcept{
        return m_data.get();
    }

    const Detail::ManagerData* d() const noexcept{
        return m_data.get();
    }

    template<typename T>
    ReturnCode dsm(Identity* dest, DataGroup dg, Dat dat, Msg msg, T& data){
        return dsmPtr(dest, dg, dat, msg, &data);
    }

    ReturnCode dsmPtr(Identity* dest, DataGroup dg, Dat dat, Msg msg, void* data){
        assert(isValid());

        return d()->m_entry(&d()->m_appId, dest, dg, dat, msg, data);
    }

    std::unique_ptr<Detail::ManagerData> m_data;

};

}

#endif // TWPP_DETAIL_FILE_APPLICATION_HPP

