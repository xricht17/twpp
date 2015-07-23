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

#ifndef TWPP_DETAIL_FILE_AUDIO_HPP
#define TWPP_DETAIL_FILE_AUDIO_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Information about current audio transfer.
/// ArgType::AudioInfo
class AudioInfo {

public:
    /// Creates empty audio info.
    constexpr AudioInfo() noexcept :
        m_name(), m_reserved(){}

    /// Creates audio info with set name of audio data.
    explicit constexpr AudioInfo(const Str255& name, UInt32 reserved = 0) noexcept :
        m_name(name), m_reserved(reserved){}

    /// Name of audio data.
    constexpr const Str255& name() const noexcept{
        return m_name;
    }

    /// Name of audio data.
    Str255& name() noexcept{
        return m_name;
    }

    constexpr UInt32 reserved() const noexcept{
        return m_reserved;
    }

    void setReserved(UInt32 reserved) noexcept{
        m_reserved = reserved;
    }

private:
    Str255 m_name;
    UInt32 m_reserved;

};

/// Owner of audio transfer handle.
class AudioNativeXfer {

public:
    template<typename T>
    using Data = Detail::Lock<typename std::decay<T>::type>;

    template<typename T>
    using ConstData = Detail::Lock<const typename std::decay<T>::type>;


    /// Creates an empty handle owner.
    constexpr AudioNativeXfer() noexcept :
        m_handle(){}

    /// Creates a memory area of desired size for audio native transfer.
    /// \throw std::bad_alloc
    explicit AudioNativeXfer(UInt32 size) :
        m_handle(Detail::alloc(size)){}

    /// Audio data.
    template<typename T = void>
    Data<T> data() noexcept{
        return m_handle.lock<typename std::decay<T>::type>();
    }

    /// Audio data.
    template<typename T = void>
    ConstData<T> data() const noexcept{
        return m_handle.lock<const typename std::decay<T>::type>();
    }

    /// Releases the owned handle.
    /// The user becomes responsible for freeing the handle.
    Handle release() noexcept{
        return m_handle.release();
    }

private:
    Detail::UniqueHandle m_handle;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_AUDIO_HPP

