/*

The MIT License (MIT)

Copyright (c) 2015 Martin Richter

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

#ifndef TWPP_DETAIL_FILE_DATASOURCE_HPP
#define TWPP_DETAIL_FILE_DATASOURCE_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

template<typename Derived, bool enabled> // false
struct StaticCustomBaseProc {
    ReturnCode operator()(Dat, Msg, void*, Status& stat){
        stat = ConditionCode::BadProtocol;
        return ReturnCode::Failure;
    }
};

template<typename Derived>
struct StaticCustomBaseProc<Derived, true> {
    ReturnCode operator()(Dat dat, Msg msg, void* data, Status& stat){
        return Derived::staticCustomBase(dat, msg, data, stat);
    }
};

}

#define TWPP_ENTRY(SourceClass)\
    extern "C" TWPP_DETAIL_EXPORT ReturnCode TWPP_DETAIL_CALLSTYLE \
    DS_Entry(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data){\
        return SourceClass::entry(origin, dg, dat, msg, data);\
    }

namespace SourceFromThisProcs {

/// Returns data source identity not associated with any instance.
const Identity& defaultIdentity();

/// Processes custom TWAIN operations without having any opened connection.
/// DataGroup is always Control.
/// \param dat Type of data. Dat::CustomBase + X.
/// \param msg Message, action to perform.
/// \param data The data, may be null.
/// \param stat Output, operation status code.
/// \return Operation result code.
ReturnCode staticCustomBase(Dat dat, Msg msg, void* data, Status& stat);

}

/// Base class of a TWAIN data source.
/// It handles instances creation and all static calls.
///
/// The derived class must:
///  1) Implement at least all pure virtual methods.
///  2) Provide `static const Identity& defaultIdentity()`.
///  3) If hasStaticCustomBaseProc == true, provide
///     `static ReturnCode staticCustomBase(Dat dat, Msg msg, void* data, Status& stat)`.
///
/// After defining your source class, do not forget to use macro
/// TWPP_ENTRY(<name-of-your-class>)
/// where the name is a literal, not string:
///
/// TWPP_ENTRY(Source)  // <- no semicolon required
/// \tparam Derived The class inheriting from this.
/// \tparam hasStaticCustomBaseProc {Whether the Derived
///     class handles static custom base operations, see above.}
template<typename Derived, bool hasStaticCustomBaseProc = false>
class SourceFromThis {

public:
    SourceFromThis(const SourceFromThis&) = delete;
    SourceFromThis& operator=(const SourceFromThis&) = delete;

    SourceFromThis(SourceFromThis&&) = delete;
    SourceFromThis& operator=(SourceFromThis&&) = delete;

protected:
    /// Creates closed instance.
    constexpr SourceFromThis() noexcept :
        m_lastStatus(ConditionCode::Bummer), m_state(DsState::Closed){}

    /// The last TWAIN status.
    Status lastStatus() const noexcept{
        return m_lastStatus;
    }

    /// Current TWAIN state.
    DsState state() const noexcept{
        return m_state;
    }

    /// Whether the source is in the supplied TWAIN state.
    bool inState(DsState state) const noexcept{
        return m_state == state;
    }

    /// Whether the source is between min and max states (both inclusive).
    bool inState(DsState min, DsState max) const noexcept{
        return m_state >= min && m_state <= max;
    }

    /// Whether there exists an enabled source.
    static bool hasEnabled() noexcept{
        for (auto& src : g_sources){
            if (src.inState(DsState::Enabled, DsState::Xferring)){
                return true;
            }
        }

        return false;
    }

    /// Source identity.
    const Identity& sourceIdentity() const noexcept{
        return m_srcId;
    }

    /// Identity of the application that opened the source.
    const Identity& applicationIdentity() const noexcept{
        return m_appId;
    }

    /// Sets current TWAIN state, use with care.
    void setState(DsState state) noexcept{
        m_state = state;
    }

    /// Sets current source identity, use with care.
    void setSourceIdentity(const Identity& sourceIdentity) noexcept{
        m_srcId = sourceIdentity;
    }

    /// Sets current application identity, use with care.
    void setApplicationIdentity(const Identity& appIdentity) noexcept{
        m_appId = appIdentity;
    }

    /// Sets the result of the last operation.
    /// This method (or shortcuts) must be used when returning from a TWAIN method to properly track statuses.
    ReturnCode setStatus(Status status, ReturnCode rc = ReturnCode::Failure) noexcept{
        m_lastStatus = status;
        return rc;
    }

    /// Shortcut for status(CC::Success, RC::Success).
    ReturnCode success() noexcept{
        return setStatus(ConditionCode::Success, ReturnCode::Success);
    }

    /// Shortcut for status(CC::BadValue, RC::Failure).
    ReturnCode badValue() noexcept{
        return setStatus(ConditionCode::BadValue);
    }

    /// Shortcut for status(CC::BadProtocol, RC::Failure).
    ReturnCode badProtocol() noexcept{
        return setStatus(ConditionCode::BadProtocol);
    }

    /// Shortcut for status(CC::SeqError, RC::Failure).
    ReturnCode seqError() noexcept{
        return setStatus(ConditionCode::SeqError);
    }

    /// Shortcut for status(CC::CapBadOperation, RC::Failure).
    ReturnCode capBadOperation() noexcept{
        return setStatus(ConditionCode::CapBadOperation);
    }

    /// Shortcut for status(CC::CapUnsupported, RC::Failure).
    ReturnCode capUnsupported() noexcept{
        return setStatus(ConditionCode::CapUnsupported);
    }


    /// Notifies application about clicking on OK button.
    ReturnCode notifyCloseOk() noexcept{
        return notifyApp(Msg::CloseDsOk);
    }

    /// Notifies application about clicking on Cancel button.
    ReturnCode notifyCloseCancel() noexcept{
        return notifyApp(Msg::CloseDsReq);
    }

    /// Notifies application about a device event.
    ReturnCode notifyDeviceEvent() noexcept{
        return notifyApp(Msg::DeviceEvent);
    }

    /// Notifies application about ready transfer (after clicking scan button is GUI is shown).
    ReturnCode notifyXferReady() noexcept{
        return notifyApp(Msg::XferReady);
    }



    /// Root of source TWAIN calls.
    /// \param origin Identity of the caller.
    /// \param dg Data group of the call.
    /// \param dat Type of data.
    /// \param msg Message, action to perform.
    /// \param data The data, may be null.
    virtual ReturnCode call(const Identity& origin, DataGroup dg, Dat dat, Msg msg, void* data){
        switch (dg){
            case DataGroup::Control:
                return control(origin, dat, msg, data);

            case DataGroup::Image:
                return image(origin, dat, msg, data);

            case DataGroup::Audio:
                return audio(origin, dat, msg, data);

            default:
                return badProtocol();

        }
    }

    /// Root of source control TWAIN calls.
    /// \param origin Identity of the caller.
    /// \param dat Type of data.
    /// \param msg Message, action to perform.
    /// \param data The data, may be null.
    virtual ReturnCode control(const Identity& origin, Dat dat, Msg msg, void* data){
        if (!data){
            // all control triplets require data
            return badValue();
        }

        switch (dat){
            case Dat::Capability:
                return capability(origin, msg, *static_cast<Capability*>(data));
            case Dat::CustomData:
                return customData(origin, msg, *static_cast<CustomData*>(data));
            case Dat::DeviceEvent:
                return deviceEvent(origin, msg, *static_cast<DeviceEvent*>(data));
            case Dat::Event: // Windows only
                return event(origin, msg, *static_cast<Event*>(data));
            case Dat::FileSystem:
                return fileSystem(origin, msg, *static_cast<FileSystem*>(data));
            case Dat::Identity:
                return identity(origin, msg, *static_cast<Identity*>(data));
            case Dat::PassThrough:
                return passThrough(origin, msg, *static_cast<PassThrough*>(data));
            case Dat::PendingXfers:
                return pendingXfers(origin, msg, *static_cast<PendingXfers*>(data));
            case Dat::SetupFileXfer:
                return setupFileXfer(origin, msg, *static_cast<SetupFileXfer*>(data));
            case Dat::SetupMemXfer:
                return setupMemXfer(origin, msg, *static_cast<SetupMemXfer*>(data));
            case Dat::Status:
                return status(origin, msg, *static_cast<Status*>(data));
            case Dat::StatusUtf8:
                return statusUtf8(origin, msg, *static_cast<StatusUtf8*>(data));
            case Dat::UserInterface:
                return userInterface(origin, msg, *static_cast<UserInterface*>(data));
            case Dat::XferGroup: {
                return xferGroup(origin, msg, *static_cast<DataGroup*>(data));
            }
            default:
                return badProtocol();
        }
    }

        /// Capability TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Capability data.
        virtual ReturnCode capability(const Identity& origin, Msg msg, Capability& data) = 0;

        /// Custom data TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Custom data.
        virtual ReturnCode customData(const Identity& origin, Msg msg, CustomData& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Device event TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Device event data.
        virtual ReturnCode deviceEvent(const Identity& origin, Msg msg, DeviceEvent& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }


#if defined(TWPP_DETAIL_OS_WIN)
        /// Event TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Event data.
        virtual ReturnCode event(const Identity& origin, Msg msg, Event& data) = 0;
#else
        /// Event TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Event data.
        virtual ReturnCode event(const Identity& origin, Msg msg, Event& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }
#endif

        /// Identity TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Identity data.
        virtual ReturnCode identity(const Identity& origin, Msg msg, Identity& data){
            ReturnCode rc;
            switch (msg){
                case Msg::Get:
                    // any state
                    data = sourceIdentity();
                    return success();

                case Msg::OpenDs: {
                    if (!inState(DsState::Closed)){
                        return seqError();
                    }

                    setSourceIdentity(data);
                    setApplicationIdentity(origin);
                    rc = identityOpenDs(origin);
                    if (Twpp::success(rc)){
                        setState(DsState::Open);
                    }

                    return rc;
                }

                case Msg::CloseDs: {
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    rc = identityCloseDs(origin);
                    if (Twpp::success(rc)){
                        setState(DsState::Closed);
                    }

                    return rc;
                }

                default:
                    return badProtocol();
            }
        }

            /// Open source identity TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual ReturnCode identityOpenDs(const Identity& origin) = 0;

            /// Close source identity TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual ReturnCode identityCloseDs(const Identity& origin) = 0;

        /// File system TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data File system data.
        virtual ReturnCode fileSystem(const Identity& origin, Msg msg, FileSystem& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Pass through TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Pass through data.
        virtual ReturnCode passThrough(const Identity& origin, Msg msg, PassThrough& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Pending xfers TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Pending xfers data.
        virtual ReturnCode pendingXfers(const Identity& origin, Msg msg, PendingXfers& data){
            switch (msg){
                case Msg::EndXfer: {
                    if (!inState(DsState::XferReady, DsState::Xferring)){
                        return seqError();
                    }

                    auto rc = pendingXfersEnd(origin, data);
                    if (Twpp::success(rc)){
                        DataGroup xferGroup = DataGroup::Image;
                        if (!Twpp::success(this->xferGroup(origin, Msg::Get, xferGroup))){
                            xferGroup = DataGroup::Image;
                        }

                        if (xferGroup == DataGroup::Audio){
                            setState(DsState::XferReady);
                        } else {
                            setState(data.count() ? DsState::XferReady : DsState::Enabled);
                        }
                    }

                    return rc;
                }


                case Msg::Reset: {
                    if (!inState(DsState::XferReady)){
                        return seqError();
                    }

                    auto rc = pendingXfersReset(origin, data);
                    if (Twpp::success(rc)){
                        DataGroup xferGroup = DataGroup::Image;
                        if (!Twpp::success(this->xferGroup(origin, Msg::Get, xferGroup))){
                            xferGroup = DataGroup::Image;
                        }

                        if (xferGroup != DataGroup::Audio){
                            setState(DsState::Enabled);
                        }
                    }

                    return rc;
                }

                case Msg::StopFeeder:
                    if (!inState(DsState::XferReady)){
                        return seqError();
                    }

                    return pendingXfersStopFeeder(origin, data);

                case Msg::Get:
                    if (!inState(DsState::Open, DsState::Xferring)){
                        return seqError();
                    }

                    return pendingXfersGet(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get pending xfers TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual ReturnCode pendingXfersGet(const Identity& origin, PendingXfers& data) = 0;

            /// End xfer pending xfers TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual ReturnCode pendingXfersEnd(const Identity& origin, PendingXfers& data) = 0;

            /// Reset xfers pending xfers TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual ReturnCode pendingXfersReset(const Identity& origin, PendingXfers& data) = 0;

            /// Stop feeder pending xfers TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual ReturnCode pendingXfersStopFeeder(const Identity& origin, PendingXfers& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Setup file xfer TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Setup file xfer data.
        virtual ReturnCode setupFileXfer(const Identity& origin, Msg msg, SetupFileXfer& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Setup memory xfer TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Setup memory xfer data.
        virtual ReturnCode setupMemXfer(const Identity& origin, Msg msg, SetupMemXfer& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Status TWAIN call.
        /// Default implementation returns last status.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Status data.
        virtual ReturnCode status(const Identity& origin, Msg msg, Status& data){
            Detail::unused(origin);
            if (msg == Msg::Get){
                data = lastStatus();
                return success();
            } else {
                return badProtocol();
            }
        }

        /// Status utf8 TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Status utf8 data.
        virtual ReturnCode statusUtf8(const Identity& origin, Msg msg, StatusUtf8& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// User interface TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data User interface data.
        virtual ReturnCode userInterface(const Identity& origin, Msg msg, UserInterface& data){
            ReturnCode rc;
            switch (msg){
                case Msg::DisableDs:
                    if (!inState(DsState::Enabled)){
                        return seqError();
                    }

                    rc = userInterfaceDisable(origin, data);
                    if (Twpp::success(rc)){
                        setState(DsState::Open);
                    }

                    return rc;

                case Msg::EnableDs:
                    if (!inState(DsState::Open) || hasEnabled()){ // only a single source can be enabled at any given time
                        return seqError();
                    }

                    rc = userInterfaceEnable(origin, data);
                    if (Twpp::success(rc) || rc == ReturnCode::CheckStatus){
                        setState(DsState::Enabled);
                    }

                    return rc;

                case Msg::EnableDsUiOnly:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    rc = userInterfaceDisable(origin, data);
                    if (Twpp::success(rc)){
                        setState(DsState::Enabled);
                    }

                    return rc;

                default:
                    return badProtocol();
            }
        }

            /// Disable user interface TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data User interface data.
            virtual ReturnCode userInterfaceDisable(const Identity& origin, UserInterface& data) = 0;

            /// Enable user interface TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data User interface data.
            virtual ReturnCode userInterfaceEnable(const Identity& origin, UserInterface& data) = 0;

            /// Enable UI only user interface TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data User interface data.
            virtual ReturnCode userInterfaceEnableUiOnly(const Identity& origin, UserInterface& data) = 0;

        /// Xfer group TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Xfer group data.
        virtual ReturnCode xferGroup(const Identity& origin, Msg msg, DataGroup& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

    /// Root of source image TWAIN calls.
    ///
    /// Special data to type casts:
    ///     ExtImageInfo: reinterpret_cast<ExtImageInfo&>(data)
    ///     GrayResponse: reinterpret_cast<GrayResponse&>(data)
    ///     RgbResponse: reinterpret_cast<RgbResponse&>(data)
    ///
    /// \param origin Identity of the caller.
    /// \param dat Type of data.
    /// \param msg Message, action to perform.
    /// \param data The data, may be null.
    virtual ReturnCode image(const Identity& origin, Dat dat, Msg msg, void* data){
        if (dat != Dat::ImageFileXfer && !data){
            return badValue();
        }

        switch (dat){
            // TODO CieColor
            /*case Dat::CieColor:
                return cieColor(origin, msg, *static_cast<CieColor*>(data));*/
            case Dat::ExtImageInfo:
                return extImageInfo(origin, msg, reinterpret_cast<ExtImageInfo&>(data)); // ExtImageInfo is simply a `pointer to TW_EXTIMAGEINFO`
            case Dat::GrayResponse:
                return grayResponse(origin, msg, reinterpret_cast<GrayResponse&>(data)); // GrayResponse is simply a `pointer to TW_GRAYRESPONSE`
            case Dat::IccProfile:
                return iccProfile(origin, msg, *static_cast<Memory*>(data));
            case Dat::ImageFileXfer:
                return imageFileXfer(origin, msg);
            case Dat::ImageInfo:
                return imageInfo(origin, msg, *static_cast<ImageInfo*>(data));
            case Dat::ImageLayout:
                return imageLayout(origin, msg, *static_cast<ImageLayout*>(data));
            case Dat::ImageMemFileXfer:
                return imageMemFileXfer(origin, msg, *static_cast<ImageMemFileXfer*>(data));
            case Dat::ImageMemXfer:
                return imageMemXfer(origin, msg, *static_cast<ImageMemXfer*>(data));
            case Dat::ImageNativeXfer:
                return imageNativeXfer(origin, msg, *static_cast<ImageNativeXfer*>(data));
            case Dat::JpegCompression:
                return jpegCompression(origin, msg, *static_cast<JpegCompression*>(data));
            case Dat::Palette8:
                return palette8(origin, msg, *static_cast<Palette8*>(data));
            case Dat::RgbResponse:
                return rgbResponse(origin, msg, reinterpret_cast<RgbResponse&>(data)); // RgbResponse is simply a `pointer to TW_RGBRESPONSE`
            default:
                return badProtocol();
        }
    }

        // TODO CieColor
    /*
        /// Cie color TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Cie color data.
        virtual ReturnCode cieColor(const Identity& origin, Msg msg, CieColor& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }*/

        /// Ext image info TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Ext image info data.
        virtual ReturnCode extImageInfo(const Identity& origin, Msg msg, ExtImageInfo& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Gray response TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Gray response data.
        virtual ReturnCode grayResponse(const Identity& origin, Msg msg, GrayResponse& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// ICC profile TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data ICC profile data.
        virtual ReturnCode iccProfile(const Identity& origin, Msg msg, Memory& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Image file xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        virtual ReturnCode imageFileXfer(const Identity& origin, Msg msg){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady)){
                return seqError();
            }

            auto rc = imageFileXferGet(origin);
            if (rc == ReturnCode::XferDone){
                setState(DsState::Xferring);
            }

            return rc;
        }

            /// Get image file xfer TWAIN call.
            /// Default implementation does nothing.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual ReturnCode imageFileXferGet(const Identity& origin){
                Detail::unused(origin);
                return badProtocol();
            }

        /// Image info TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image info data.
        virtual ReturnCode imageInfo(const Identity& origin, Msg msg, ImageInfo& data) = 0;

        /// Image layout TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image layout data.
        virtual ReturnCode imageLayout(const Identity& origin, Msg msg, ImageLayout& data) = 0;

        /// Image memory file xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image memory file xfer data.
        virtual ReturnCode imageMemFileXfer(const Identity& origin, Msg msg, ImageMemFileXfer& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady)){
                return seqError();
            }

            auto rc = imageMemFileXferGet(origin, data);
            if (rc == ReturnCode::XferDone){
                setState(DsState::Xferring);
            }

            return rc;
        }

            /// Get image memory file xfer TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Image memory file xfer data.
            virtual ReturnCode imageMemFileXferGet(const Identity& origin, ImageMemFileXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Image memory xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image memory xfer data.
        virtual ReturnCode imageMemXfer(const Identity& origin, Msg msg, ImageMemXfer& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady, DsState::Xferring)){
                return seqError();
            }

            auto rc = imageMemXferGet(origin, data);
            if (Twpp::success(rc) || rc == ReturnCode::XferDone){
                setState(DsState::Xferring);
            }

            return rc;
        }

            /// Get image memory xfer TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param msg Message, action to perform.
            /// \param data Image memory xfer data.
            virtual ReturnCode imageMemXferGet(const Identity& origin, ImageMemXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Image native xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Handle to image native xfer data.
        virtual ReturnCode imageNativeXfer(const Identity& origin, Msg msg, ImageNativeXfer& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady)){
                return seqError();
            }

            auto rc = imageNativeXferGet(origin, data);
            if (rc == ReturnCode::XferDone){
                setState(DsState::Xferring);
            }

            return rc;
        }

            /// Get image native xfer TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Handle to image native xfer data.
            virtual ReturnCode imageNativeXferGet(const Identity& origin, ImageNativeXfer& data) = 0;

        /// JPEG compression TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data JPEG compression data.
        virtual ReturnCode jpegCompression(const Identity& origin, Msg msg, JpegCompression& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Palette8 TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Palette8 data.
        virtual ReturnCode palette8(const Identity& origin, Msg msg, Palette8& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// RGB response TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data RGB response data.
        virtual ReturnCode rgbResponse(const Identity& origin, Msg msg, RgbResponse& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }


    /// Root of source audio TWAIN calls.
    /// \param origin Identity of the caller.
    /// \param dat Type of data.
    /// \param msg Message, action to perform.
    /// \param data The data, may be null.
    virtual ReturnCode audio(const Identity& origin, Dat dat, Msg msg, void* data){
        if (dat != Dat::AudioFileXfer && !data){
            return badValue();
        }

        switch (dat){
            case Dat::AudioFileXfer:
                return audioFileXfer(origin, msg);
            case Dat::AudioInfo:
                return audioInfo(origin, msg, *static_cast<AudioInfo*>(data));
            case Dat::AudioNativeXfer:
                return audioNativeXfer(origin, msg, *static_cast<AudioNativeXfer*>(data));
            default:
                return badProtocol();
        }
    }

        /// Audio file xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        virtual ReturnCode audioFileXfer(const Identity& origin, Msg msg){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady)){
                return seqError();
            }

            auto rc = audioFileXferGet(origin);
            if (rc == ReturnCode::XferDone){
                setState(DsState::Xferring);
            }

            return rc;
        }

            /// Get audio file xfer TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual ReturnCode audioFileXferGet(const Identity& origin){
                Detail::unused(origin);
                return badProtocol();
            }

        /// Audio info TWAIN call.
        /// Default implementation does nothing.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Audio info data.
        virtual ReturnCode audioInfo(const Identity& origin, Msg msg, AudioInfo& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }

        /// Audio native xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Handle to audio native xfer data.
        virtual ReturnCode audioNativeXfer(const Identity& origin, Msg msg, AudioNativeXfer& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady)){
                return seqError();
            }

            auto rc = audioNativeXferGet(origin, data);
            if (Twpp::success(rc)){
                setState(DsState::Xferring);
            }

            return rc;
        }

            /// Get audio native xfer TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param msg Message, action to perform.
            /// \param data Handle to audio native xfer data.
            virtual ReturnCode audioNativeXferGet(const Identity& origin, AudioNativeXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

private:
    ReturnCode notifyApp(Msg msg) noexcept{
        return g_entry(&m_srcId, &m_appId, DataGroup::Control, Dat::Null, msg, nullptr);
    }

    ReturnCode callRoot(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data) noexcept{
        if (!origin){
            return badProtocol();
        }

        try {
            return call(*origin, dg, dat, msg, data);
        } catch (const std::bad_alloc&){
            return setStatus(ConditionCode::LowMemory);
        } catch (...){
            // the exception would be caught in the static handler below
            // that would set static status, we want to set local one
            return setStatus(ConditionCode::Bummer);
        }
    }


    Identity m_srcId;
    Identity m_appId;
    Status m_lastStatus;
    DsState m_state;



    static ReturnCode setStatRet(Status stat, ReturnCode rc = ReturnCode::Failure){
        g_lastStatus = stat;
        return rc;
    }

    static ReturnCode statSuccess(){
        return setStatRet(ConditionCode::Success, ReturnCode::Success);
    }

    static typename std::list<Derived>::iterator find(Identity* origin) noexcept{
        if (origin){
            for (auto it = g_sources.begin(); it != g_sources.end(); ++it){
                if (it->m_appId.id() == origin->id()){
                    return it;
                }
            }
        }

        return g_sources.end();
    }

    static void resetDsm(){
        g_entry = nullptr;

#if defined(TWPP_DETAIL_OS_WIN32)
        g_dsm.unload();
#endif
    }

    static ReturnCode staticCall(typename std::list<Derived>::iterator src, Identity* origin,
                                 DataGroup dg, Dat dat, Msg msg, void* data){

#if defined(TWPP_DETAIL_OS_WIN32)
        if (!g_entry){
            if (!g_dsm && !g_dsm.load(true)){
                return setStatRet(ConditionCode::Bummer);
            }

            g_entry = g_dsm.resolve();
        }
#endif

        if (!g_entry){
            return setStatRet(ConditionCode::Bummer);
        }

        auto rc = src->callRoot(origin, dg, dat, msg, data);

        if (dg == DataGroup::Control && dat == Dat::Identity && (
                (msg == Msg::CloseDs && rc == ReturnCode::Success) ||
                (msg == Msg::OpenDs && rc != ReturnCode::Success)
            )
        ){
            g_lastStatus = src->m_lastStatus;
            g_sources.erase(src);

            if (g_sources.empty()){
                resetDsm();
            }
        }

        return rc;
    }

    static ReturnCode staticControl(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data){
        if (dg != DataGroup::Control){
            return setStatRet(ConditionCode::SeqError);
        }

        switch (dat){
            case Dat::EntryPoint:
                if (msg == Msg::Set){
                    if (!data){
                        return setStatRet(ConditionCode::BadValue);
                    }

                    auto& e = *static_cast<Detail::EntryPoint*>(data);
                    g_entry = e.m_entry;
                    Detail::setMemFuncs(e.m_alloc, e.m_free, e.m_lock, e.m_unlock);
                    return statSuccess();
                }

                break;

            case Dat::Status: {
                if (msg == Msg::Get){
                    if (!data){
                        return setStatRet(ConditionCode::BadValue);
                    }

                    *static_cast<Status*>(data) = g_lastStatus;
                    return statSuccess();
                }

                break;
            }

            case Dat::Identity: {
                switch (msg){
                    case Msg::Get: {
                        if (!data){
                            return setStatRet(ConditionCode::BadValue);
                        }

                        auto& ident = *static_cast<Identity*>(data);
                        const Identity& def = Derived::defaultIdentity();
                        ident = Identity(ident.id(), def.version(), def.protocolMajor(),
                                         def.protocolMinor(), def.dataGroupsRaw(), def.manufacturer(),
                                         def.productFamily(), def.productName());

                        return statSuccess();
                    }

                    case Msg::OpenDs: {
                        g_sources.emplace_back();
                        return staticCall(--g_sources.end(), origin, dg, dat, msg, data);
                    }

                    case Msg::CloseDs:
                        // not open yet
                        return statSuccess();

                    default:
                        break;
                }

                break;
            }

            default:
                if (dat >= Dat::CustomBase){
                    Status status;
                    auto rc = Detail::StaticCustomBaseProc<Derived, hasStaticCustomBaseProc>()(dat, msg, data, status);
                    return setStatRet(status, rc);
                }

                break;
        }

        return setStatRet(ConditionCode::BadProtocol);
    }

public:
    static ReturnCode entry(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data) noexcept{
        auto src = find(origin);
        try {
            return src == g_sources.end() ?
                        staticControl(origin, dg, dat, msg, data) :
                        staticCall(src, origin, dg, dat, msg, data);
        } catch (const std::bad_alloc&) {
            return setStatRet(ConditionCode::LowMemory);
        } catch (...){
            // we can't throw exceptions out of data sources
            // the C interface can't really handle them
            // especially when there are different implementations
            return setStatRet(ConditionCode::Bummer);
        }
    }

private:
    static std::list<Derived> g_sources;
    static Detail::DsmEntry g_entry;
    static Status g_lastStatus;

#if defined(TWPP_DETAIL_OS_WIN32)
    static Detail::DsmLib g_dsm; // only old windows dsm requires this
#endif

};

template<typename Derived, bool proc>
std::list<Derived> SourceFromThis<Derived, proc>::g_sources;

template<typename Derived, bool proc>
Detail::DsmEntry SourceFromThis<Derived, proc>::g_entry;

template<typename Derived, bool proc>
Status SourceFromThis<Derived, proc>::g_lastStatus;

#if defined(TWPP_DETAIL_OS_WIN32)
template<typename Derived, bool proc>
Detail::DsmLib SourceFromThis<Derived, proc>::g_dsm;
#endif

}

#endif // TWPP_DETAIL_FILE_DATASOURCE_HPP

