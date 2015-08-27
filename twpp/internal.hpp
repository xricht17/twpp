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

#ifndef TWPP_DETAIL_FILE_INTERNAL_HPP
#define TWPP_DETAIL_FILE_INTERNAL_HPP

#include "../twpp.hpp"

namespace Twpp {

struct AudioFileXfer {};
struct ImageFileXfer {};
typedef Memory IccProfileMemory;

namespace Detail {

typedef ReturnCode (TWPP_DETAIL_CALLSTYLE* DsmEntry)(
        Identity* origin,
        Identity* dest,
        DataGroup dg,
        Dat dat,
        Msg msg,
        void* data
);

typedef DsmEntry CallBackFunc;

typedef
#if defined(TWPP_DETAIL_OS_MAC)
void*
#else
UInt32
#endif
CallBackConstant;


TWPP_DETAIL_PACK_BEGIN
struct EntryPoint {
    constexpr EntryPoint() noexcept :
        m_size(sizeof(EntryPoint)), m_entry(nullptr), m_alloc(nullptr),
        m_free(nullptr), m_lock(nullptr), m_unlock(nullptr){}

    UInt32 m_size;
    DsmEntry m_entry;
    MemAlloc m_alloc;
    MemFree m_free;
    MemLock m_lock;
    MemUnlock m_unlock;
};

struct CallBack {

    constexpr CallBack(CallBackFunc func, CallBackConstant constant, Msg msg) noexcept :
        m_func(func), m_constant(constant), m_msg(msg){}

    CallBackFunc m_func;
    CallBackConstant m_constant;
    Msg m_msg;

};

struct CallBack2 {

    constexpr CallBack2(CallBackFunc func, UIntPtr constant, Msg msg) noexcept :
        m_func(func), m_constant(constant), m_msg(msg){}

    CallBackFunc m_func;
    UIntPtr m_constant;
    Msg m_msg;
};
TWPP_DETAIL_PACK_END

/// Manages DSM dll/so/framework connection.
class DsmLib {

public:
    constexpr DsmLib() noexcept :
        m_handle(DsmLibOs::nullHandle){}

    ~DsmLib(){
        unload();
    }

    DsmLib(const DsmLib&) = delete;
    DsmLib& operator=(const DsmLib&) = delete;

    DsmLib(DsmLib&& o) noexcept :
        m_handle(o.m_handle){

        o.m_handle = DsmLibOs::nullHandle;
    }

    DsmLib& operator=(DsmLib&& o) noexcept{
        if (&o != this){
            unload();

            m_handle = o.m_handle;
            o.m_handle = DsmLibOs::nullHandle;
        }

        return *this;
    }

    operator bool() const noexcept{
        return m_handle != DsmLibOs::nullHandle;
    }

    bool load(bool preferOld = false) noexcept{
        m_handle = DsmLibOs::load(preferOld);
        return m_handle != DsmLibOs::nullHandle;
    }

    void unload() noexcept{
        if (m_handle != DsmLibOs::nullHandle){
            DsmLibOs::unload(m_handle);
            m_handle = DsmLibOs::nullHandle;
        }
    }

    DsmEntry resolve() const noexcept{
        return DsmLibOs::resolve<DsmEntry>(m_handle);
    }

private:
    DsmLibOs::Handle m_handle;

};

}

}

#endif // TWPP_DETAIL_FILE_INTERNAL_HPP
