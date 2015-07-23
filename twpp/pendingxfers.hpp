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

#ifndef TWPP_DETAIL_FILE_PENDINGXFERS_HPP
#define TWPP_DETAIL_FILE_PENDINGXFERS_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Reports number of pending images, transfers.
class PendingXfers {

public:
    /// Job control settings.
    enum class JobPatch : UInt32 {
        None = 0x0000,
        MidSeparator = 0x0001,
        P1 = 0x0002,
        P2 = 0x0003,
        P3 = 0x0004,
        P4 = 0x0005,
        P6 = 0x0006,
        PT = 0x0007
    };

    /// Creates object to report number of pending transfers.
    /// \param count Number of pending transfers.
    /// \param patch Job control settings.
    constexpr PendingXfers(UInt16 count = 0, JobPatch patch = JobPatch::None) noexcept :
        m_count(count), m_eoj(patch){}

    /// Number of pending images/transfers.
    constexpr UInt16 count() const noexcept{
        return m_count;
    }

    /// Sets number of pending images/transfers.
    void setCount(UInt16 count) noexcept{
        m_count = count;
    }

    /// Job control settings.
    constexpr JobPatch jobPatch() const noexcept{
        return m_eoj;
    }

    /// Sets job control settings.
    void setJobPatch(JobPatch eoj) noexcept{
        m_eoj = eoj;
    }

private:
    UInt16 m_count;
    JobPatch m_eoj;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_PENDINGXFERS_HPP
