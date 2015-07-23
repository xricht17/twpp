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

#ifndef TWPP_DETAIL_FILE_JPEGCOMPRESSION_HPP
#define TWPP_DETAIL_FILE_JPEGCOMPRESSION_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// See manual for more info.
class JpegCompression {

public:
    typedef UInt16 UInt16Arr4[4];
    typedef Memory MemoryArr2[2];
    typedef Memory MemoryArr4[4];

    constexpr JpegCompression() noexcept :
        m_colorSpace(PixelType::BlackWhite), m_subSampling(0x10001000), m_components(0),
        m_restartFrequency(0), m_quantMap(), m_huffmanMap(){}

    template<
        std::size_t quantTableMapSize,
        std::size_t quantTableSize,
        std::size_t huffmanTableMapSize,
        std::size_t huffmanDcSize,
        std::size_t huffmanAcSize
    >
    JpegCompression(
        PixelType colorSpace,
        UInt32 subSampling,
        UInt16 components,
        UInt16 restartFrequency,
        const UInt16(& quantTableMap)[quantTableMapSize],
        Memory(& quantTable)[quantTableSize],
        const UInt16(& huffmanTableMap)[huffmanTableMapSize],
        Memory(& huffmanDc)[huffmanDcSize],
        Memory(& huffmanAc)[huffmanAcSize]
    ) noexcept :
        m_colorSpace(colorSpace),
        m_subSampling(subSampling),
        m_components(components),
        m_restartFrequency(restartFrequency),
        m_quantMap(quantTableMap),
        m_huffmanMap(huffmanTableMap){

        for (std::size_t i = 0; i < quantTableSize; i++){
            m_quantTable[i] = std::move(quantTable[i]);
        }

        for (std::size_t i = 0; i < huffmanDcSize; i++){
            m_huffmanDc[i] = std::move(huffmanDc[i]);
        }

        for (std::size_t i = 0; i < huffmanAcSize; i++){
            m_huffmanAc[i] = std::move(huffmanAc[i]);
        }
    }

    PixelType pixelType() const noexcept{
        return m_colorSpace;
    }

    void setPixelType(PixelType pixelType) noexcept{
        m_colorSpace = pixelType;
    }

    UInt32 subSampling() const noexcept{
        return m_subSampling;
    }

    void setSubSampling(UInt32 subSampling) noexcept{
        m_subSampling = subSampling;
    }

    UInt16 components() const noexcept{
        return m_components;
    }

    void setComponents(UInt16 components) noexcept{
        m_components = components;
    }

    UInt16 restartFrequency() const noexcept{
        return m_restartFrequency;
    }

    void setRestartFrequency(UInt16 restartFrequency) noexcept{
        m_restartFrequency = restartFrequency;
    }

    const UInt16Arr4& quantTableMap() const noexcept{
        return m_quantMap.array();
    }

    UInt16Arr4& quantTableMap() noexcept{
        return m_quantMap.array();
    }

    const MemoryArr4& quantTable() const noexcept{
        return m_quantTable;
    }

    MemoryArr4& quantTable() noexcept{
        return m_quantTable;
    }

    const UInt16Arr4& huffmanTableMap() const noexcept{
        return m_huffmanMap.array();
    }

    UInt16Arr4& huffmanTableMap() noexcept{
        return m_huffmanMap.array();
    }

    const MemoryArr2& huffmanDc() const noexcept{
        return m_huffmanDc;
    }

    MemoryArr2& huffmanDc() noexcept{
        return m_huffmanDc;
    }

    const MemoryArr2& huffmanAc() const noexcept{
        return m_huffmanAc;
    }

    MemoryArr2& huffmanAc() noexcept{
        return m_huffmanAc;
    }

private:
    PixelType m_colorSpace;
    UInt32 m_subSampling;
    UInt16 m_components;
    UInt16 m_restartFrequency;
    Detail::FixedArray<UInt16, 4> m_quantMap;
    MemoryArr4 m_quantTable;
    Detail::FixedArray<UInt16, 4> m_huffmanMap;
    MemoryArr2 m_huffmanDc;
    MemoryArr2 m_huffmanAc;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_JPEGCOMPRESSION_HPP
