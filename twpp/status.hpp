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

#ifndef TWPP_DETAIL_FILE_STATUS_HPP
#define TWPP_DETAIL_FILE_STATUS_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Additional status information about a performed TWAIN operation.
class Status {

public:
    /// Creates operation status.
    /// \param cond Status condition code.
    /// \param data Additional status data, source-specific.
    constexpr Status(CC cond = CC::Success, UInt16 data = 0) noexcept :
        m_cond(cond), m_data(data){}

    /// Status condition code.
    constexpr CC condition() const noexcept{
        return m_cond;
    }

    /// Sets status condition code.
    void setCondition(CC cc) noexcept{
        m_cond = cc;
    }

    /// Aditional status data, source-specific.
    constexpr UInt16 data() const noexcept{
        return m_data;
    }

    /// Sets aditional status data, source-specific.
    void setData(UInt16 data) noexcept{
        m_data = data;
    }

    constexpr operator CC() const noexcept{
        return m_cond;
    }

    constexpr operator bool() const noexcept{
        return success(m_cond);
    }

    constexpr bool operator==(CC o) const noexcept{return m_cond == o;}
    constexpr bool operator!=(CC o) const noexcept{return m_cond != o;}

    constexpr bool operator==(Status o) const noexcept{return m_cond == o.m_cond && m_data == o.m_data;}
    constexpr bool operator!=(Status o) const noexcept{return m_cond != o.m_cond || m_data != o.m_data;}


private:
    CC m_cond;
    UInt16 m_data;

};

static inline constexpr bool success(Status stat) noexcept{
    return stat;
}

/// Structure for translating status to UTF8 text.
class StatusUtf8 {

public:
    typedef Detail::Lock<const char> ConstString;


    /// Creates a status utf8 without string data.
    StatusUtf8(Status status = Status()) noexcept :
        m_status(status), m_size(0), m_string(){}

    /// Creates a status utf8 containing copy of string data.
    /// The string must be null-terminated.
    /// \tparam inputSize Size of the string including null terminator.
    /// \param str The string, must be null-terminated.
    /// \throw std::bad_alloc
    template<UInt32 inputSize>
    StatusUtf8(Status status, const char(& str)[inputSize]) :
        m_status(status), m_size(inputSize), m_string(Detail::alloc(inputSize)){

        std::copy(str, str + inputSize, string().data());
    }

    /// Creates a new status utf8 containing a copy of the supplied string.
    /// \param status Status to be translated.
    /// \param str Utf-8 string to copy, must be null-terminated.
    /// \throw RangeException When string is too long, could not insert null terminator.
    /// \throw std::bad_alloc
    StatusUtf8(Status status, const char* str) :
        m_status(status), m_size(0), m_string(){

        auto len = strlen(str);
        if (len >= std::numeric_limits<UInt32>::max()){
            throw RangeException();
        }

        m_size = static_cast<UInt32>(len) + 1;
        m_string = Detail::alloc(m_size);
        std::copy(str, str + len + 1, m_string.lock<char>().data());
    }

    /// Creates a new status utf8 containing a copy of the supplied string.
    /// \param status Status to be translated.
    /// \param str Utf-8 string to copy.
    /// \throw RangeException When string is too long, could not insert null terminator.
    /// \throw std::bad_alloc
    StatusUtf8(Status status, const std::string& str) :
        m_status(status), m_size(0), m_string(){

        auto len = str.length();
        if (len >= std::numeric_limits<UInt32>::max()){
            throw RangeException();
        }

        m_size = static_cast<UInt32>(len) + 1;
        m_string = Detail::alloc(m_size);

        auto lock = m_string.lock<char>();
        std::copy(str.cbegin(), str.cend(), lock.data());
        lock[len] = '\0';
    }

    /// Creates a new StatusUtf8 containing a copy of the supplied string.
    /// \param status Status to be translated.
    /// \param str Utf-8 string to copy, null terminator is not required.
    /// \param strSize {Number of bytes to copy including null terminator.
    ///                     Null terminator is inserted automatically.}
    /// \throw RangeException When string is too short to satisfy the requested size.
    /// \throw std::bad_alloc
    StatusUtf8(Status status, const char* str, UInt32 strSize) :
        m_status(status), m_size(0), m_string(){

        auto len = strlen(str);
        if (len < strSize){
            throw RangeException();
        }

        m_size = static_cast<UInt32>(strSize) + 1;
        m_string = Detail::alloc(m_size);

        auto lock = m_string.lock<char>();
        std::copy(str, str + strSize, lock.data());
        lock[strSize] = '\0';
    }

    StatusUtf8(const StatusUtf8&) = delete;
    StatusUtf8& operator=(const StatusUtf8&) = delete;

    StatusUtf8(StatusUtf8&& o) noexcept :
        m_status(o.m_status), m_size(o.m_size), m_string(std::move(o.m_string)){

        o.m_status = Status();
        o.m_size = 0;
    }

    StatusUtf8& operator=(StatusUtf8&& o) noexcept{
        if (&o != this){
            m_status = o.m_status;
            m_size = o.m_size;
            m_string = std::move(o.m_string);

            o.m_status = Status();
            o.m_size = 0;
        }

        return *this;
    }

    /// Returns the interpreted status.
    Status status() const noexcept{
        return m_status;
    }

    /// Sets the status to be interpreted.
    void setStatus(Status status) noexcept{
        m_status = status;
    }

    /// Returns the total number of bytes including null byte.
    UInt32 size() const noexcept{
        return m_string ? m_size : 0;
    }

    /// The UTF8 string itself.
    ConstString string() const noexcept{
        return m_string.lock<const char>();
    }

private:
    Status m_status;
    UInt32 m_size;
    Detail::UniqueHandle m_string;

};

TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_STATUS_HPP

