/*

The MIT License (MIT)

Copyright (c) 2015-2017 Martin Richter

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

#ifndef TWPP_DETAIL_FILE_MEMORYOPS_HPP
#define TWPP_DETAIL_FILE_MEMORYOPS_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

extern "C" {

typedef Handle::Raw (TWPP_DETAIL_CALLSTYLE* MemAlloc)(UInt32 size);
typedef void (TWPP_DETAIL_CALLSTYLE* MemFree)(Handle::Raw handle);
typedef void* (TWPP_DETAIL_CALLSTYLE* MemLock)(Handle::Raw handle);
typedef void (TWPP_DETAIL_CALLSTYLE* MemUnlock)(Handle::Raw handle);

}

// templates behave as if they were defined in at most one module
// ideal for storing static data
template<typename Dummy>
struct GlobalMemFuncs {

#if defined(TWPP_DETAIL_OS_WIN)
    static Handle::Raw TWPP_DETAIL_CALLSTYLE defAlloc(UInt32 size){
        return ::GlobalAlloc(GHND, size);
    }

    static void TWPP_DETAIL_CALLSTYLE defFree(Handle::Raw handle){
        ::GlobalFree(handle);
    }

    static void* TWPP_DETAIL_CALLSTYLE defLock(Handle::Raw handle){
        return ::GlobalLock(handle);
    }

    static void TWPP_DETAIL_CALLSTYLE defUnlock(Handle::Raw handle){
        ::GlobalUnlock(handle);
    }
#elif defined(TWPP_DETAIL_OS_MAC)
    static Handle::Raw TWPP_DETAIL_CALLSTYLE defAlloc(UInt32 size){
        return ::NewHandle(size);
    }

    static void TWPP_DETAIL_CALLSTYLE defFree(Handle::Raw handle){
        ::DisposeHandle(handle);
    }

    static void* TWPP_DETAIL_CALLSTYLE defLock(Handle::Raw handle){
        return *handle;
    }

    static void TWPP_DETAIL_CALLSTYLE defUnlock(Handle::Raw handle){
        // noop
    }
#elif !defined(TWPP_DETAIL_OS_LINUX) // Linux doesnt need default functions
#   error "default memory functions for your platform here"
#endif

    static MemAlloc alloc;
    static MemFree free;
    static MemLock lock;
    static MemUnlock unlock;

};

#if defined(TWPP_DETAIL_OS_WIN) || defined(TWPP_DETAIL_OS_MAC)
template<typename Dummy>
MemAlloc GlobalMemFuncs<Dummy>::alloc = GlobalMemFuncs<Dummy>::defAlloc;

template<typename Dummy>
MemFree GlobalMemFuncs<Dummy>::free = GlobalMemFuncs<Dummy>::defFree;

template<typename Dummy>
MemLock GlobalMemFuncs<Dummy>::lock = GlobalMemFuncs<Dummy>::defLock;

template<typename Dummy>
MemUnlock GlobalMemFuncs<Dummy>::unlock = GlobalMemFuncs<Dummy>::defUnlock;
#elif defined(TWPP_DETAIL_OS_LINUX)
template<typename Dummy>
MemAlloc GlobalMemFuncs<Dummy>::alloc = nullptr;

template<typename Dummy>
MemFree GlobalMemFuncs<Dummy>::free = nullptr;

template<typename Dummy>
MemLock GlobalMemFuncs<Dummy>::lock = nullptr;

template<typename Dummy>
MemUnlock GlobalMemFuncs<Dummy>::unlock = nullptr;
#else
#   error "default memory functions setup for your platform here"
#endif

inline static void setMemFuncs(MemAlloc alloc, MemFree free, MemLock lock, MemUnlock unlock) noexcept{
    GlobalMemFuncs<void>::alloc = alloc;
    GlobalMemFuncs<void>::free = free;
    GlobalMemFuncs<void>::lock = lock;
    GlobalMemFuncs<void>::unlock = unlock;
}

inline static void resetMemFuncs() noexcept{
#if defined(TWPP_DETAIL_OS_WIN) || defined(TWPP_DETAIL_OS_MAC)
    GlobalMemFuncs<void>::alloc = GlobalMemFuncs<void>::defAlloc;
    GlobalMemFuncs<void>::free = GlobalMemFuncs<void>::defFree;
    GlobalMemFuncs<void>::lock = GlobalMemFuncs<void>::defLock;
    GlobalMemFuncs<void>::unlock = GlobalMemFuncs<void>::defUnlock;
#elif defined(TWPP_DETAIL_OS_LINUX)
    GlobalMemFuncs<void>::alloc = nullptr;
    GlobalMemFuncs<void>::free = nullptr;
    GlobalMemFuncs<void>::lock = nullptr;
    GlobalMemFuncs<void>::unlock = nullptr;
#else
#   error "resetMemFuncs for your platform here"
#endif
}

inline static Handle alloc(UInt32 size){
    auto h = GlobalMemFuncs<void>::alloc(size);
    if (!h){
        throw std::bad_alloc();
    }

    return Handle(h);
}

inline static void* lock(Handle handle) noexcept{
    return GlobalMemFuncs<void>::lock(handle.raw());
}

inline static void unlock(Handle handle) noexcept{
    GlobalMemFuncs<void>::unlock(handle.raw());
}

inline static void free(Handle handle) noexcept{
    GlobalMemFuncs<void>::free(handle.raw());
}

template<typename T>
static inline T* typeLock(Handle handle) noexcept{
    return static_cast<T*>(lock(handle));
}

/// A lock that can contain either handle or raw pointer.
/// Locks and unlocks handle, noop for pointer.
template<typename T>
class MaybeLock {

public:
    constexpr MaybeLock() noexcept :
        m_handle(), m_pointer(nullptr){}

    MaybeLock(Handle h) noexcept :
        m_handle(h), m_pointer(typeLock<T>(h)){}

    constexpr MaybeLock(T* ptr) noexcept :
        m_handle(), m_pointer(ptr){}

    ~MaybeLock(){
        unlock();
    }

    MaybeLock(const MaybeLock& o) noexcept :
        m_handle(o.m_handle), m_pointer(o.m_handle ? typeLock<T>(o.m_handle) : o.m_pointer){}

    MaybeLock& operator=(const MaybeLock& o) noexcept{
        if (&o != this){
            unlock();

            m_handle = o.m_handle;
            m_pointer = m_handle ? typeLock<T>(m_handle) : o.m_pointer;
        }

        return *this;
    }


    MaybeLock(MaybeLock&& o) noexcept :
        m_handle(o.m_handle), m_pointer(o.m_pointer){

        o.m_handle = Handle();
        o.m_pointer = nullptr;
    }

    MaybeLock& operator=(MaybeLock&& o) noexcept{
        if (&o != this){
            unlock();

            m_handle = o.m_handle;
            m_pointer = o.m_pointer;

            o.m_handle = Handle();
            o.m_pointer = nullptr;
        }

        return *this;
    }

    T* data() const noexcept{
        return m_pointer;
    }

    operator T*() const noexcept{
        return m_pointer;
    }

    T* operator->() noexcept{
        return m_pointer;
    }

    T* operator->() const noexcept{
        return m_pointer;
    }

    bool hasData() const noexcept{
        return m_pointer;
    }

    operator bool() const noexcept{
        return m_pointer;
    }

private:
    void unlock() noexcept{
        if (m_handle){
            Detail::unlock(m_handle);
        }
    }

    Handle m_handle;
    T* m_pointer;

};

/// Simple handle lock.
/// Locks on creation and unlocks on destruction.
template<typename T>
class Lock {

public:
    constexpr Lock() noexcept :
        m_handle(), m_pointer(nullptr){}

    Lock(Handle h) noexcept :
        m_handle(h), m_pointer(typeLock<T>(h)){}

    ~Lock(){
        unlock();
    }


    Lock(const Lock& o) noexcept :
        m_handle(o.m_handle), m_pointer(typeLock<T>(o.m_handle)){}

    Lock& operator=(const Lock& o) noexcept{
        if (&o != this){
            unlock();

            m_handle = o.m_handle;
            m_pointer = typeLock<T>(m_handle);
        }

        return *this;
    }


    Lock(Lock&& o) noexcept :
        m_handle(o.m_handle), m_pointer(o.m_pointer){

        o.m_handle = Handle();
        o.m_pointer = nullptr;
    }

    Lock& operator=(Lock&& o) noexcept{
        if (&o != this){
            unlock();

            m_handle = o.m_handle;
            m_pointer = o.m_pointer;

            o.m_handle = Handle();
            o.m_pointer = nullptr;
        }

        return *this;
    }


    T* data() const noexcept{
        return m_pointer;
    }

    operator T*() const noexcept{
        return m_pointer;
    }

    T* operator->() noexcept{
        return m_pointer;
    }

    T* operator->() const noexcept{
        return m_pointer;
    }

    bool hasData() const noexcept{
        return m_pointer;
    }

    operator bool() const noexcept{
        return m_pointer;
    }

private:
    void unlock() noexcept{
        if (m_handle){
            Detail::unlock(m_handle);
        }
    }

    Handle m_handle;
    T* m_pointer;

};



/// Owns a handle and frees it upon destruction,
/// unless `release` is called beforehand.
class UniqueHandle {

public:
    constexpr UniqueHandle(Handle h = Handle()) noexcept :
        m_handle(h){}

    ~UniqueHandle(){
        free();
    }

    UniqueHandle(const UniqueHandle&) = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;

    UniqueHandle(UniqueHandle&& o) noexcept :
        m_handle(o.m_handle){

        o.m_handle = Handle();
    }

    UniqueHandle& operator=(UniqueHandle&& o) noexcept{
        if (&o != this){
            free();

            m_handle = o.m_handle;

            o.m_handle = Handle();
        }

        return *this;
    }

    operator bool() const noexcept{
        return m_handle;
    }

    /// The contained handle.
    Handle get() noexcept{
        return m_handle;
    }

    /// The contained handle.
    Handle get() const noexcept{
        return m_handle;
    }

    /// Releases the contained handle, making the user responsible for freeing it.
    Handle release() noexcept{
        Handle ret = m_handle;
        m_handle = Handle();
        return ret;
    }

    template<typename T>
    Lock<T> lock() const{
        return m_handle;
    }

private:
    void free() noexcept{
        if (m_handle){
            Detail::free(m_handle);
        }
    }

    Handle m_handle;

};

}

}

#endif // TWPP_DETAIL_FILE_MEMORYOPS_HPP

