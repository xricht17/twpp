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

#ifndef TWPP_DETAIL_FILE_FRAME_HPP
#define TWPP_DETAIL_FILE_FRAME_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Section of an image to retrieve.
class Frame {

public:
    /// Creates zero-initialized frame.
    constexpr Frame() noexcept{}

    /// Creates frame with set top-left and bottom-right corners.
    constexpr Frame(Fix32 left, Fix32 top, Fix32 right, Fix32 bottom) noexcept :
        m_left(left), m_top(top), m_right(right), m_bottom(bottom){}

    /// Left position of the image frame.
    constexpr Fix32 left() const noexcept{
        return m_left;
    }

    /// Sets left position of the image frame.
    void setLeft(Fix32 left) noexcept{
        m_left = left;
    }

    /// Top position of the image frame.
    constexpr Fix32 top() const noexcept{
        return m_top;
    }

    /// Sets top position of the image frame.
    void setTop(Fix32 top) noexcept{
        m_top = top;
    }

    /// Right position of the image frame.
    constexpr Fix32 right() const noexcept{
        return m_right;
    }

    /// Sets right position of the image frame.
    void setRight(Fix32 right) noexcept{
        m_right = right;
    }

    /// Bottom position of the image frame.
    constexpr Fix32 bottom() const noexcept{
        return m_bottom;
    }

    /// Sets bottom position of the image frame.
    void setBottom(Fix32 bottom) noexcept{
        m_bottom = bottom;
    }

private:
    Fix32 m_left;
    Fix32 m_top;
    Fix32 m_right;
    Fix32 m_bottom;

};
TWPP_DETAIL_PACK_END

static constexpr inline bool operator==(const Frame& a, const Frame& b) noexcept{
    return a.left() == b.left() && a.top() == b.top() && a.right() == b.right() && a.bottom() == b.bottom();
}

static constexpr inline bool operator!=(const Frame& a, const Frame& b) noexcept{
    return !(a == b);
}

}

#endif // TWPP_DETAIL_FILE_FRAME_HPP

