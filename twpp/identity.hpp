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

#ifndef TWPP_DETAIL_FILE_IDENTITY_HPP
#define TWPP_DETAIL_FILE_IDENTITY_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

static constexpr const UInt32 identV2 = TWPP_DETAIL_IS_DS ? Detail::Ds2 : Detail::App2;

}

TWPP_DETAIL_PACK_BEGIN
/// Source or application version information.
class Version {

public:
    /// Creates default-initialized version.
    constexpr Version() noexcept :
        m_majorNum(0), m_minorNum(0), m_language(Language::English),
        m_country(Country::UnitedKingdom){}

    /// Creates version initialized with supplied values.
    constexpr Version(
            UInt16 majorNumber,
            UInt16 minorNumber,
            Language language,
            Country country,
            const Str32& info = Str32()) noexcept :
        m_majorNum(majorNumber), m_minorNum(minorNumber), m_language(language),
        m_country(country), m_info(info){}

    /// Major version number of the source or application.
    constexpr UInt16 majorNumber() const noexcept{
        return m_majorNum;
    }

    /// Sets major version number of the source or application.
    void setMajorNumber(UInt16 major) noexcept{
        m_majorNum = major;
    }

    /// Minor version number of the source or application.
    constexpr UInt16 minorNumber() const noexcept{
        return m_minorNum;
    }

    /// Sets minor version number of the source or application.
    void setMinorNumber(UInt16 minor) noexcept{
        m_minorNum = minor;
    }

    /// Language of the source or application.
    constexpr Language language() const noexcept{
        return m_language;
    }

    /// Sets language of the source or application.
    void setLanguage(Language language) noexcept{
        m_language = language;
    }

    /// Original country of the source or application.
    constexpr Country country() const noexcept{
        return m_country;
    }

    /// Set original country of the source or application.
    void setCountry(Country country) noexcept{
        m_country = country;
    }

    /// Additional version information of the source or application.
    constexpr const Str32& info() const noexcept{
        return m_info;
    }

    /// Sets additional version information of the source or application.
    void setInfo(const Str32& info) noexcept{
        m_info = info;
    }

private:
    UInt16 m_majorNum;
    UInt16 m_minorNum;
    Language m_language;
    Country m_country;
    Str32 m_info;

};

/// Source or application identity.
/// Uniquely identifies an endpoint.
class Identity {

public:
    typedef
#if defined(TWPP_DETAIL_OS_MAC)
    void*
#else
    UInt32
#endif
    Id;

    /// Creates default-initialized identity.
    /// ID is set to zero.
    /// TWAIN protocol is always Detail::ProtoMajor and Detail::ProtoMinor.
    /// Supported group always contains DG::Control and V2.
    constexpr Identity() noexcept :
        m_id(), m_protoMaj(Detail::ProtoMajor), m_protoMin(Detail::ProtoMinor),
        m_groups(DataGroup::Control | Detail::identV2){}

    /// Creates identity initialized with supplied values.
    /// ID is set to zero.
    /// TWAIN protocol is always Detail::ProtoMajor and Detail::ProtoMinor.
    /// Supported group always contains DG::Control and V2.
    constexpr Identity(
            const Version& version,
            DataGroup group,
            const Str32& manufacturer,
            const Str32& productFamily,
            const Str32& productName) noexcept :
        m_id(), m_version(version), m_protoMaj(Detail::ProtoMajor),
        m_protoMin(Detail::ProtoMinor), m_groups(DataGroup::Control | group | Detail::identV2),
        m_manuf(manufacturer), m_prodFamily(productFamily), m_prodName(productName){}

    /// Creates identity initialized with supplied values.
    constexpr Identity(
            Id id,
            const Version& version,
            UInt16 protoMajor,
            UInt16 protoMinor,
            UInt32 groups,
            const Str32& manufacturer,
            const Str32& productFamily,
            const Str32& productName) noexcept :
        m_id(id), m_version(version), m_protoMaj(protoMajor), m_protoMin(protoMinor),
        m_groups(groups), m_manuf(manufacturer), m_prodFamily(productFamily),
        m_prodName(productName){}

    /// DSM-supplied ID of this identity.
    constexpr Id id() const{
        return m_id;
    }

    /// Version information.
    constexpr const Version& version() const noexcept{
        return m_version;
    }

    /// Whether a data group is supported.
    constexpr bool supports(DataGroup group) const noexcept{
        return (m_groups & group) != 0;
    }

    /// Whether this is V2 application.
    constexpr bool isAppV2() const noexcept{
        return (m_groups & Detail::App2) != 0;
    }

    /// Whether this is V2 DSM.
    constexpr bool isDsmV2() const noexcept{
        return (m_groups & Detail::Dsm2) != 0;
    }

    /// Whether this is V2 source.
    constexpr bool isDsV2() const noexcept{
        return (m_groups & Detail::Ds2) != 0;
    }

    /// The manufacturer.
    /// Manufacturer and product name uniquely identify a source.
    constexpr const Str32& manufacturer() const noexcept{
        return m_manuf;
    }

    /// The product name.
    /// Manufacturer and product name uniquely identify a source.
    constexpr const Str32& productName() const noexcept{
        return m_prodName;
    }

    /// The product family.
    constexpr const Str32& productFamily() const noexcept{
        return m_prodFamily;
    }

    /// Raw data group flags.
    constexpr UInt32 dataGroupsRaw() const noexcept{
        return m_groups;
    }

    /// TWAIN protocol major version.
    constexpr UInt16 protocolMajor() const noexcept{
        return m_protoMaj;
    }

    /// TWAIN protocol minor version.
    constexpr UInt16 protocolMinor() const noexcept{
        return m_protoMin;
    }

private:
    Id m_id;
    Version m_version;
    UInt16 m_protoMaj;
    UInt16 m_protoMin;
    UInt32 m_groups;
    Str32 m_manuf;
    Str32 m_prodFamily;
    Str32 m_prodName;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_IDENTITY_HPP
