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

#ifndef TWPP_DETAIL_FILE_ENV_HPP
#define TWPP_DETAIL_FILE_ENV_HPP

// =============
// Twpp specific

namespace Twpp {

namespace Detail {

enum {
    ProtoMajor = 2,
    ProtoMinor = 3,
    Dsm2 = 0x10000000L,
    App2 = 0x20000000L,
    Ds2  = 0x40000000L
};

}

}

#if defined(TWPP_IS_DS)
#   define TWPP_DETAIL_IS_DS 1
#else
#   define TWPP_DETAIL_IS_DS 0
#endif


// ===========
// OS specific

// Windows
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#   define TWPP_DETAIL_OS_WIN 1
#   if defined(WIN64) || defined(_WIN64)
#       define TWPP_DETAIL_OS_WIN64 1
#   else
#       define TWPP_DETAIL_OS_WIN32 1
#   endif
#   if !defined(WIN32_LEAN_AND_MEAN)
#       define WIN32_LEAN_AND_MEAN
#   endif
#   if !defined(NOMINMAX)
#       define NOMINMAX
#   endif
extern "C" {
#   include <windows.h>
}
#   define TWPP_DETAIL_CALLSTYLE PASCAL
#   define TWPP_DETAIL_EXPORT __declspec(dllexport)
namespace Twpp {

namespace Detail {

typedef HANDLE RawHandle;


namespace DsmLibOs {

typedef HMODULE Handle;
static constexpr const Handle nullHandle = nullptr;

template<typename T>
static inline T resolve(Handle h) noexcept{
    return reinterpret_cast<T>(::GetProcAddress(h, "DSM_Entry"));
}

#   if defined(TWPP_DETAIL_OS_WIN32)
static inline Handle load(bool old) noexcept{
    if (old){
        auto h = ::LoadLibraryA("TWAIN_32.dll");
        if (!h){
            h = ::LoadLibraryA("TWAINDSM.dll");
        }

        return h;
    } else {
        auto h = ::LoadLibraryA("TWAINDSM.dll");
        if (!h){
            h = ::LoadLibraryA("TWAIN_32.dll");
        }

        return h;
    }
}
#   else
static inline Handle load(bool) noexcept{
    return ::LoadLibraryA("TWAINDSM.dll");
}
#   endif

static inline void unload(Handle h) noexcept{
    ::FreeLibrary(h);
}

} // namespace DsmLibOs

} // namespace Detail

} // namespace Twpp


// Mac OS
#elif defined(__APPLE__)
#   pragma message "No testing has been done on this platform, this framework might not work correctly."
#   define TWPP_DETAIL_OS_MAC 1
#   include <limits>
extern "C" {
#   include <objc/objc.h>
#   include <objc/objc-runtime.h>
#   include <objc/NSObjCRuntime.h>
#   include <CoreServices/CoreServices.h>
#   include <dlfcn.h>
}
#   define TWPP_DETAIL_CALLSTYLE pascal
namespace Twpp {

namespace Detail {

typedef Handle RawHandle;


namespace DsmLibOs {

typedef void* Handle;
static constexpr const Handle nullHandle = nullptr;

template<typename T>
static inline T resolve(Handle h) noexcept{
    return reinterpret_cast<T>(::dlsym(h, "DSM_Entry"));
}

static inline Handle load(bool) noexcept{
    return ::dlopen("/System/Library/Frameworks/TWAIN.framework/TWAIN", RTLD_LAZY);
}

static inline void unload(Handle h) noexcept{
    ::dlclose(h);
}

} // namespace DsmLibOs

template<typename>
struct MacStatic {

    static const ::Class g_autoreleasePool;
    static const ::SEL g_release;
    static const ::SEL g_alloc;
    static const ::SEL g_init;

    static const ::SEL g_nextEvent;
    static const ::SEL g_postEvent;
    static const ::SEL g_sendEvent;
    static const ::id g_app;
    static const ::id g_distantFuture;

    static const ::Class g_event;
    static const ::SEL g_otherEventWithType;

};

template<typename Dummy> const ::Class MacStatic<Dummy>::g_autoreleasePool = objc_getClass("NSAutoreleasePool");
template<typename Dummy> const ::SEL MacStatic<Dummy>::g_release = sel_registerName("release");
template<typename Dummy> const ::SEL MacStatic<Dummy>::g_alloc = sel_registerName("alloc");
template<typename Dummy> const ::SEL MacStatic<Dummy>::g_init = sel_registerName("init");

template<typename Dummy> const ::SEL MacStatic<Dummy>::g_nextEvent = sel_registerName("nextEventMatchingMask:untilDate:inMode:dequeue:");
template<typename Dummy> const ::SEL MacStatic<Dummy>::g_postEvent = sel_registerName("postEvent:atStart:");
template<typename Dummy> const ::SEL MacStatic<Dummy>::g_sendEvent = sel_registerName("sendEvent:");
template<typename Dummy> const ::id MacStatic<Dummy>::g_app = objc_msgSend(reinterpret_cast<::id>(objc_getClass("NSApplication")), sel_registerName("sharedApplication"));
template<typename Dummy> const ::id MacStatic<Dummy>::g_distantFuture = objc_msgSend(reinterpret_cast<::id>(objc_getClass("NSDate")), sel_registerName("distantFuture"));

template<typename Dummy> const ::Class MacStatic<Dummy>::g_event = objc_getClass("NSEvent");
template<typename Dummy> const ::SEL MacStatic<Dummy>::g_otherEventWithType = sel_registerName("otherEventWithType:location:modifierFlags:timestamp:windowNumber:context:subtype:data1:data2:");

class NSAutoreleasePool {

public:
    NSAutoreleasePool() noexcept :
        m_id(createPool()) {}

    ~NSAutoreleasePool(){
        release();
    }

    NSAutoreleasePool(const NSAutoreleasePool&) = delete;
    NSAutoreleasePool& operator=(const NSAutoreleasePool&) = delete;

    NSAutoreleasePool(NSAutoreleasePool&& o) noexcept :
        m_id(o.m_id){

        o.m_id = nullptr;
    }

    NSAutoreleasePool& operator=(NSAutoreleasePool&& o) noexcept{
        if (this != &o){
            release();
            std::swap(m_id, o.m_id);
        }

        return *this;
    }

    void release() noexcept{
        if (m_id != nullptr){
            objc_msgSend(m_id, MacStatic<void>::g_release);
            m_id = nullptr;
        }
    }

private:
    static ::id createPool() noexcept{
        auto poolId = objc_msgSend(reinterpret_cast<::id>(MacStatic<void>::g_autoreleasePool), MacStatic<void>::g_alloc);
        return objc_msgSend(poolId, MacStatic<void>::g_init);
    }

    ::id m_id;

};

namespace NSLoop {

static constexpr ::NSUInteger NSAnyEventMask = std::numeric_limits<::NSUInteger>::max();
static constexpr ::NSUInteger NSApplicationDefined = 15;

static void processEvent() noexcept{
    auto event = objc_msgSend(MacStatic<void>::g_app, MacStatic<void>::g_nextEvent, NSAnyEventMask, MacStatic<void>::g_distantFuture, kCFRunLoopDefaultMode, YES);
    objc_msgSend(MacStatic<void>::g_app, MacStatic<void>::g_sendEvent, event);
}

static void postDummy() noexcept{
    auto event = objc_msgSend(reinterpret_cast<::id>(MacStatic<void>::g_event), MacStatic<void>::g_otherEventWithType, NSApplicationDefined, nullptr, 1, 0.0, 0, nullptr, static_cast<short>(0), 0, 0);
    objc_msgSend(MacStatic<void>::g_app, MacStatic<void>::g_postEvent, event, NO);
}

} // namespace NSLoop

} // namespace Detail

} // namespace Twpp

// Linux
#elif defined(__linux__)
#   warning "No testing has been done on this platform, this framework might not work correctly."
#   define TWPP_DETAIL_OS_LINUX 1
extern "C" {
#   include <dlfcn.h>
}
#   define TWPP_DETAIL_CALLSTYLE
namespace Twpp {

namespace Detail {

typedef void* RawHandle;


namespace DsmLibOs {

typedef void* Handle;
static constexpr const Handle nullHandle = nullptr;

template<typename T>
static inline T resolve(Handle h) noexcept{
    return reinterpret_cast<T>(::dlsym(h, "DSM_Entry"));
}

static inline Handle load(bool) noexcept{
    return ::dlopen("libtwaindsm.so", RTLD_LAZY);
}

static inline void unload(Handle h) noexcept{
    ::dlclose(h);
}

} // namespace DsmLibOs

} // namespace Detail

} // namespace Twpp

// fail everything else
#else
#   error "unsupported platform, supports only Windows, Mac OS and Linux"
#endif


// =================
// compiler specific

// MSVC
#if defined(_MSC_VER)
#   define TWPP_DETAIL_PACK_BEGIN \
        __pragma(pack (push, beforeTwpp)) \
        __pragma(pack (2))
#   define TWPP_DETAIL_PACK_END  __pragma(pack (pop, beforeTwpp));

// GNU or CLang
#elif defined(__GNUC__) || defined(__clang__)
#   if defined(TWPP_DETAIL_OS_MAC)
#       define TWPP_DETAIL_PACK_BEGIN _Pragma("options align = power")
#       define TWPP_DETAIL_PACK_END _Pragma("options align = reset")
#   else
#       define TWPP_DETAIL_PACK_BEGIN \
            _Pragma("pack (push, beforeTwpp)") \
            _Pragma("pack (2)")
#       define TWPP_DETAIL_PACK_END  _Pragma("pack (pop, beforeTwpp)")
#   endif
#   if !defined(TWPP_DETAIL_EXPORT)
#       define TWPP_DETAIL_EXPORT __attribute__((__visibility__("default")))
#   endif

// Borland
#elif defined(__BORLAND__) || defined(__BORLANDC__) || defined(__CODEGEARC__)
#   define TWPP_DETAIL_PACK_BEGIN _Pragma("option -a2")
#   define TWPP_DETAIL_PACK_END _Pragma("option -a")

// fail everything else
#else
#   error "unsupported compiler, please define your own TWPP_DETAIL_PACK_BEGIN and TWPP_DETAIL_PACK_END and possibly TWPP_DETAIL_EXPORT in twpp/env.hpp and send me your patch"
#endif


#if (!defined(_MSC_VER) && __cplusplus < 201103L) || (defined(_MSC_VER) && _MSC_VER < 1900) // msvc2015
#   error "C++11 or later is required"
#endif


#endif // TWPP_DETAIL_FILE_ENV_HPP

