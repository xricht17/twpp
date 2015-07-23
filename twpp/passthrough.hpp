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

#ifndef TWPP_DETAIL_FILE_PASSTHROUGH_HPP
#define TWPP_DETAIL_FILE_PASSTHROUGH_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure for raw comminication with device in source.
/// See manual for more information, DAT_PASSTHRU, MSG_PASSTHRU.
class PassThrough {

public:
    enum class Direction : Int32 {
        Get = 1,
        Set = 2
    };

    constexpr PassThrough(
            void* command,
            UInt32 commandSize,
            Direction direction,
            void* data,
            UInt32 dataSize,
            UInt32 dataXfered
    ) noexcept :
        m_cmd(command), m_cmdSize(commandSize),
        m_direction(direction),
        m_data(data), m_dataSize(dataSize), m_dataXfered(dataXfered){}

    constexpr void* command() const noexcept{
        return m_cmd;
    }

    constexpr UInt32 commandSize() const noexcept{
        return m_cmdSize;
    }

    template<typename Container>
    void setCommand(const Container& command) noexcept{
        m_cmd = command.data();
        m_cmdSize = sizeof(Container::value_type) * command.size();
    }

    void setCommand(void* command, UInt32 size) noexcept{
        m_cmd = command;
        m_cmdSize = size;
    }

    constexpr Direction direction() const noexcept{
        return m_direction;
    }

    void setDirection(Direction direction) noexcept{
        m_direction = direction;
    }

    constexpr void* data() const noexcept{
        return m_data;
    }

    constexpr UInt32 dataSize() const noexcept{
        return m_dataSize;
    }

    template<typename Container>
    void setData(const Container& data) noexcept{
        m_data = data.data();
        m_dataSize = sizeof(Container::value_type) * data.size();
        m_dataXfered = 0;
    }

    void setData(void* data, UInt32 dataSize) noexcept{
        m_data = data;
        m_dataSize = dataSize;
        m_dataXfered = 0;
    }

    constexpr UInt32 dataXfered() const noexcept{
        return m_dataXfered;
    }

    void setDataXfered(Int32 dataXfered) noexcept{
        m_dataXfered = dataXfered;
    }

private:
    void* m_cmd;
    UInt32 m_cmdSize;
    Direction m_direction;
    void* m_data;
    UInt32 m_dataSize;
    UInt32 m_dataXfered;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_PASSTHROUGH_HPP
