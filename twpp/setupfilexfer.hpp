/*

The MIT License (MIT)

Copyright (c) 2015-2017 Martin Richter

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

#ifndef TWPP_DETAIL_FILE_SETUPFILEXFER_HPP
#define TWPP_DETAIL_FILE_SETUPFILEXFER_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure for setting up file transfer.
class SetupFileXfer {

public:
    /// Creates zero-initialized instance.
    constexpr SetupFileXfer() noexcept :
        m_format(ImageFileFormat::Tiff), m_volRefNum(0){}

    /// Creates instance with set file path and format.
    /// And volume reference number on Mac OS.
    /// \param filePath Path to transfered file.
    /// \param format File format.
    /// \param vrn Volume reference number. Mac OS only.
    constexpr SetupFileXfer(
            const Str255& filePath,
            ImageFileFormat format,
            Int16 vrn
#if defined(TWPP_DETAIL_OS_WIN) || defined(TWPP_DETAIL_OS_LINUX)
                = -1
#elif !defined(TWPP_DETAIL_OS_MAC)
#   error "Volume reference number for your platform here"
#endif
    ) noexcept :
        m_filePath(filePath), m_format(format),
        m_volRefNum(vrn){}

    /// Path to transfered file.
    constexpr const Str255& filePath() const noexcept{
        return m_filePath;
    }

    /// Sets path to transfered file.
    void setFilePath(const Str255& filePath) noexcept{
        m_filePath = filePath;
    }

    /// Format of the transfered file.
    constexpr ImageFileFormat format() const noexcept{
        return m_format;
    }

    /// Sets format of the transfered file.
    void setFormat(ImageFileFormat format) noexcept{
        m_format = format;
    }

    /// Volume reference number.
    /// Mac OS only.
    constexpr Int16 volumeReferenceNumber() const noexcept{
        return m_volRefNum;
    }

    /// Sets volume reference number.
    /// Mac OS only.
    void setVolumeReferenceNumber(Int16 volumeReferenceNumber) noexcept{
        m_volRefNum = volumeReferenceNumber;
    }

private:
    Str255 m_filePath;
    ImageFileFormat m_format;
    Int16 m_volRefNum;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_SETUPFILEXFER_HPP
