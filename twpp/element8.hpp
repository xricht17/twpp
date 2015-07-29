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

#ifndef TWPP_DETAIL_FILE_ELEMENT8_HPP
#define TWPP_DETAIL_FILE_ELEMENT8_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Element in a palette consisting of 3 parts (RGB, CMY, ...)
/// in the order of the type alphabetic representation.
class Element8 {

public:
    /// Creates zero-initialized element.
    constexpr Element8() noexcept :
        m_index(0), m_channel1(0), m_channel2(0), m_channel3(0){}

    /// Creates zero-initialized element with specified index.
    explicit constexpr Element8(UInt8 index) noexcept :
        m_index(index), m_channel1(0), m_channel2(0), m_channel3(0){}

    /// Creates element with set channels.
    constexpr Element8(
            UInt8 channel1,
            UInt8 channel2,
            UInt8 channel3
    ) noexcept :
        m_index(0), m_channel1(channel1), m_channel2(channel2),
        m_channel3(channel3){}

    /// Creates element with set channels at index.
    constexpr Element8(
            UInt8 index,
            UInt8 channel1,
            UInt8 channel2,
            UInt8 channel3
    ) noexcept :
        m_index(index), m_channel1(channel1), m_channel2(channel2),
        m_channel3(channel3){}

    /// Index of the element in palette.
    constexpr UInt8 index() const noexcept{
        return m_index;
    }

    /// Sets index of the element in palette.
    void setIndex(UInt8 index) noexcept{
        m_index = index;
    }

    /// Channel 1 information.
    constexpr UInt8 channel1() const noexcept{
        return m_channel1;
    }

    /// Sets channel 1 information.
    void setChannel1(UInt8 channel1) noexcept{
        m_channel1 = channel1;
    }

    /// Channel 2 information.
    constexpr UInt8 channel2() const noexcept{
        return m_channel2;
    }

    /// Sets channel 2 information.
    void setChannel2(UInt8 channel2) noexcept{
        m_channel2 = channel2;
    }

    /// Channel 3 information.
    constexpr UInt8 channel3() const noexcept{
        return m_channel3;
    }

    /// Sets channel 3 information.
    void setChannel3(UInt8 channel3) noexcept{
        m_channel3 = channel3;
    }

private:
    UInt8 m_index;
    UInt8 m_channel1;
    UInt8 m_channel2;
    UInt8 m_channel3;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_ELEMENT8_HPP
