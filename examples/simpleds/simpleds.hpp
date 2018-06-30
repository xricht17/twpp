#ifndef SIMPLEDS_HPP
#define SIMPLEDS_HPP

#include <twpp.hpp>
#include <unordered_map>

namespace std {

template<>
struct hash<Twpp::CapType> {
    size_t operator()(Twpp::CapType cap) const{
        return hash<Twpp::UInt16>()(static_cast<Twpp::UInt16>(cap));
    }
};

}

class SimpleDs : public Twpp::SourceFromThis<SimpleDs> {

public:
    static const Twpp::Identity& defaultIdentity() noexcept;

    // SourceFromThis interface
protected:
    typedef Twpp::SourceFromThis<SimpleDs> Base;

    virtual Twpp::Result capabilityGet(const Twpp::Identity& origin, Twpp::Capability& data) override;
    virtual Twpp::Result capabilityGetCurrent(const Twpp::Identity& origin, Twpp::Capability& data) override;
    virtual Twpp::Result capabilityGetDefault(const Twpp::Identity& origin, Twpp::Capability& data) override;
    virtual Twpp::Result capabilityQuerySupport(const Twpp::Identity& origin, Twpp::Capability& data) override;
    virtual Twpp::Result capabilityReset(const Twpp::Identity& origin, Twpp::Capability& data) override;
    virtual Twpp::Result capabilityResetAll(const Twpp::Identity& origin) override;
    virtual Twpp::Result capabilitySet(const Twpp::Identity& origin, Twpp::Capability& data) override;
    virtual Twpp::Result eventProcess(const Twpp::Identity& origin, Twpp::Event& data) override;
    virtual Twpp::Result identityOpenDs(const Twpp::Identity& origin) override;
    virtual Twpp::Result identityCloseDs(const Twpp::Identity& origin) override;
    virtual Twpp::Result pendingXfersGet(const Twpp::Identity& origin, Twpp::PendingXfers& data) override;
    virtual Twpp::Result pendingXfersEnd(const Twpp::Identity& origin, Twpp::PendingXfers& data) override;
    virtual Twpp::Result pendingXfersReset(const Twpp::Identity& origin, Twpp::PendingXfers& data) override;
    virtual Twpp::Result setupMemXferGet(const Twpp::Identity& origin, Twpp::SetupMemXfer& data) override;
    virtual Twpp::Result userInterfaceDisable(const Twpp::Identity& origin, Twpp::UserInterface& data) override;
    virtual Twpp::Result userInterfaceEnable(const Twpp::Identity& origin, Twpp::UserInterface& data) override;
    virtual Twpp::Result userInterfaceEnableUiOnly(const Twpp::Identity& origin, Twpp::UserInterface& data) override;
    virtual Twpp::Result imageInfoGet(const Twpp::Identity& origin, Twpp::ImageInfo& data) override;
    virtual Twpp::Result imageLayoutGet(const Twpp::Identity& origin, Twpp::ImageLayout& data) override;
    virtual Twpp::Result imageLayoutGetDefault(const Twpp::Identity& origin, Twpp::ImageLayout& data) override;
    virtual Twpp::Result imageLayoutSet(const Twpp::Identity& origin, Twpp::ImageLayout& data) override;
    virtual Twpp::Result imageLayoutReset(const Twpp::Identity& origin, Twpp::ImageLayout& data) override;
    virtual Twpp::Result imageMemXferGet(const Twpp::Identity& origin, Twpp::ImageMemXfer& data) override;
    virtual Twpp::Result imageNativeXferGet(const Twpp::Identity& origin, Twpp::ImageNativeXfer& data) override;

    virtual Twpp::Result call(const Twpp::Identity& origin, Twpp::DataGroup dg, Twpp::Dat dat, Twpp::Msg msg, void* data) override;

private:
    const BITMAPINFOHEADER* header() const noexcept;
    Twpp::UInt32 bytesPerLine() const noexcept;
    Twpp::UInt32 bmpSize() const noexcept;
    const char* bmpBegin() const noexcept;
    const char* bmpEnd() const noexcept;

    Twpp::Result capCommon(const Twpp::Identity& origin, Twpp::Msg msg, Twpp::Capability& data);

    std::unordered_map<Twpp::CapType, std::function<Twpp::Result(Twpp::Msg msg, Twpp::Capability& data)>> m_caps;
    std::unordered_map<Twpp::CapType, Twpp::MsgSupport> m_query;

    Twpp::UInt32 m_memXferYOff;
    Twpp::UInt16 m_pendingXfers;

    Twpp::Int16 m_capXferCount = -1;
    Twpp::XferMech m_capXferMech = Twpp::XferMech::Native;

};

#endif // SIMPLEDS_HPP
