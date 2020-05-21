/*

The MIT License (MIT)

Copyright (c) 2020 Martin Richter

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

#ifndef TWPP_DETAIL_FILE_SUPPORTEDDAT_HPP
#define TWPP_DETAIL_FILE_SUPPORTEDDAT_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Special value of SupportedDats Capability.
/// HIWORD is DataGroup, LOWORD is Dat.
class SupportedDat {

public:
    /// Creates an empty supported Dat.
    constexpr SupportedDat() noexcept :
#if defined(TWPP_DETAIL_ENDIAN_LITTLE)
        m_dat(Dat::Null), m_dataGroup(0) {}
#else
        m_dataGroup(0), m_dat(Dat::Null) {}
#endif

    /// Creates a supported Dat.
    /// \param data Group Group Data group of the Dat.
    /// \param dat Dat, an operation argument type.
    constexpr SupportedDat(DataGroup dataGroup, Dat dat) noexcept :
#if defined(TWPP_DETAIL_ENDIAN_LITTLE)
        m_dat(dat), m_dataGroup(static_cast<UInt16>(dataGroup)) {}
#else
        m_dataGroup(static_cast<UInt16>(dataGroup)), m_dat(dat) {}
#endif

    /// Group Group Data group of the Dat.
    constexpr DataGroup dataGroup() const noexcept{
        return static_cast<DataGroup>(m_dataGroup);
    }

    /// Dat, an operation argument type.
    constexpr Dat dat() const noexcept{
        return m_dat;
    }

private:
#if defined(TWPP_DETAIL_ENDIAN_LITTLE)
    Dat m_dat;
    UInt16 m_dataGroup;
#else
    UInt16 m_dataGroup;
    Dat m_dat;
#endif

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_SUPPORTEDDAT_HPP
