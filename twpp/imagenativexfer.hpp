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

#ifndef TWPP_DETAIL_FILE_IMAGENATIVEXFER_HPP
#define TWPP_DETAIL_FILE_IMAGENATIVEXFER_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure holding native transfer image handle.
class ImageNativeXfer {

public:
    template<typename T>
    using Data = Detail::Lock<typename std::decay<T>::type>;

    template<typename T>
    using ConstData = Detail::Lock<const typename std::decay<T>::type>;


    /// Creates empty, invalid native transfer.
    constexpr ImageNativeXfer() noexcept :
        m_handle(){}

    /// Creates a new ImageNativeXfer object from a handle.
    /// The ownership of the handle is taken over.
    explicit ImageNativeXfer(Handle h) :
        m_handle(h){}

    /// Creates uninitialized native image with defines size in bytes.
    /// \throw std::bad_alloc
    explicit ImageNativeXfer(UInt32 size) :
        m_handle(Detail::alloc(size)){}

    /// Data of this native transfer.
    /// Actual type depends on system and source.
    /// Windows sources use BMP format without file header, version varies.
    /// Linux uses TIFF, version varies.
    /// Mac uses QuickDraw Picture.
    template<typename T = void>
    Data<T> data() noexcept{
        return m_handle.lock<typename std::decay<T>::type>();
    }

    /// Data of this native transfer.
    /// Actual type depends on system and source.
    /// Windows sources use BMP format without file header, version varies.
    /// Linux uses TIFF, version varies.
    /// Mac uses QuickDraw Picture.
    template<typename T = void>
    ConstData<T> data() const noexcept{
        return m_handle.lock<const typename std::decay<T>::type>();
    }

    operator bool() const noexcept{
        return m_handle;
    }

    /// Releases the contained handle, making user responsible for freeing it.
    Handle release() noexcept{
        return m_handle.release();
    }

private:
    Detail::UniqueHandle m_handle;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_IMAGENATIVEXFER_HPP

