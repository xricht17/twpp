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

#ifndef TWPP_DETAIL_FILE_UTILS_HPP
#define TWPP_DETAIL_FILE_UTILS_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

/// Performs a pointer type cast, suppresses strict aliasing warnings.
/// \tparam T Type of the returned pointer. Must be pointer type (e.g. `char*`).
/// \param ptr Pointer to be cast.
/// \return Cast pointer.
template<typename T>
static constexpr inline T alias_cast(void* ptr) noexcept{
    return reinterpret_cast<T>(ptr);
}

/// Performs a constant pointer type cast, suppresses strict aliasing warnings.
/// \tparam T Type of the returned pointer. Must be pointer type (e.g. `char*`).
/// \param ptr Pointer to be cast.
/// \return Cast pointer.
template<typename T>
static constexpr inline T alias_cast(const void* ptr) noexcept{
    return reinterpret_cast<T>(ptr);
}

/// Suppresses warnings about unused parameters or arguments.
/// \tparam Args List of argument types. No need to specify explicitly.
template<typename... Args>
static constexpr inline void unused(const Args& ...) noexcept{}



// CODE FROM http://www.macieira.org/blog/2011/07/initialising-an-array-with-cx0x-using-constexpr-and-variadic-templates/
// BEGIN
template<std::size_t... Idx> struct IndexList {};

template<typename IndexList, std::size_t Right> struct Append;
template<std::size_t... Left, std::size_t Right>
struct Append<IndexList<Left...>, Right>{ typedef IndexList<Left..., Right> Result; };

template<std::size_t N> struct Indexes {
    typedef typename Append<typename Indexes<N - 1>::Result, N - 1>::Result Result;
};
template<> struct Indexes<0> { typedef IndexList<> Result; };
// END

/// Converts an array of arbitary size to array-like recursive structure of fixed size (at compile time).
/// Provide template specialization if special handling of elements is required, and you do care
/// about their positions - otherwise see FixedArrayData below.
/// \tparam T Element type.
/// \tparam arraySize Number of elements in the fixed array.
template<typename T, std::size_t arraySize>
struct FixedArrayFlat : FixedArrayFlat<T, arraySize - 1> {

    /// The index this structure (with this `arraySize`) holds.
    static constexpr const std::size_t g_index = arraySize - 1;

    /// Performs the conversion from arbiraty-size array to fixed-size structure.
    /// We use left recursion to initialize values of all inherited structures first.
    /// Then the value of this one is initialized, either copied from the input array itself,
    /// or default-initialized in case the array is not large enough.
    /// \tparam inputSize {Size of the input array. If smaller than the fixed array,
    ///                    excessive elements are default-initialized (may be changed in specializations).
    ///                    Providing larger array results in undefined behaviour.}
    /// \param arr The arbitary-size array.
    template<std::size_t inputSize>
    constexpr inline FixedArrayFlat(const T(& arr)[inputSize]) noexcept :
        FixedArrayFlat<T, g_index>(arr), m_val(g_index < inputSize ? arr[g_index] : T()){}

    /// Returns value contained at specific index.
    /// If the index if smaller than the size of the input array, a value is returned
    /// as if the operation was performed on that array. Otherwise a default value
    /// of the type `T` is returned (or anything else a specialization provides).
    /// Behaviour of this operator is undefined if the index equals to or is greater than
    /// the size of the fixed array.
    /// \param i Value index.
    /// \return Value at index.
    constexpr inline T operator[](std::size_t i) noexcept{
        return i == g_index ? m_val : FixedArrayFlat<T, g_index>::operator [](i);
    }

    /// Value held by this structure.
    T m_val;

};

/// Converts an array of arbitary size to array-like recursive structure of fixed size (at compile time).
/// This template specialization terminates the recursion.
/// No need to provide any further specializations.
/// \tparam T Element type.
template<typename T>
struct FixedArrayFlat<T, 0> {

    template<std::size_t inputSize>
    constexpr inline FixedArrayFlat(const T(&)[inputSize]) noexcept{}

    constexpr inline T operator[](std::size_t) noexcept{
        return T();
    }

};


/// Converts an array of arbitary size to array of fixed size at compile time.
/// The job itself is done in the specialization below.
/// \tparam T Element type.
/// \tparam arraySize Number of elements in the fixed array.
/// \tparam IndexList Type holding indexes of the fixed array.
template<typename T, std::size_t arraySize, typename IndexList>
struct FixedArrayData {};

/// Converts an array of arbitary size to array of fixed size at compile time.
/// Provide template specialization if special handling of elements is required, and you
/// don't care about their positions.
/// \tparam T Element type.
/// \tparam arraySize Number of elements in the fixed array.
/// \tparam i Indexes of the fixed array.
template<typename T, std::size_t arraySize, std::size_t... i>
struct FixedArrayData<T, arraySize, IndexList<i...> > {

    /// Performs the conversion from arbiraty-size array to fixed-size array.
    /// Uses FixedArrayFlat to extend the input array to desired size.
    /// \tparam inputSize Size of the input array.
    /// \param arr The input array.
    template<std::size_t inputSize>
    constexpr FixedArrayData(const T(& arr)[inputSize]) noexcept :
        m_arr{FixedArrayFlat<T, arraySize>(arr)[i]...}{}

    /// Creates default-initialized array.
    constexpr FixedArrayData() noexcept :
        m_arr(){}

    /// The fixed array.
    T m_arr[arraySize];

};

/// Compile-time constructible fixed-size array of type `T` and length `arraySize`.
/// The array can be constructed from variable-sized array
/// of up to `arraySize` elements at compile time.
/// \tparam T Element type.
/// \tparam arraySize Number of elements in the array.
template<typename T, std::size_t arraySize>
struct FixedArray : public FixedArrayData<T, arraySize, typename Indexes<arraySize>::Result> {

    typedef FixedArrayData<T, arraySize, typename Indexes<arraySize>::Result> ParentType;
    typedef T Array[arraySize];

    /// Creates default-initialized array.
    constexpr FixedArray() noexcept :
        ParentType(){}

    /// Creates fixed-size array from variable-size array at compile time.
    /// If the size of input array exceeds `arraySize`, a compile-time error is emited.
    /// \tparam inputSize Number of elements of the input array.
    /// \param arr The input array.
    template<std::size_t inputSize>
    constexpr FixedArray(const T(& arr)[inputSize]) noexcept :
        ParentType(arr){

        static_assert(inputSize <= arraySize, "array literal is too big");
    }

    /// The contained array.
    constexpr const Array& array() const noexcept{
        return ParentType::m_arr;
    }

    /// The contained array.
    Array& array() noexcept{
        return ParentType::m_arr;
    }

};

/// Joins two arrays at compile time.
/// The job itself is done in the specialization below.
/// \tparam T Element type.
/// \tparam lenA Size of the first array.
/// \tparam lenB Size of the second array.
/// \tparam IndexList Type holding indexes of the resulting array.
template<typename T, std::size_t lenA, std::size_t lenB, typename IndexList>
struct ArrayJoinData {};

/// Joins two arrays at compile time.
/// The result of this operation is an array that contains all the elements
/// from the first array immediately followed by all the elements from
/// the second array.
/// \tparam T Element type.
/// \tparam lenA Size of the first array.
/// \tparam lenB Size of the second array.
/// \tparam i Indexes of the resulting array.
template<typename T, std::size_t lenA, std::size_t lenB, std::size_t... i>
struct ArrayJoinData<T, lenA, lenB, IndexList<i...> > {

    /// Performs the join operation.
    /// \param a The first array.
    /// \param b The second array.
    constexpr ArrayJoinData(const T(& a)[lenA], const T(& b)[lenB]) noexcept :
        m_arr{(i < lenA ? a[i] : b[i - lenA])...}{}

    /// The resulting array.
    T m_arr[lenA + lenB];

};

/// Compile-time join operation of two arrays of the same type.
/// \tparam T Element type.
/// \tparam lenA Size of the first array.
/// \tparam lenB Size of the second array.
template<typename T, std::size_t lenA, std::size_t lenB>
struct ArrayJoin : public ArrayJoinData<T, lenA, lenB, typename Indexes<lenA + lenB>::Result> {

    typedef ArrayJoinData<T, lenA, lenB, typename Indexes<lenA + lenB>::Result> ParentType;
    typedef T Array[lenA + lenB];

    /// Performs the join operation.
    /// \param a The first array.
    /// \param b The second array.
    constexpr ArrayJoin(const T(& a)[lenA], const T(& b)[lenB]) noexcept :
        ParentType(a, b){}

    /// The joined array.
    constexpr const Array& array() const noexcept{
        return ParentType::m_arr;
    }

    /// The joined array.
    Array& array() noexcept{
        return ParentType::m_arr;
    }

};

/// Performs compile-time array join operation.
/// This is a helper function, see ArrayJoin and ArrayJoinData for more info.
/// \tparam T Element type.
/// \tparam lenA Size of the first array.
/// \tparam lenB Size of the second array.
/// \param a The first array.
/// \param b The second array.
/// \return The joined array.
template<typename T, std::size_t lenA, std::size_t lenB>
static constexpr inline ArrayJoin<T, lenA, lenB> arrayJoin(const T(& a)[lenA], const T(& b)[lenB]) noexcept{
    return {a, b};
}


/// The loop that checks the suffix at compile time, see endsWith below.
/// Checks are performed from right to left.
/// \tparam T Element type.
/// \tparam arrLen The size of the array to be checked for the suffix.
/// \tparam subLen The size of the suffix array.
/// \param arr The array to be checked for the suffix.
/// \param sub The suffix array.
/// \param endOff Offset from the last element to be checked in this call.
/// \return Whether the suffix is contained.
template<typename T, std::size_t arrLen, std::size_t subLen>
static constexpr inline bool endsWithLoop(const T(& arr)[arrLen], const T(& sub)[subLen], std::size_t endOff){
    return endOff >= subLen || (arr[arrLen - 1 - endOff] == sub[subLen - 1 - endOff] && endsWithLoop(arr, sub, endOff + 1));
}

/// Checks whether the input array contains supplied suffix at compile time.
/// \tparam T Element type.
/// \tparam arrLen The size of the array to be checked for the suffix.
/// \tparam subLen The size of the suffix array.
/// \param arr The array to be checked for the suffix.
/// \param sub The suffix array.
/// \return Whether the suffix is contained.
template<typename T, std::size_t arrLen, std::size_t subLen>
static constexpr inline bool endsWith(const T(& arr)[arrLen], const T(& sub)[subLen]){
    return arrLen >= subLen && endsWithLoop(arr, sub, 0);
}

/// Implementation of compile-time C string length.
/// Uses tail recursion.
/// \param str The string, or its remaining part.
/// \param len Length of the previous, already processed, part of the string.
/// \return Length of the string.
static constexpr inline std::size_t strLenImpl(const char* str, std::size_t len = 0) noexcept{
    return *str == '\0' ? len : strLenImpl(str + 1, len + 1);
}

/// Compile-time C string length.
/// \param str The string.
/// \return Length of the string.
static constexpr inline std::size_t strLen(const char* str) noexcept{
    return strLenImpl(str);
}


/// Unsigned to signed conversion, using static_cast.
/// Available only if integers are represented using 2 complement.
/// Specialization handles non-2 complement cases.
/// \tparam T An integral type.
/// \tparam _2complement Whether ints are represented as 2 complement.
template<typename T, bool _2complement> // true
struct UnsigToSig {
    typedef typename std::make_signed<T>::type Signed;
    typedef typename std::make_unsigned<T>::type Unsigned;

    static constexpr Signed convert(Unsigned val) noexcept{
        return static_cast<Signed>(val);
    }
};

/// Unsigned to signed conversion.
/// This specialization is used when architecture does not use 2 complement.
/// \tparam T An integral type.
template<typename T>
struct UnsigToSig<T, false> {
    typedef typename std::make_signed<T>::type Signed;
    typedef typename std::make_unsigned<T>::type Unsigned;

    static constexpr Signed convert(Unsigned val) noexcept{
        return val <= std::numeric_limits<Signed>::max() ?
                    static_cast<Signed>(val) :
                    static_cast<Signed>(val - std::numeric_limits<Signed>::min()) + std::numeric_limits<Signed>::min();
    }
};

/// Converts, at compile time, an unsigned integer to its signed counterpart.
/// This holds true: unsignedValue == static_cast<unsigned type>(unsignedToSigned(unsignedValue))
/// \tparam T Unsigned integral type.
/// \param val Unsigned value to be converted to signed.
/// \return Signed value that can be converted back to its unsigned type.
template<typename T, typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
static constexpr inline typename std::make_signed<T>::type unsignedToSigned(T val) noexcept{
    typedef typename std::make_signed<T>::type Signed;
    typedef typename std::make_unsigned<T>::type Unsigned;

    return UnsigToSig<T, static_cast<Signed>(-1) == static_cast<Signed>(~Unsigned(0))>::convert(val);
}

/// Compares two C strings at compile time as if strcmp was used.
/// \param a First string.
/// \param b Second string.
/// \return See strcmp.
static constexpr inline int strCmp(const char* a, const char* b) noexcept{
    return *a != *b ? (static_cast<int>(*a) - *b) : (a == '\0' ? 0 : strCmp(a + 1, b + 1));
}

/// Absolute value.
/// Default implementation handles signed values
/// of non-integral types.
/// \tparam T Data type.
/// \tparam integral Whether the type is integral.
/// \tparam unsig Whether the data type is unsigned.
template<typename T, bool integral, bool unsig> // false, false
struct Abs {
    static constexpr inline T abs(T a) noexcept{
        return a >= T() ? a : -a;
    }
};

/// Absolute value.
/// This handles signed values of integral types.
/// \tparam T Data type.
template<typename T>
struct Abs<T, true, false> {
    static constexpr inline T abs(T a) noexcept{
        return std::abs(a);
    }
};

/// Absolute value.
/// This handles unsigned values.
/// \tparam T Data type.
template<typename T, bool integral>
struct Abs<T, integral, true> {
    static constexpr inline T abs(T a) noexcept{
        return a;
    }
};

/// Absolute value.
/// Handles anything that has `bool operator >=(const T&)` (or equiv.),
/// `T operator-()`, and its default value represents `zero`.
/// \tparam T Data type.
/// \param a Value.
template<typename T>
static constexpr inline T abs(T a) noexcept{
    return Abs<T, std::is_integral<T>::value, std::is_unsigned<T>::value>::abs(a);
}

}

}

#endif // TWPP_DETAIL_FILE_UTILS_HPP

