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

#ifndef TWPP_DETAIL_FILE_MEMORY_HPP
#define TWPP_DETAIL_FILE_MEMORY_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

namespace Flags {

enum {
    AppOwns = 0x0001,
    DsmOwns = 0x0002,
    DsOwns = 0x0004,
    Pointer = 0x0008,
    Handle = 0x0010
};


#if !defined(TWPP_IS_DS)
static constexpr const UInt32 thisOwns = AppOwns;
static constexpr const UInt32 otherOwns = DsOwns;
#else
static constexpr const UInt32 thisOwns = DsOwns;
static constexpr const UInt32 otherOwns = AppOwns;
#endif

}

}

TWPP_DETAIL_PACK_BEGIN
/// Holds and potentially owns a block of memory using either pointer or handle.
class Memory {

public:
    typedef Detail::MaybeLock<char> Data;
    typedef Detail::MaybeLock<const char> ConstData;

    /// Creates an empty memory.
    constexpr Memory() noexcept :
        m_flags(0), m_size(0), m_data(nullptr){}

    /// Creates a memory block of supplied size.
    /// \throw std::bad_alloc
    explicit Memory(UInt32 size) :
        m_flags(Detail::Flags::thisOwns | Detail::Flags::Handle), m_size(size),
        m_data(Detail::alloc(size).raw()){}

    /// Creates a new memory object from Handle.
    /// The memory ownership is taken over.
    /// \param h The handle, see thisOwns for more information about memory ownership.
    /// \param size Size of the memory in bytes, that handle h manages.
    /// \param thisOwns {
    /// If true, this object frees the memory once it goes out of scope.
    ///
    /// If false the memory is not freed, and MUST be passed to the other side
    /// (APP->DS or DS->APP) of the connection, that will free it.
    /// }
    Memory(Handle h, UInt32 size, bool thisOwns = true) noexcept :
        m_flags((thisOwns ? Detail::Flags::thisOwns : Detail::Flags::otherOwns) | Detail::Flags::Handle),
        m_size(size),
        m_data(h.raw()){}

    /// Creates a memory object from container.
    /// The memory object does NOT take over the ownership of the data.
    /// Make sure the container is destroyed after the memory object is.
    template<typename Container>
    explicit Memory(const Container& container) noexcept :
        m_flags(Detail::Flags::thisOwns | Detail::Flags::Pointer),
        m_size(sizeof(Container::value_type) * container.size()),
        m_data(container.data()){}

    /// Creates a memory object from pointer.
    /// The memory object does NOT take over the ownership of the data.
    /// Make sure the data is destroyed after the memory object is.
    constexpr Memory(void* data, UInt32 size) noexcept :
        m_flags(Detail::Flags::thisOwns | Detail::Flags::Pointer), m_size(size),
        m_data(data){}

    ~Memory(){
        freePriv();
    }

    Memory(const Memory& o) = delete;
    Memory& operator=(const Memory& o) = delete;

    Memory(Memory&& o) noexcept :
        m_flags(o.m_flags), m_size(o.m_size), m_data(o.m_data)
    {
        o.m_flags = 0;
        o.m_size = 0;
        o.m_data = nullptr;
    }

    Memory& operator=(Memory&& o) noexcept{
        if (&o != this){
            freePriv();

            m_flags = o.m_flags;
            m_size = o.m_size;
            m_data = o.m_data;

            o.m_flags = 0;
            o.m_size = 0;
            o.m_data = nullptr;
        }

        return *this;
    }

    /// The data in this memory block.
    ConstData data() const noexcept{
        return m_flags & Detail::Flags::Handle ?
                    ConstData(Handle(static_cast<Handle::Raw>(m_data))) :
                    ConstData(static_cast<const char*>(m_data));
    }

    /// The data in this memory block.
    Data data() noexcept{
        return m_flags & Detail::Flags::Handle ?
                    Data(Handle(static_cast<Handle::Raw>(m_data))) :
                    Data(static_cast<char*>(m_data));
    }

    /// Number of bytes in the memory block.
    UInt32 size() const noexcept{
        return m_size;
    }

    /// In case of handle, frees memory regardless its owner; does nothing otherwise (pointer).
    /// Potentially unsafe operation.
    void free(){
        if (m_flags & Detail::Flags::Handle){
            Handle h(static_cast<Handle::Raw>(m_data));
            if (h){
                Detail::free(h);
            }

            m_size = 0;
            m_data = nullptr;
            m_flags = 0;
        }
    }

private:
    void freePriv(){
        if (m_flags & Detail::Flags::thisOwns){
            if (m_flags & Detail::Flags::Handle){
                Detail::free(Handle(static_cast<Handle::Raw>(m_data)));
            }
        }
    }

    UInt32 m_flags;
    UInt32 m_size;
    void* m_data;

};
TWPP_DETAIL_PACK_END



}

#endif // TWPP_DETAIL_FILE_MEMORY_HPP

