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

#ifndef TWPP_DETAIL_FILE_IMAGEINFO_HPP
#define TWPP_DETAIL_FILE_IMAGEINFO_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Contains information about transfered image.
class ImageInfo {

    typedef Detail::FixedArray<Int16, 8> BitsPerSampleImpl;

public:
    typedef Int16 BitsPerSample[8];

    /// Creates zero-initialized info.
    constexpr ImageInfo() noexcept :
        m_imgWidth(0), m_imgHeight(0), m_spp(0), m_bps(), m_bpp(0),
        m_planar(0), m_pixelType(PixelType::BlackWhite), m_compression(Compression::None){}

    /// Creates info with supplied values.
    template<std::size_t inputSize>
    constexpr ImageInfo(
            Fix32 xResolution,
            Fix32 yResolution,
            Int32 width,
            Int32 height,
            Int16 samplesPerPixel,
            const Int16(& bitsPerSample)[inputSize],
            Int16 bitsPerPixel,
            Bool planar,
            PixelType pixelType,
            Compression compression
    ) noexcept :
        m_xres(xResolution), m_yres(yResolution), m_imgWidth(width), m_imgHeight(height),
        m_spp(samplesPerPixel), m_bps(bitsPerSample), m_bpp(bitsPerPixel), m_planar(planar),
        m_pixelType(pixelType), m_compression(compression){}

    /// X-axis resolution of the image.
    constexpr Fix32 xResolution() const noexcept{
        return m_xres;
    }

    /// Sets x-axis resolution of the image.
    void setXResolution(Fix32 xres) noexcept{
        m_xres = xres;
    }

    /// Y-axis resolution of the image.
    constexpr Fix32 yResolution() const noexcept{
        return m_yres;
    }

    /// Sets y-axis resolution of the image.
    void setYResolution(Fix32 yres) noexcept{
        m_yres = yres;
    }

    /// Image width in pixels.
    constexpr Int32 width() const noexcept{
        return m_imgWidth;
    }

    /// Sets image width in pixels.
    void setWidth(Int32 width) noexcept{
        m_imgWidth = width;
    }

    /// Image height in pixels.
    constexpr Int32 height() const noexcept{
        return m_imgHeight;
    }

    /// Sets image height in pixels.
    void setHeight(Int32 height) noexcept{
        m_imgHeight = height;
    }

    /// Samples per single pixel.
    constexpr Int16 samplesPerPixel() const noexcept{
        return m_spp;
    }

    /// Sets samples per single pixel.
    void setSamplesPerPixel(Int16 spp) noexcept{
        m_spp = spp;
    }

    /// Array of bits per sample.
    /// Contains `samplesPerPixel` entries.
    constexpr const BitsPerSample& bitsPerSample() const noexcept{
        return m_bps.array();
    }

    /// Array of bits per sample.
    /// Contains `samplesPerPixel` entries.
    BitsPerSample& bitsPerSample() noexcept{
        return m_bps.array();
    }

    /// Total number of bits per pixel.
    /// This should be true: bitsPerPixel = SUM[i=0..samplesPerPixel-1](bitsPerSample[i])
    constexpr Int16 bitsPerPixel() const noexcept{
        return m_bpp;
    }

    /// Sets total number of bits per pixel.
    /// This should be true: bitsPerPixel = SUM[i=0..samplesPerPixel-1](bitsPerSample[i])
    void setBitsPerPixel(Int16 bpp) noexcept{
        m_bpp = bpp;
    }

    /// Whether the image is planar (consists of several sample planes) or is chunky
    /// (samples are transferes in one plane and are interlaced).
    constexpr Bool planar() const noexcept{
        return m_planar;
    }

    /// Sets whether the image is planar (consists of several sample planes) or is chunky
    /// (samples are transferes in one plane and are interlaced).
    void setPlanar(Bool planar) noexcept{
        m_planar = planar;
    }

    /// The type of image.
    constexpr PixelType pixelType() const noexcept{
        return m_pixelType;
    }

    /// Sets the type of image.
    void setPixelType(PixelType pixelType) noexcept{
        m_pixelType = pixelType;
    }

    /// Image compression.
    constexpr Compression compression() const noexcept{
        return m_compression;
    }

    /// Sets image compression.
    void compression(Compression compression) noexcept{
        m_compression = compression;
    }

private:
    Fix32 m_xres;
    Fix32 m_yres;
    Int32 m_imgWidth;
    Int32 m_imgHeight;
    Int16 m_spp;
    BitsPerSampleImpl m_bps;
    Int16 m_bpp;
    Bool m_planar;
    PixelType m_pixelType;
    Compression m_compression;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_IMAGEINFO_HPP

