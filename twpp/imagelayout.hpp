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

#ifndef TWPP_DETAIL_FILE_IMAGELAYOUT_HPP
#define TWPP_DETAIL_FILE_IMAGELAYOUT_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Provides image size and its position on the scanner and information about order of the image.
class ImageLayout {

public:
    /// Creates layout.
    constexpr ImageLayout(
            const Frame& frame = Frame(),
            UInt32 documentNumber = 1,
            UInt32 pageNumber = 1,
            UInt32 frameNumber = 1
    ) noexcept :
        m_frame(frame), m_docNumber(documentNumber),
        m_pageNumber(pageNumber), m_frameNumber(frameNumber){}

    /// The image frame.
    constexpr const Frame& frame() const noexcept{
        return m_frame;
    }

    /// Sets the image frame.
    void setFrame(const Frame& frame) noexcept{
        m_frame = frame;
    }

    /// Number of the document, set by source.
    constexpr UInt32 documentNumber() const noexcept{
        return m_docNumber;
    }

    /// Sets number of the document.
    void setDocumentNumber(UInt32 documentNumber) noexcept{
        m_docNumber = documentNumber;
    }

    /// Number of the page, set by source.
    constexpr UInt32 pageNumber() const noexcept{
        return m_pageNumber;
    }

    /// Sets number of the page.
    void setPageNumber(UInt32 pageNumber) noexcept{
        m_pageNumber = pageNumber;
    }

    /// Number of the frame, set by source.
    constexpr UInt32 frameNumber() const noexcept{
        return m_frameNumber;
    }

    /// Sets number of the frame.
    void setFrameNumber(UInt32 frameNumber) noexcept{
        m_frameNumber = frameNumber;
    }

private:
    Frame m_frame;
    UInt32 m_docNumber;
    UInt32 m_pageNumber;
    UInt32 m_frameNumber;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_IMAGELAYOUT_HPP
