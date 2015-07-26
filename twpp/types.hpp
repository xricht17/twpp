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

#ifndef TWPP_DETAIL_FILE_TYPES_HPP
#define TWPP_DETAIL_FILE_TYPES_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
typedef std::uintptr_t UIntPtr;
typedef std::uint8_t UInt8;
typedef std::uint16_t UInt16;
typedef std::uint32_t UInt32;
typedef std::int8_t Int8;
typedef std::int16_t Int16;
typedef std::int32_t Int32;

/// Boolean value.
/// Implemented as a class to provide better type safety.
class Bool {

public:
    constexpr Bool(bool value = false) noexcept :
        m_value(value){}

    constexpr operator bool() const noexcept{
        return m_value;
    }

private:
    Int16 m_value;

};

/// Handle to memory area.
/// Implemented as a class to provide better type safety.
class Handle {

public:
    typedef Detail::RawHandle Raw;

    constexpr explicit Handle(Raw raw = Raw()) noexcept :
        m_raw(raw){}

    /// Underlying OS-dependent handle.
    constexpr Raw raw() const noexcept{
        return m_raw;
    }

    constexpr operator bool() const noexcept{
        return m_raw != Raw();
    }

private:
    Raw m_raw;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_TYPES_HPP

