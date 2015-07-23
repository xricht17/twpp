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

#ifndef TWPP_DETAIL_FILE_SETUPMEMXFER_HPP
#define TWPP_DETAIL_FILE_SETUPMEMXFER_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure for setting up memory transfer.
class SetupMemXfer {

public:
    /// Creates zero-initialized instance.
    constexpr SetupMemXfer() noexcept :
        m_minSize(0), m_maxSize(0), m_prefSize(0){}

    /// Creates an initialized instance with set minimal, maximal and preferred sizes.
    /// Must be true, or the behaviour is undefined: minSize <= preferredSize <= maxSize
    constexpr SetupMemXfer(
            UInt32 minSize,
            UInt32 maxSize,
            UInt32 preferredSize
    ) noexcept :
        m_minSize(minSize), m_maxSize(maxSize), m_prefSize(preferredSize){}

    /// Minimal supported buffer size in bytes.
    constexpr UInt32 minSize() const noexcept{
        return m_minSize;
    }

    /// Sets minimal supported buffer size in bytes.
    void setMinSize(UInt32 minSize) noexcept{
        m_minSize = minSize;
    }

    /// Maximal supported buffer size in bytes.
    constexpr UInt32 maxSize() const noexcept{
        return m_maxSize;
    }

    /// Sets maximal supported buffer size in bytes.
    void maxSize(UInt32 maxSize) noexcept{
        m_maxSize = maxSize;
    }

    /// Preferred buffer size in bytes.
    constexpr UInt32 preferredSize() const noexcept{
        return m_prefSize;
    }

    /// Sets preferred buffer size in bytes.
    void setPreferredSize(UInt32 prefSize) noexcept{
        m_prefSize = prefSize;
    }

private:
    UInt32 m_minSize;
    UInt32 m_maxSize;
    UInt32 m_prefSize;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_SETUPMEMXFER_HPP
