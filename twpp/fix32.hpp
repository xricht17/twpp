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

#ifndef TWPP_DETAIL_FILE_FIX32_HPP
#define TWPP_DETAIL_FILE_FIX32_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

static constexpr inline Int32 floatToValue(float val){
    return static_cast<Int32>(
        (val >= 0.0f) ?
        (val * 65536.0f + 0.5f) :
        (val * 65536.0f - 0.5f)
    );
}

static constexpr inline Int16 floatToWhole(float val){
    return static_cast<Int16>(floatToValue(val) >> 16);
}

static constexpr inline UInt16 floatToFrac(float val){
    return static_cast<UInt16>(floatToValue(val) & 0xFFFF);
}

}

TWPP_DETAIL_PACK_BEGIN
/// TWAIN fixed point fractional type.
/// The fractional part has resolution of 1/65536.
class Fix32 {

public:
    /// Creates zero-initialized fixed type.
    constexpr Fix32() noexcept :
        m_whole(0), m_frac(0){}

    /// Creates fixed type from float at compile time if possible.
    constexpr Fix32(float value) noexcept :
        m_whole(Detail::floatToWhole(value)), m_frac(Detail::floatToFrac(value)){}

    /// Creates fixed type from whole and fractional parts.
    /// The fractional part has resolution of 1/65536.
    constexpr Fix32(Int16 whole, UInt16 frac) noexcept :
        m_whole(whole), m_frac(frac){}


    /// Whole part of this fixed type.
    constexpr Int16 whole() const noexcept{
        return m_whole;
    }

    /// Sets whole part of this fixed type.
    void setWhole(Int16 whole) noexcept{
        m_whole = whole;
    }

    /// Fractional part of this fixed type.
    /// Resolution of 1/65536.
    constexpr UInt16 frac() const noexcept{
        return m_frac;
    }

    /// Sets fractional part of this fixed type.
    /// Resolution of 1/65536.
    void setFrac(UInt16 frac) noexcept{
        m_frac = frac;
    }

    explicit constexpr operator float() const noexcept{
        return toFloat();
    }

    constexpr float toFloat() const noexcept{
        return m_whole + m_frac / 65536.0f;
    }

    constexpr Fix32 operator-() const noexcept{
        return -toFloat();
    }

private:
    Int16 m_whole;
    UInt16 m_frac;

};
TWPP_DETAIL_PACK_END

namespace Detail {

static inline constexpr Fix32 fix32AddHelper(Int32 frac, Int16 whole){
    return frac < 65536 ? Fix32(whole, frac) : Fix32(whole + 1, frac - 65536);
}

static inline constexpr Fix32 fix32SubHelper(Int32 frac, Int16 whole){
    return frac >= 0 ? Fix32(whole, frac) : Fix32(whole - 1, frac + 65536);
}

}

static inline constexpr bool operator>(Fix32 a, Fix32 b) noexcept{
    return a.whole() > b.whole() || (a.whole() == b.whole() && a.frac() > b.frac());
}

static inline constexpr bool operator<(Fix32 a, Fix32 b) noexcept{
    return a.whole() < b.whole() || (a.whole() == b.whole() && a.frac() < b.frac());
}

static inline constexpr bool operator>=(Fix32 a, Fix32 b) noexcept{
    return !(a < b);
}

static inline constexpr bool operator<=(Fix32 a, Fix32 b) noexcept{
    return !(a > b);
}

static inline constexpr bool operator==(Fix32 a, Fix32 b) noexcept{
    return a.whole() == b.whole() && a.frac() == b.frac();
}

static inline constexpr bool operator!=(Fix32 a, Fix32 b) noexcept{
    return !(a == b);
}

static inline constexpr Fix32 operator+(Fix32 a, Fix32 b) noexcept{
    return Detail::fix32AddHelper(static_cast<Int32>(a.frac()) + b.frac(), a.whole() + b.whole());
}

static inline constexpr Fix32 operator-(Fix32 a, Fix32 b) noexcept{
    return Detail::fix32SubHelper(static_cast<Int32>(a.frac()) - b.frac(), a.whole() - b.whole());
}

static inline constexpr Fix32 operator*(Fix32 a, Fix32 b) noexcept{
    return Fix32(static_cast<float>(a) * static_cast<float>(b));
}

static inline constexpr Fix32 operator/(Fix32 a, Fix32 b) noexcept{ // wonder about zero b
    return Fix32(static_cast<float>(a) / static_cast<float>(b));
}

static inline Fix32& operator+=(Fix32& a, Fix32 b) noexcept{
    return a = a + b;
}

static inline Fix32& operator-=(Fix32& a, Fix32 b) noexcept{
    return a = a - b;
}

static inline Fix32& operator*=(Fix32& a, Fix32 b) noexcept{
    return a = a * b;
}

static inline Fix32& operator/=(Fix32& a, Fix32 b) noexcept{ // wonder about zero b
    return a = a / b;
}

namespace Literals {

static inline constexpr Fix32 operator "" _fix(long double val) noexcept{
    return Fix32(static_cast<float>(val));
}

static inline constexpr Fix32 operator "" _fix(unsigned long long val) noexcept{
    return Fix32(static_cast<float>(val));
}

}

}

#endif // TWPP_DETAIL_FILE_FIX32_HPP

