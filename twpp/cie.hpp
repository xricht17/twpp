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

#ifndef TWPP_DETAIL_FILE_CIE_HPP
#define TWPP_DETAIL_FILE_CIE_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Part of CieColor structure.
class CiePoint {

public:
    /// Creates zero-initialized cie point.
    constexpr CiePoint() noexcept :
        m_x(), m_y(), m_z(){}

    /// Creates cie point with desired values.
    constexpr CiePoint(Fix32 x, Fix32 y, Fix32 z) noexcept :
        m_x(x), m_y(y), m_z(z){}

    /// X value of CIE space.
    constexpr Fix32 x() const noexcept{
        return m_x;
    }

    /// Y value of CIE space.
    constexpr Fix32 y() const noexcept{
        return m_y;
    }

    /// Z value of CIE space.
    constexpr Fix32 z() const noexcept{
        return m_z;
    }

    /// Sets x value of CIE space.
    void setX(Fix32 x) noexcept{
        m_x = x;
    }

    /// Sets y value of CIE space.
    void setY(Fix32 y) noexcept{
        m_y = y;
    }

    /// Sets z value of CIE space.
    void setZ(Fix32 z) noexcept{
        m_z = z;
    }

private:
    Fix32 m_x;
    Fix32 m_y;
    Fix32 m_z;

};

/// Defines parameters for channel transformations.
/// Part of TransformStage.
class DecodeFunction {

public:
    /// Creates zero-initialized decode function.
    constexpr DecodeFunction() noexcept{}

    /// Creates initialized decode function.
    constexpr DecodeFunction(
            Fix32 startIn,
            Fix32 breakIn,
            Fix32 endIn,
            Fix32 startOut,
            Fix32 breakOut,
            Fix32 endOut,
            Fix32 gamma,
            Fix32 sampleCount
    ) noexcept :
        m_startIn(startIn), m_breakIn(breakIn), m_endIn(endIn),
        m_startOut(startOut), m_breakOut(breakOut), m_endOut(endOut),
        m_gamma(gamma), m_sampleCount(sampleCount){}

    /// Starting input value.
    constexpr Fix32 startIn() const noexcept{
        return m_startIn;
    }

    /// Sets starting input value.
    void setStartIn(Fix32 startIn) noexcept{
        m_startIn = startIn;
    }

    /// Ending input value.
    constexpr Fix32 breakIn() const noexcept{
        return m_breakIn;
    }

    /// Sets ending input value.
    void setBreakIn(Fix32 breakIn) noexcept{
        m_breakIn = breakIn;
    }

    /// Input value when to switch from linear to gamma transformation.
    constexpr Fix32 endIn() const noexcept{
        return m_endIn;
    }

    /// Sets input value when to switch from linear to gamma transformation.
    void setEndIn(Fix32 endIn) noexcept{
        m_endIn = endIn;
    }

    /// Starting output value.
    constexpr Fix32 startOut() const noexcept{
        return m_startOut;
    }

    /// Sets starting output value.
    void setStartOut(Fix32 startOut) noexcept{
        m_startOut = startOut;
    }

    /// Ending output value.
    constexpr Fix32 breakOut() const noexcept{
        return m_breakOut;
    }

    /// Sets ending output value.
    void setBreakOut(Fix32 breakOut) noexcept{
        m_breakOut = breakOut;
    }

    /// Output value when to switch from linear to gamma transformation.
    constexpr Fix32 endOut() const noexcept{
        return m_endOut;
    }

    /// Sets output value when to switch from linear to gamma transformation.
    void setEndOut(Fix32 endOut) noexcept{
        m_endOut = endOut;
    }

    /// Constant, exponential used in gamma funciton.
    constexpr Fix32 gamma() const noexcept{
        return m_gamma;
    }

    /// Sets constant, exponential used in gamma funciton.
    void setGamma(Fix32 gamma) noexcept{
        m_gamma = gamma;
    }

    /// Number of samples in lookup table.
    constexpr Fix32 sampleCount() const noexcept{
        return m_sampleCount;
    }

    /// Sets number of samples in lookup table.
    void setSampleCount(Fix32 sampleCount) noexcept{
        m_sampleCount = sampleCount;
    }

private:
    Fix32 m_startIn;
    Fix32 m_breakIn;
    Fix32 m_endIn;
    Fix32 m_startOut;
    Fix32 m_breakOut;
    Fix32 m_endOut;
    Fix32 m_gamma;
    Fix32 m_sampleCount;

};

/// Parameters of ABC or LMN transformations.
/// Refer to manual for more information about members.
class TransformStage {

public:
    typedef std::array<DecodeFunction, 3> Decode;
    typedef std::array<std::array<Fix32, 3>, 3> Mix;

    constexpr TransformStage() noexcept :
        m_decode(), m_mix(){}

    constexpr TransformStage(const Decode& decode) noexcept :
        m_decode(decode), m_mix(){}

    constexpr TransformStage(const Mix& mix) noexcept :
        m_decode(), m_mix(mix){}

    constexpr TransformStage(const Decode& decode, const Mix& mix) noexcept :
        m_decode(decode), m_mix(mix){}

    constexpr const Decode& decode() const noexcept{
        return m_decode;
    }

    Decode& decode() noexcept{
        return m_decode;
    }

    constexpr const Mix& mix() const noexcept{
        return m_mix;
    }

    Mix& mix() noexcept{
        return m_mix;
    }

private:
    Decode m_decode;
    Mix m_mix;

};

namespace Unsupported {

// TODO CieColor
/// Cie color
/// Currently stub, more info required.
struct CieColor {
    UInt16 m_colorSpace;
    Bool m_lowEndian;
    Bool m_deviceDependent;
    Int32 m_versionNumber;
    TransformStage m_stageAbc;
    TransformStage m_stageLmn;
    CiePoint m_whitePoint;
    CiePoint m_blackPoint;
    CiePoint m_whitePaper;
    CiePoint m_blackInk;
    Fix32 m_samples[1]; // <- how many elements? how to use?
};

}

TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_CIE_HPP

