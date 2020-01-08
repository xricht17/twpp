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

#ifndef TWPP_DETAIL_FILE_PALETTE8_HPP
#define TWPP_DETAIL_FILE_PALETTE8_HPP

#include "../twpp.hpp"


namespace Twpp {

namespace Detail {

// specialization for Element8
// we also want to set index of the element when placing it inside array
template<std::size_t arraySize, std::size_t... i>
struct FixedArrayData<Element8, arraySize, IndexList<i...> > {

    static constexpr Element8 updateIndex(UInt8 index, const Element8& e) noexcept{
        return Element8(index, e.channel1(), e.channel2(), e.channel3());
    }

    template<std::size_t inputSize>
    constexpr FixedArrayData(const Element8(& arr)[inputSize]) noexcept :
        m_arr{updateIndex(i, FixedArrayFlat<Element8, arraySize>(arr)[i])...}{}

    constexpr FixedArrayData() noexcept :
        m_arr{Element8(i)...}{}

    Element8 m_arr[arraySize];

};

}


TWPP_DETAIL_PACK_BEGIN
/// Palette information for memory transfers
class Palette8 {

public:
    enum class Type : UInt16 {
        Rgb = 0,
        Gray = 1,
        Cmy = 2
    };

    typedef Element8 Element8Arr256[256];

    /// Creates an uninitialized palette.
    constexpr Palette8() noexcept :
        m_size(0), m_type(Type::Rgb), m_colors(){}

    /// Creates a palette with the supplied type and elements.
    template<std::size_t inputSize>
    constexpr Palette8(Type type, const Element8(& colors)[inputSize]) noexcept :
        m_size(inputSize), m_type(type),
        m_colors(colors){

        static_assert(inputSize <= 256, "too many colors");
    }

    /// Creates a palette with the supplied type and elements from container.
    /// \throw RangeException When there are more than 256 colors.
    template<typename Container>
    Palette8(Type type, const Container& colors) :
        m_size(static_cast<UInt16>(colors.size())), m_type(type){

        if (colors.size() > 256){
            throw RangeException();
        }

        auto& array = m_colors.array();
        for (UInt16 i = 0; i < m_size; i++){
            array[i] = colors[i];
            array[i].setIndex(i);
        }
    }

    /// Creates a palette with the supplied type and elements.
    /// \throw RangeException When there are more than 256 colors.
    Palette8(Type type, const Element8* colors, UInt16 size) :
        m_size(size), m_type(type){

        if (m_size > 256){
            throw RangeException();
        }

        auto& array = m_colors.array();
        for (UInt16 i = 0; i < m_size; i++){
            array[i] = colors[i];
            array[i].setIndex(static_cast<UInt8>(i)); // 0..255 max
        }
    }

    /// Number of elements in the palette.
    constexpr UInt16 size() const noexcept{
        return m_size;
    }

    /// Type of palette data.
    constexpr Type type() const noexcept{
        return m_type;
    }

    /// Array of palette elements.
    constexpr const Element8Arr256& colors() const noexcept{
        return m_colors.array();
    }

private:
    UInt16 m_size;
    Type m_type;
    Detail::FixedArray<Element8, 256> m_colors;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_PALETTE8_HPP

