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

#ifndef TWPP_DETAIL_FILE_TYPESOPS_HPP
#define TWPP_DETAIL_FILE_TYPESOPS_HPP

#include "../twpp.hpp"

namespace Twpp {

/// Enumeration representing basic types.
enum class Type : UInt16 {
    DontCare = 0xFFFF,
    Int8 = 0x0000,
    Int16 = 0x0001,
    Int32 = 0x0002,
    UInt8 = 0x0003,
    UInt16 = 0x0004,
    UInt32 = 0x0005,
    Bool = 0x0006,
    Fix32 = 0x0007,
    Frame = 0x0008,
    Str32 = 0x0009,
    Str64 = 0x000a,
    Str128 = 0x000b,
    Str255 = 0x000c,
    Handle = 0x000f
};

/// Whether the enum value actually is a type, DontCare is not a type.
static inline bool isType(Type type){
    switch (type){
        case Type::Int8:
        case Type::UInt8:
        case Type::Int16:
        case Type::UInt16:
        case Type::Int32:
        case Type::UInt32:
        case Type::Bool:
        case Type::Fix32:
        case Type::Str32:
        case Type::Str64:
        case Type::Str128:
        case Type::Str255:
        case Type::Frame:
        case Type::Handle:
            return true;

        default:
            return false;
    }
}

/// Size in bytes of a type represented by enum value.
static inline UInt32 typeSize(Type type){
    switch (type){
        case Type::Int8: return sizeof(Int8);
        case Type::UInt8: return sizeof(UInt8);
        case Type::Int16: return sizeof(Int16);
        case Type::UInt16: return sizeof(UInt16);
        case Type::Int32: return sizeof(Int32);
        case Type::UInt32: return sizeof(UInt32);
        case Type::Bool: return sizeof(Bool);
        case Type::Fix32: return sizeof(Fix32);
        case Type::Str32: return sizeof(Str32);
        case Type::Str64: return sizeof(Str64);
        case Type::Str128: return sizeof(Str128);
        case Type::Str255: return sizeof(Str255);
        case Type::Frame: return sizeof(Frame);
        case Type::Handle: return sizeof(Handle);
        default: throw std::invalid_argument("unknown type");
    }
}

namespace Detail {

/// Conversion from Type enum to actual data type.
template<Type type> struct Twty {};
template<> struct Twty<Type::Int8> {typedef Int8 Type;};
template<> struct Twty<Type::Int16> {typedef Int16 Type;};
template<> struct Twty<Type::Int32> {typedef Int32 Type;};
template<> struct Twty<Type::UInt8> {typedef UInt8 Type;};
template<> struct Twty<Type::UInt16> {typedef UInt16 Type;};
template<> struct Twty<Type::UInt32> {typedef UInt32 Type;};
template<> struct Twty<Type::Bool> {typedef Bool Type;};
template<> struct Twty<Type::Fix32> {typedef Fix32 Type;};
template<> struct Twty<Type::Frame> {typedef Frame Type;};
template<> struct Twty<Type::Str32> {typedef Str32 Type;};
template<> struct Twty<Type::Str64> {typedef Str64 Type;};
template<> struct Twty<Type::Str128> {typedef Str128 Type;};
template<> struct Twty<Type::Str255> {typedef Str255 Type;};
template<> struct Twty<Type::Handle> {typedef Handle Type;};


// Conversion from data type to Type enum helpers.
template<typename DataType> struct Tytw;

template<typename DataType, bool isEnum> // true
struct TytwHelper : Tytw<typename std::underlying_type<DataType>::type> {};

template<typename DataType>
struct TytwHelper<DataType, false> {};

/// Conversion from data type to Type enum.
template<typename DataType> struct Tytw : TytwHelper<DataType, std::is_enum<DataType>::value> {};
template<> struct Tytw<Int8> {static constexpr const Type twty = Type::Int8;};
template<> struct Tytw<Int16> {static constexpr const Type twty = Type::Int16;};
template<> struct Tytw<Int32> {static constexpr const Type twty = Type::Int32;};
template<> struct Tytw<UInt8> {static constexpr const Type twty = Type::UInt8;};
template<> struct Tytw<UInt16> {static constexpr const Type twty = Type::UInt16;};
template<> struct Tytw<UInt32> {static constexpr const Type twty = Type::UInt32;};
template<> struct Tytw<Bool> {static constexpr const Type twty = Type::Bool;};
template<> struct Tytw<Fix32> {static constexpr const Type twty = Type::Fix32;};
template<> struct Tytw<Frame> {static constexpr const Type twty = Type::Frame;};
template<> struct Tytw<Str32> {static constexpr const Type twty = Type::Str32;};
template<> struct Tytw<Str64> {static constexpr const Type twty = Type::Str64;};
template<> struct Tytw<Str128> {static constexpr const Type twty = Type::Str128;};
template<> struct Tytw<Str255> {static constexpr const Type twty = Type::Str255;};
template<> struct Tytw<Handle> {static constexpr const Type twty = Type::Handle;};

}

}

#endif // TWPP_DETAIL_FILE_TYPESOPS_HPP

