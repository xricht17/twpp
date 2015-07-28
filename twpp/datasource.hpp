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

#define TWPP_ENTRY(SourceClass)\
    extern "C" TWPP_DETAIL_EXPORT ReturnCode TWPP_DETAIL_CALLSTYLE \
    DS_Entry(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data){\
        return SourceClass::entry(origin, dg, dat, msg, data);\
    }

/// Result of a data source operation.
/// Contains both return code and status.
class Result {

public:
    /// Creates successful result.
    constexpr Result() noexcept :
        m_status(), m_rc(ReturnCode::Success){}

    /// Creates result with supplied return code and status.
    constexpr Result(ReturnCode rc, Status status) noexcept :
        m_status(status), m_rc(rc){}

    /// Status part of the result.
    constexpr Status status() const noexcept{
        return m_status;
    }

    /// Return code part of the result.
    constexpr ReturnCode returnCode() const noexcept{
        return m_rc;
    }

    /// Sets status part of the result.
    void setStatus(Status status) noexcept{
        m_status = status;
    }

    /// Sets return code part of the result.
    void setReturnCode(ReturnCode rc) noexcept{
        m_rc = rc;
    }

    constexpr operator ReturnCode() const noexcept{
        return m_rc;
    }

    constexpr operator Status() const noexcept{
        return m_status;
    }

private:
    Status m_status;
    ReturnCode m_rc;

};

static constexpr inline bool success(const Result& res) noexcept{
    return success(res.returnCode());
}


namespace Detail {

template<typename Derived, bool enabled> // false
struct StaticCustomBaseProc {
    Result operator()(Dat, Msg, void*){
        return {ReturnCode::Failure, ConditionCode::BadProtocol};
    }
};

template<typename Derived>
struct StaticCustomBaseProc<Derived, true> {
    Result operator()(Dat dat, Msg msg, void* data){
        return Derived::staticCustomBase(dat, msg, data);
    }
};

}

namespace SourceFromThisProcs {

/// Returns data source identity not associated with any instance.
const Identity& defaultIdentity();

/// Processes custom TWAIN operations without having any opened connection.
/// DataGroup is always Control.
/// \param dat Type of data. Dat::CustomBase + X.
/// \param msg Message, action to perform.
/// \param data The data, may be null.
/// \return Operation result code.
Result staticCustomBase(Dat dat, Msg msg, void* data);

}

/// Base class of a TWAIN data source.
/// It handles instances creation and all static calls.
///
/// The derived class must:
///  1) Implement at least all pure virtual methods.
///  2) Provide `static const Identity& defaultIdentity()`.
///  3) If hasStaticCustomBaseProc == true, provide
///     `static Result staticCustomBase(Dat dat, Msg msg, void* data)`.
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

    /// Shortcut for Result(RC::Success, CC::Success).
    static constexpr Result success() noexcept{
        return {ReturnCode::Success, ConditionCode::Success};
    }

    /// Shortcut for Result(RC::Failure, CC::BadValue).
    static constexpr Result badValue() noexcept{
        return {ReturnCode::Failure, ConditionCode::BadValue};
    }

    /// Shortcut for Result(RC::Failure, CC::BadProtocol).
    static constexpr Result badProtocol() noexcept{
        return {ReturnCode::Failure, ConditionCode::BadProtocol};
    }

    /// Shortcut for Result(RC::Failure, CC::SeqError).
    static constexpr Result seqError() noexcept{
        return {ReturnCode::Failure, ConditionCode::SeqError};
    }

    /// Shortcut for Result(RC::Failure, CC::CapBadOperation).
    static constexpr Result capBadOperation() noexcept{
        return {ReturnCode::Failure, ConditionCode::CapBadOperation};
    }

    /// Shortcut for Result(RC::Failure, CC::CapUnsupported).
    static constexpr Result capUnsupported() noexcept{
        return {ReturnCode::Failure, ConditionCode::CapUnsupported};
    }

    /// Shortcut for Result(RC::Failure, CC::Bummber).
    static constexpr Result bummer() noexcept{
        return {ReturnCode::Failure, ConditionCode::Bummer};
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
    virtual Result call(const Identity& origin, DataGroup dg, Dat dat, Msg msg, void* data){
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
    virtual Result control(const Identity& origin, Dat dat, Msg msg, void* data){
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
        /// Reset, set and set constraint operations are limited to
        /// state DsState::Open (4), override this method if you
        /// support CapType::ExtendedCaps.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Capability data.
        virtual Result capability(const Identity& origin, Msg msg, Capability& data){
            switch (msg){
                case Msg::Get:
                    // 4 - 7
                    return capabilityGet(origin, data);

                case Msg::GetCurrent:
                    // 4 - 7
                    return capabilityGetCurrent(origin, data);

                case Msg::GetDefault:
                    // 4 - 7
                    return capabilityGetDefault(origin, data);

                case Msg::GetHelp:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilityGetHelp(origin, data);

                case Msg::GetLabel:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilityGetLabel(origin, data);

                case Msg::GetLabelEnum:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilityGetLabelEnum(origin, data);

                case Msg::QuerySupport:
                    // 4 - 7
                    return capabilityQuerySupport(origin, data);

                case Msg::Reset:
                    // 4, extended: 5, 6, 7
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilityReset(origin, data);

                case Msg::ResetAll:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilityResetAll(origin); // data has no meaning here

                case Msg::Set:
                    // 4, extended: 5, 6, 7
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilitySet(origin, data);

                case Msg::SetConstraint:
                    // 4, extended: 5, 6, 7
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return capabilitySetConstraint(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get capability TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityGet(const Identity& origin, Capability& data) = 0;

            /// Get current capability TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityGetCurrent(const Identity& origin, Capability& data) = 0;

            /// Get default capability TWAIN call.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityGetDefault(const Identity& origin, Capability& data) = 0;

            /// Get help capability TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityGetHelp(const Identity& origin, Capability& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get label capability TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityGetLabel(const Identity& origin, Capability& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get label enum capability TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityGetLabelEnum(const Identity& origin, Capability& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Query support capability TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityQuerySupport(const Identity& origin, Capability& data) = 0;

            /// Reset capability TWAIN call.
            /// Always called in correct state: 4, if you support extended
            /// capabilities, override `capability` method.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilityReset(const Identity& origin, Capability& data) = 0;

            /// Reset all capability TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual Result capabilityResetAll(const Identity& origin) = 0;

            /// Set capability TWAIN call.
            /// Always called in correct state: 4, if you support extended
            /// capabilities, override `capability` method.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilitySet(const Identity& origin, Capability& data) = 0;

            /// Set capability TWAIN call.
            /// Always called in correct state: 4, if you support extended
            /// capabilities, override `capability` method.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Capability data.
            virtual Result capabilitySetConstraint(const Identity& origin, Capability& data){
                Detail::unused(origin, data);
                return badProtocol();
            }



        /// Custom data TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Custom data.
        virtual Result customData(const Identity& origin, Msg msg, CustomData& data){
            if (!inState(DsState::Open)){
                return seqError();
            }

            switch (msg){
                case Msg::Get:
                    return customDataGet(origin, data);

                case Msg::Set:
                    return customDataSet(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get custom data TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Custom data.
            virtual Result customDataGet(const Identity& origin, CustomData& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Set custom data TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Custom data.
            virtual Result customDataSet(const Identity& origin, CustomData& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Device event TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Device event data.
        virtual Result deviceEvent(const Identity& origin, Msg msg, DeviceEvent& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            return deviceEventGet(origin, data);
        }

            /// Get device event TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Device event data.
            virtual Result deviceEventGet(const Identity& origin, DeviceEvent& data){
                Detail::unused(origin, data);
                return badProtocol();
            }



        /// Event TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Event data.
        virtual Result event(const Identity& origin, Msg msg, Event& data){
            if (msg != Msg::ProcessEvent){
                return badProtocol();
            }

            if (!inState(DsState::Enabled, DsState::Xferring)){
                return seqError();
            }

            return eventProcess(origin, data);
        }

#if defined(TWPP_DETAIL_OS_WIN)
            /// Process event TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Event data.
            virtual Result eventProcess(const Identity& origin, Event& data) = 0;
#else
            /// Process event TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Event data.
            virtual Result eventProcess(const Identity& origin, Event& data){
                Detail::unused(origin, data);
                return badProtocol();
            }
#endif

        /// Identity TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Identity data.
        virtual Result identity(const Identity& origin, Msg msg, Identity& data){
            Result rc;
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
            virtual Result identityOpenDs(const Identity& origin) = 0;

            /// Close source identity TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual Result identityCloseDs(const Identity& origin) = 0;

        /// File system TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data File system data.
        virtual Result fileSystem(const Identity& origin, Msg msg, FileSystem& data){
            switch (msg){
                case Msg::AutomaticCaptureDirectory:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemAutomatic(origin, data);

                case Msg::ChangeDirectory:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemChange(origin, data);

                case Msg::Copy:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemCopy(origin, data);

                case Msg::CreateDirectory:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemCreate(origin, data);

                case Msg::Delete:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemDelete(origin, data);

                case Msg::FormatMedia:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemFormat(origin, data);

                case Msg::GetClose:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return fileSystemGetClose(origin, data);

                case Msg::GetFirstFile:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return fileSystemGetFirst(origin, data);

                case Msg::GetInfo:
                    // 4 - 7
                    return fileSystemGetInfo(origin, data);

                case Msg::GetNextFile:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return fileSystemGetNext(origin, data);

                case Msg::Rename:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return fileSystemRename(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Automatic capture directory file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemAutomatic(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Change directory file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemChange(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }


            /// Copy file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemCopy(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Create directory file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemCreate(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Delete file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemDelete(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Format media file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemFormat(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get close file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemGetClose(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get first file file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemGetFirst(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get info file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemGetInfo(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get next file file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemGetNext(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Rename file system TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data File system data.
            virtual Result fileSystemRename(const Identity& origin, FileSystem& data){
                Detail::unused(origin, data);
                return badProtocol();
            }


        /// Pass through TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Pass through data.
        virtual Result passThrough(const Identity& origin, Msg msg, PassThrough& data){
            if (msg != Msg::PassThrough){
                return badProtocol();
            }

            // 4 - 7
            return passThroughPass(origin, data);
        }

            /// Pass through pass through TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Pass through data.
            virtual Result passThroughPass(const Identity& origin, PassThrough& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Pending xfers TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Pending xfers data.
        virtual Result pendingXfers(const Identity& origin, Msg msg, PendingXfers& data){
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
            virtual Result pendingXfersGet(const Identity& origin, PendingXfers& data) = 0;

            /// End xfer pending xfers TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual Result pendingXfersEnd(const Identity& origin, PendingXfers& data) = 0;

            /// Reset xfers pending xfers TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual Result pendingXfersReset(const Identity& origin, PendingXfers& data) = 0;

            /// Stop feeder pending xfers TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Pending xfers data.
            virtual Result pendingXfersStopFeeder(const Identity& origin, PendingXfers& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Setup file xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Setup file xfer data.
        virtual Result setupFileXfer(const Identity& origin, Msg msg, SetupFileXfer& data){
            switch (msg){
                case Msg::Get:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return setupFileXferGet(origin, data);

                case Msg::GetDefault:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return setupFileXferGetDefault(origin, data);

                case Msg::Set:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return setupFileXferSet(origin, data);

                case Msg::Reset:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return setupFileXferReset(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get setup file xfer TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Setup file xfer data.
            virtual Result setupFileXferGet(const Identity& origin, SetupFileXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get default setup file xfer TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Setup file xfer data.
            virtual Result setupFileXferGetDefault(const Identity& origin, SetupFileXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Set setup file xfer TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Setup file xfer data.
            virtual Result setupFileXferSet(const Identity& origin, SetupFileXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Reset setup file xfer TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Setup file xfer data.
            virtual Result setupFileXferReset(const Identity& origin, SetupFileXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Setup memory xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Setup memory xfer data.
        virtual Result setupMemXfer(const Identity& origin, Msg msg, SetupMemXfer& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::Open, DsState::XferReady)){
                return seqError();
            }

            return setupMemXferGet(origin, data);
        }

            /// Get setup memory xfer TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Setup memory xfer data.
            virtual Result setupMemXferGet(const Identity& origin, SetupMemXfer& data) = 0;

        /// Status TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Status data.
        virtual Result status(const Identity& origin, Msg msg, Status& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            return statusGet(origin, data);
        }

            /// Get status TWAIN call.
            /// Always called in correct state.
            /// Default implementation returns last status.
            /// \param origin Identity of the caller.
            /// \param data Status data.
            virtual Result statusGet(const Identity& origin, Status& data){
                Detail::unused(origin);
                data = lastStatus();
                return success();
            }

        /// Status utf8 TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Status utf8 data.
        virtual Result statusUtf8(const Identity& origin, Msg msg, StatusUtf8& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            // 3 - 7
            return statusUtf8Get(origin, data);
        }

            /// Get status utf8 TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param msg Message, action to perform.
            /// \param data Status utf8 data.
            virtual Result statusUtf8Get(const Identity& origin, StatusUtf8& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// User interface TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data User interface data.
        virtual Result userInterface(const Identity& origin, Msg msg, UserInterface& data){
            Result rc;
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
            virtual Result userInterfaceDisable(const Identity& origin, UserInterface& data) = 0;

            /// Enable user interface TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data User interface data.
            virtual Result userInterfaceEnable(const Identity& origin, UserInterface& data) = 0;

            /// Enable UI only user interface TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data User interface data.
            virtual Result userInterfaceEnableUiOnly(const Identity& origin, UserInterface& data) = 0;

        /// Xfer group TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Xfer group data.
        virtual Result xferGroup(const Identity& origin, Msg msg, DataGroup& data){
            switch (msg){
                case Msg::Get:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return xferGroupGet(origin, data);

                case Msg::Set:
                    if (!inState(DsState::XferReady)){
                        return seqError();
                    }

                    return xferGroupSet(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get xfer group TWAIN call.
            /// Always called in correct state.
            /// Default implementation returns DataGroup::Image.
            /// \param origin Identity of the caller.
            /// \param data Xfer group data.
            virtual Result xferGroupGet(const Identity& origin, DataGroup& data){
                Detail::unused(origin);
                data = DataGroup::Image;
                return success();
            }

            /// Set xfer group TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Xfer group data.
            virtual Result xferGroupSet(const Identity& origin, DataGroup& data){
                Detail::unused(origin, data);
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
    virtual Result image(const Identity& origin, Dat dat, Msg msg, void* data){
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
        virtual Result cieColor(const Identity& origin, Msg msg, CieColor& data){
            Detail::unused(origin, msg, data);
            return badProtocol();
        }*/

        /// Ext image info TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Ext image info data.
        virtual Result extImageInfo(const Identity& origin, Msg msg, ExtImageInfo& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::Xferring)){
                return seqError();
            }

            return extImageInfoGet(origin, data);
        }

            /// Get ext image info TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Ext image info data.
            virtual Result extImageInfoGet(const Identity& origin, ExtImageInfo& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Gray response TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Gray response data.
        virtual Result grayResponse(const Identity& origin, Msg msg, GrayResponse& data){
            if (!inState(DsState::Open)){
                return seqError();
            }

            switch (msg){
                case Msg::Set:
                    return grayResponseSet(origin, data);

                case Msg::Reset:
                    return grayResponseReset(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Set gray response TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Gray response data.
            virtual Result grayResponseSet(const Identity& origin, GrayResponse& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Reset gray response TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Gray response data.
            virtual Result grayResponseReset(const Identity& origin, GrayResponse& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// ICC profile TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data ICC profile data.
        virtual Result iccProfile(const Identity& origin, Msg msg, IccProfileMemory& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady, DsState::Xferring)){
                return seqError();
            }

            return iccProfileGet(origin, data);
        }

            /// Get ICC profile TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data ICC profile data.
            virtual Result iccProfileGet(const Identity& origin, IccProfileMemory& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Image file xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        virtual Result imageFileXfer(const Identity& origin, Msg msg){
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
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            virtual Result imageFileXferGet(const Identity& origin){
                Detail::unused(origin);
                return badProtocol();
            }

        /// Image info TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image info data.
        virtual Result imageInfo(const Identity& origin, Msg msg, ImageInfo& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady, DsState::Xferring)){
                return seqError();
            }

            return imageInfoGet(origin, data);
        }

            /// Get image info TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Image info data.
            virtual Result imageInfoGet(const Identity& origin, ImageInfo& data) = 0;


        /// Image layout TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image layout data.
        virtual Result imageLayout(const Identity& origin, Msg msg, ImageLayout& data){
            switch (msg){
                case Msg::Get:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return imageLayoutGet(origin, data);

                case Msg::GetDefault:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return imageLayoutGetDefault(origin, data);

                case Msg::Set:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return imageLayoutSet(origin, data);

                case Msg::Reset:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return imageLayoutReset(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get image layout TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Image layout data.
            virtual Result imageLayoutGet(const Identity& origin, ImageLayout& data) = 0;

            /// Get default image layout TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Image layout data.
            virtual Result imageLayoutGetDefault(const Identity& origin, ImageLayout& data) = 0;

            /// Set image layout TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Image layout data.
            virtual Result imageLayoutSet(const Identity& origin, ImageLayout& data) = 0;

            /// Reset image layout TWAIN call.
            /// Always called in correct state.
            /// \param origin Identity of the caller.
            /// \param data Image layout data.
            virtual Result imageLayoutReset(const Identity& origin, ImageLayout& data) = 0;


        /// Image memory file xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image memory file xfer data.
        virtual Result imageMemFileXfer(const Identity& origin, Msg msg, ImageMemFileXfer& data){
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
            virtual Result imageMemFileXferGet(const Identity& origin, ImageMemFileXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Image memory xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Image memory xfer data.
        virtual Result imageMemXfer(const Identity& origin, Msg msg, ImageMemXfer& data){
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
            /// \param origin Identity of the caller.
            /// \param data Image memory xfer data.
            virtual Result imageMemXferGet(const Identity& origin, ImageMemXfer& data) = 0;

        /// Image native xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Handle to image native xfer data.
        virtual Result imageNativeXfer(const Identity& origin, Msg msg, ImageNativeXfer& data){
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
            virtual Result imageNativeXferGet(const Identity& origin, ImageNativeXfer& data) = 0;

        /// JPEG compression TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data JPEG compression data.
        virtual Result jpegCompression(const Identity& origin, Msg msg, JpegCompression& data){
            switch (msg){
                case Msg::Get:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return jpegCompressionGet(origin, data);

                case Msg::GetDefault:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return jpegCompressionGetDefault(origin, data);

                case Msg::Set:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return jpegCompressionSet(origin, data);

                case Msg::Reset:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return jpegCompressionReset(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get JPEG compression TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data JPEG compression data.
            virtual Result jpegCompressionGet(const Identity& origin, JpegCompression& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get default JPEG compression TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data JPEG compression data.
            virtual Result jpegCompressionGetDefault(const Identity& origin, JpegCompression& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Set JPEG compression TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data JPEG compression data.
            virtual Result jpegCompressionSet(const Identity& origin, JpegCompression& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Reset JPEG compression TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data JPEG compression data.
            virtual Result jpegCompressionReset(const Identity& origin, JpegCompression& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Palette8 TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Palette8 data.
        virtual Result palette8(const Identity& origin, Msg msg, Palette8& data){
            switch (msg){
                case Msg::Get:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return palette8Get(origin, data);

                case Msg::GetDefault:
                    if (!inState(DsState::Open, DsState::XferReady)){
                        return seqError();
                    }

                    return palette8GetDefault(origin, data);

                case Msg::Set:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return palette8Set(origin, data);

                case Msg::Reset:
                    if (!inState(DsState::Open)){
                        return seqError();
                    }

                    return palette8Reset(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Get Palette8 TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Palette8 data.
            virtual Result palette8Get(const Identity& origin, Palette8& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Get default Palette8 TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Palette8 data.
            virtual Result palette8GetDefault(const Identity& origin, Palette8& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Set Palette8 TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Palette8 data.
            virtual Result palette8Set(const Identity& origin, Palette8& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Reset Palette8 TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Palette8 data.
            virtual Result palette8Reset(const Identity& origin, Palette8& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// RGB response TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data RGB response data.
        virtual Result rgbResponse(const Identity& origin, Msg msg, RgbResponse& data){
            if (!inState(DsState::Open)){
                return seqError();
            }

            switch (msg){
                case Msg::Set:
                    return rgbResponseSet(origin, data);

                case Msg::Reset:
                    return rgbResponseReset(origin, data);

                default:
                    return badProtocol();
            }
        }

            /// Set RGB response TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data RGB response data.
            virtual Result rgbResponseSet(const Identity& origin, RgbResponse& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

            /// Reset RGB response TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data RGB response data.
            virtual Result rgbResponseReset(const Identity& origin, RgbResponse& data){
                Detail::unused(origin, data);
                return badProtocol();
            }


    /// Root of source audio TWAIN calls.
    /// \param origin Identity of the caller.
    /// \param dat Type of data.
    /// \param msg Message, action to perform.
    /// \param data The data, may be null.
    virtual Result audio(const Identity& origin, Dat dat, Msg msg, void* data){
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
        virtual Result audioFileXfer(const Identity& origin, Msg msg){
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
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            virtual Result audioFileXferGet(const Identity& origin){
                Detail::unused(origin);
                return badProtocol();
            }

        /// Audio info TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Audio info data.
        virtual Result audioInfo(const Identity& origin, Msg msg, AudioInfo& data){
            if (msg != Msg::Get){
                return badProtocol();
            }

            if (!inState(DsState::XferReady, DsState::Xferring)){
                return seqError();
            }

            return audioInfoGet(origin, data);
        }

            /// Get audio info TWAIN call.
            /// Always called in correct state.
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Audio info data.
            virtual Result audioInfoGet(const Identity& origin, AudioInfo& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

        /// Audio native xfer TWAIN call.
        /// \param origin Identity of the caller.
        /// \param msg Message, action to perform.
        /// \param data Handle to audio native xfer data.
        virtual Result audioNativeXfer(const Identity& origin, Msg msg, AudioNativeXfer& data){
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
            /// Default implementation does nothing.
            /// \param origin Identity of the caller.
            /// \param data Handle to audio native xfer data.
            virtual Result audioNativeXferGet(const Identity& origin, AudioNativeXfer& data){
                Detail::unused(origin, data);
                return badProtocol();
            }

private:
    ReturnCode notifyApp(Msg msg) noexcept{
        return g_entry(&m_srcId, &m_appId, DataGroup::Control, Dat::Null, msg, nullptr);
    }

    Result callRoot(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data) noexcept{
        if (!origin){
            return badProtocol();
        }

        try {
            return call(*origin, dg, dat, msg, data);
        } catch (const std::bad_alloc&){
            return {ReturnCode::Failure, ConditionCode::LowMemory};
        } catch (...){
            // the exception would be caught in the static handler below
            // that would set static status, we want to set local one
            return bummer();
        }
    }


    Identity m_srcId;
    Identity m_appId;
    Status m_lastStatus;
    DsState m_state;


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

    static Result staticCall(typename std::list<Derived>::iterator src, Identity* origin,
                                 DataGroup dg, Dat dat, Msg msg, void* data){

#if defined(TWPP_DETAIL_OS_WIN32)
        if (!g_entry){
            if (!g_dsm && !g_dsm.load(true)){
                return bummer();
            }

            g_entry = g_dsm.resolve();
        }
#endif

        if (!g_entry){
            return bummer();
        }

        auto rc = src->callRoot(origin, dg, dat, msg, data);
        src->m_lastStatus = rc.status();

        if (dg == DataGroup::Control && dat == Dat::Identity && (
                (msg == Msg::CloseDs && Twpp::success(rc)) ||
                (msg == Msg::OpenDs && !Twpp::success(rc))
            )
        ){
            g_sources.erase(src);
            if (g_sources.empty()){
                resetDsm();
            }
        }

        return rc;
    }

    static Result staticControl(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data){
        if (dg != DataGroup::Control){
            return seqError();
        }

        switch (dat){
            case Dat::EntryPoint:
                if (msg == Msg::Set){
                    if (!data){
                        return badValue();
                    }

                    auto& e = *static_cast<Detail::EntryPoint*>(data);
                    g_entry = e.m_entry;
                    Detail::setMemFuncs(e.m_alloc, e.m_free, e.m_lock, e.m_unlock);
                    return success();
                }

                break;

            case Dat::Status: {
                if (msg == Msg::Get){
                    if (!data){
                        return badValue();
                    }

                    *static_cast<Status*>(data) = g_lastStatus;
                    return success();
                }

                break;
            }

            case Dat::Identity: {
                switch (msg){
                    case Msg::Get: {
                        if (!data){
                            return badValue();
                        }

                        auto& ident = *static_cast<Identity*>(data);
                        const Identity& def = Derived::defaultIdentity();
                        ident = Identity(ident.id(), def.version(), def.protocolMajor(),
                                         def.protocolMinor(), def.dataGroupsRaw(), def.manufacturer(),
                                         def.productFamily(), def.productName());

                        return success();
                    }

                    case Msg::OpenDs: {
                        g_sources.emplace_back();
                        return staticCall(--g_sources.end(), origin, dg, dat, msg, data);
                    }

                    case Msg::CloseDs:
                        // not open yet
                        return success();

                    default:
                        break;
                }

                break;
            }

            default:
                if (dat >= Dat::CustomBase){
                    return Detail::StaticCustomBaseProc<Derived, hasStaticCustomBaseProc>()(dat, msg, data);
                }

                break;
        }

        return badProtocol();
    }

public:
    /// TWAIN entry, do not call from data source.
    static ReturnCode entry(Identity* origin, DataGroup dg, Dat dat, Msg msg, void* data) noexcept{
        auto src = find(origin);
        try {
            auto rc = src == g_sources.end() ?
                        staticControl(origin, dg, dat, msg, data) :
                        staticCall(src, origin, dg, dat, msg, data);

            g_lastStatus = rc.status();
            return rc.returnCode();
        } catch (const std::bad_alloc&) {
            g_lastStatus = ConditionCode::LowMemory;
            return ReturnCode::Failure;
        } catch (...){
            // we can't throw exceptions out of data sources
            // the C interface can't really handle them
            // especially when there are different implementations
            g_lastStatus = ConditionCode::Bummer;
            return ReturnCode::Failure;
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
Status SourceFromThis<Derived, proc>::g_lastStatus = ConditionCode::Bummer;

#if defined(TWPP_DETAIL_OS_WIN32)
template<typename Derived, bool proc>
Detail::DsmLib SourceFromThis<Derived, proc>::g_dsm;
#endif

}

#endif // TWPP_DETAIL_FILE_DATASOURCE_HPP

