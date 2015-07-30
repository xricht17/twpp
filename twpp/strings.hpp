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

#ifndef TWPP_DETAIL_FILE_STRINGS_HPP
#define TWPP_DETAIL_FILE_STRINGS_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

// specialization for twain strings
// on mac os, these strings do not contain null terminator
// instead, the first byte contains the length
template<std::size_t arraySize, std::size_t... i>
struct FixedArrayData<char, arraySize, IndexList<i...> > {

    template<std::size_t inputSize>
    constexpr FixedArrayData(const char(& arr)[inputSize]) noexcept :
        m_arr{
#if defined(TWPP_DETAIL_OS_MAC)
            unsignedToSigned<unsigned char>(inputSize - 1),
#endif
            FixedArrayFlat<char, arraySize>(arr)[i]...
        }{}

    constexpr FixedArrayData() noexcept :
        m_arr(){}

    char m_arr[arraySize];

};

// specialization for twain strings
// on mac os, these strings do not contain null terminator
// instead, the first byte contains the length
// so we provide one less index for the fixed array
// on windows, its element is zero-initialized due to it not being specified
// on mac os, the first byte contains the length, so the index is not used anyway
template<std::size_t arraySize>
struct FixedArray<char, arraySize> : public FixedArrayData<char, arraySize, typename Indexes<arraySize - 1>::Result> {

    typedef FixedArrayData<char, arraySize, typename Indexes<arraySize - 1>::Result> ParentType;
    typedef char Array[arraySize];

    constexpr FixedArray() noexcept :
        ParentType(){}

    template<std::size_t inputSize>
    constexpr FixedArray(const char(& arr)[inputSize]) noexcept :
        ParentType(arr){

        static_assert(inputSize <= arraySize, "string literal is too long");
    }

    constexpr const Array& array() const noexcept{
        return ParentType::m_arr;
    }

    Array& array() noexcept{
        return ParentType::m_arr;
    }

};

/// TWAIN string template.
/// \tparam arraySize String capacity, including either null byte, or length byte (Mac OS).
template<std::size_t arraySize>
class Str : private FixedArray<char, arraySize>{

    typedef FixedArray<char, arraySize> DataType;

public:
    typedef const char* const_iterator;
    typedef char* iterator;

    /// Maximal number of characters this string may hold.
    /// Excluding null byte (length byte).
    static constexpr UInt32 maxSize() noexcept{
        return arraySize - 1;
    }

    static_assert(maxSize() <= std::numeric_limits<unsigned char>::max(), "string type exceeds allowed sizes");


    /// Creates an empty, zero-initialized string.
    constexpr Str() noexcept{}

    /// Creates a compile-time string from string literal (or char array).
    /// \tparam inputSize Size of the string literal including null terminator.
    /// \param str The string literal.
    template<std::size_t inputSize>
    constexpr Str(const char(& str)[inputSize]) noexcept :
        DataType(str){

        static_assert(inputSize <= arraySize, "string literal is too long");
    }

    /// Alias to length().
    constexpr UInt32 size() const noexcept{
        return length();
    }

    /// Length of the string (number of 8-bit characters).
    /// O(1) on Mac OS, O(n) anywhere else.
    constexpr UInt32 length() const noexcept{
#if defined(TWPP_DETAIL_OS_MAC)
        return static_cast<unsigned const char>(this->array()[0]);
#else
        return strLen(data());
#endif
    }

    /// Pointer to constant data.
    /// On Mac OS, the data is NOT null-terminated,
    /// and points to the first character after size byte.
    /// This operation is unsafe, and its use may not be platform-independent.
    constexpr const char* data() const noexcept{
#if defined(TWPP_DETAIL_OS_MAC)
        return this->array() + 1;
#else
        return this->array();
#endif
    }

    /// Pointer to data.
    /// On Mac OS, the data is NOT null-terminated,
    /// and points to the first character after size byte.
    /// This operation is unsafe, and its use may not be platform-independent.
    char* data() noexcept{
#if defined(TWPP_DETAIL_OS_MAC)
        return this->array() + 1;
#else
        return this->array();
#endif
    }

    /// Sets string data.
    /// Copies as much data as possible, discarding the rest.
    /// The data needn't be null terminated.
    /// \param str Data to copy.
    /// \param size Maximal number of bytes to copy.
    /// \return Number of bytes copied - the new length of this string.
    UInt32 setData(const char* data, UInt32 size) noexcept{
        char* arr = this->data();
        UInt32 i = 0;

        auto maxLen = std::min(maxSize(), size);
        for ( ; i < maxLen && *data; i++, data++){
            arr[i] = *data;
        }

#if defined(TWPP_DETAIL_OS_MAC)
        *reinterpret_cast<unsigned char*>(this->array()) = static_cast<unsigned char>(i);
#else
        arr[i] = '\0';
#endif

        return i;
    }

    /// Sets string data.
    /// Copies as much data as possible, discarding the rest.
    /// The string must be null terminated.
    /// \param str String to copy.
    /// \return Number of characters copied - the new length of this string.
    UInt32 setData(const char* str) noexcept{
        return setData(str, maxSize());
    }

    /// Sets string data from container (e.g. std::string).
    /// Copies as much data as possible, discarding the rest.
    /// The string needn't be null terminated.
    /// \tparam Contaier Container type.
    /// \param cont Container with data to be copied.
    /// \return Number of characters copied - the new length of this string.
    template<typename Container, typename = typename std::enable_if<std::is_same<typename Container::value_type, char>::value>::type>
    UInt32 setData(const Container& cont) noexcept{
        return setData(cont.data(), static_cast<UInt32>(std::min<typename Container::size_type>(cont.size(), maxSize())));
    }

    char operator[](UInt32 i) const noexcept{
        return data()[i];
    }

    char& operator[](UInt32 i) noexcept{
        return data()[i];
    }

    iterator begin() noexcept{
        return data();
    }

    constexpr const_iterator begin() const noexcept{
        return cbegin();
    }

    constexpr const_iterator cbegin() const noexcept{
        return data();
    }

    iterator end() noexcept{
        return data() + length();
    }

    constexpr const_iterator end() const noexcept{
        return cend();
    }

    constexpr const_iterator cend() const noexcept{
        return data() + length();
    }

    std::string string() const{
        return std::string(cbegin(), cend());
    }

};

}

template<std::size_t sizeA, std::size_t sizeB>
constexpr bool operator==(const Detail::Str<sizeA>& a, const Detail::Str<sizeB>& b) noexcept{
    // length() is O(1) on mac os, O(n) anywhere else
#if defined(TWPP_DETAIL_OS_MAC)
    return a.length() == b.length() && Detail::strCmp(a.data(), b.data()) == 0;
#else
    return Detail::strCmp(a.data(), b.data()) == 0;
#endif
}

template<std::size_t sizeA, std::size_t sizeB>
constexpr bool operator<(const Detail::Str<sizeA>& a, const Detail::Str<sizeB>& b) noexcept{
    return Detail::strCmp(a.data(), b.data()) < 0;
}

template<std::size_t sizeA, std::size_t sizeB>
constexpr bool operator>(const Detail::Str<sizeA>& a, const Detail::Str<sizeB>& b) noexcept{
    return Detail::strCmp(a.data(), b.data()) > 0;
}

template<std::size_t sizeA, std::size_t sizeB>
constexpr bool operator!=(const Detail::Str<sizeA>& a, const Detail::Str<sizeB>& b) noexcept{
    return !(a == b);
}

template<std::size_t sizeA, std::size_t sizeB>
constexpr bool operator<=(const Detail::Str<sizeA>& a, const Detail::Str<sizeB>& b) noexcept{
    return !(a > b);
}

template<std::size_t sizeA, std::size_t sizeB>
constexpr bool operator>=(const Detail::Str<sizeA>& a, const Detail::Str<sizeB>& b) noexcept{
    return !(a < b);
}

/// TWAIN string that can contain up to 33 characters (bytes).
typedef Detail::Str<34> Str32;

/// TWAIN string that can contain up to 65 characters (bytes).
typedef Detail::Str<66> Str64;

/// TWAIN string that can contain up to 129 characters (bytes).
typedef Detail::Str<130> Str128;

/// TWAIN string that can contain up to 255 characters (bytes).
typedef Detail::Str<256> Str255;

}


#endif // TWPP_DETAIL_FILE_STRINGS_HPP

