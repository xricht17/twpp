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

#ifndef TWPP_DETAIL_FILE_CUSTOMDATA_HPP
#define TWPP_DETAIL_FILE_CUSTOMDATA_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure for sending custom data to source or application.
class CustomData {

public:
    template <typename T>
    using Data = typename Detail::Lock<T>;

    /// Creates empty custom data.
    constexpr CustomData() noexcept :
        m_size(0), m_handle(){}

    /// Creates custom data with allocated memory.
    /// \throw std::bad_alloc
    explicit CustomData(UInt32 size) :
        m_size(size), m_handle(Detail::alloc(size)){}

    /// Locks and returns pointer to custom data memory.
    template<typename T = void>
    Data<T> lock() const noexcept{
        return Data<T>(m_handle);
    }

    /// The size of contained memory block.
    UInt32 size() const noexcept{
        return m_size;
    }

private:
    UInt32 m_size;
    Detail::UniqueHandle m_handle;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_CUSTOMDATA_HPP
