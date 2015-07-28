TWPP
====
Portable, header-only TWAIN framework for C++11 and later.

Contents
--------
- [Features](#features)
- [Requirements](#requirements)
- [Compilers](#compilers)
- [Platforms](#platforms)
- [Installation](#installation)
- [Usage](#usage)
- [Application development](#application-development)
- [Source development](#source-development)

Features
--------
TWPP was primarily designed to take away the burden of managing the dynamic memory while developing TWAIN applications and data sources, but the framework provides much more:

 - fast and easy application and data source development
  - abstracts data source manager and sources to easy to use classes
  - provides base class for data sources, implements all necessary procedures
 - implicit dynamic memory management (allocation, freeing, locking, and unlocking)
 - great capability handling
 - portability (with exception of certain string and data transfer operations)
 - type safety (scoped enumerations, distinguishable types)
 - compile-time strings and simple types
 - easy to use, but powerful API designed to be as similar as possible to the original `twain.h`

Requirements
------------
 - C++11
 - Windows, Linux, Mac OS X
 - Linux, Mac OS: `<mutex>` and `<condition_variable>`
 - Linux: -ldl

Compilers
---------
 - GCC: working on >= 4.8
 - MSVC: unknown
 - CLang: working on >= 3.5

Platforms
---------
 - Windows: working on Windows 7 32/64bit, expected to work fine on any 32/64bit version
 - Linux: working on Ubuntu 10.04 i386, Ubuntu 14.04 i386
 - Mac OS: unknown, issues expected

Installation
------------
Being header-only, installation consists of simply copying `twpp.hpp` and `twpp/` directory to one of your include directories or to your project directory itself.

Usage
-----
TWPP framework is designed to ease both application and data source development. There are certain differences between the two, but the common thing is that you always include only `twpp.hpp` and use stuff from `Twpp` namespace. See [Application development](#application-development) or  [Source development](#source-development) for more information.

Usage of classes is very similar to the C API, only with addition of OOP and certain abstractions.

Application development
-----------------------
TWAIN workflow can be roughly described as:

 1. open data source manager
 2. open data source
 3. negotiate capabilities
 4. transfer data
 5. close data source
 6. close data source manager

Let's start:

```c++
Manager mgr(
    Identity(
        Version(1, 0, Language::English, Country::UnitedKingdom, "v1.0"),
        DataGroup::Image,
        "Broke & Company",
        "BC Scan",
        "BC Soft Scan"
    )
);
```

We have created a `Manager` object and set our application identity. The identity can be anything that describes the application. By providing `DataGroup::Image`, we tell the manager that we are prepared to handle image operations (support for control operations is indicated implicitly). Nothing is open yet, we only created means to access data source manager (DSM).

```c++
mgr.load(); // loads DSM DLL/SO/Framework
mgr.open(); // opens DSM
```

With these two operations done, we can now perform operations on DSM, and ultimately open a data source (DS). Don't forget to check return values, any operation on DSM may fail! There are several ways to get a `Source` object:

```c++
// all available DSs
std::vector<Source> sources;
mgr.sources(sources);

// default DS
Source defSrc;
mgr.defaultSource(defSrc);

// show DS selection dialog, only on Windows and Mac OS
Source userSrc;
mgr.showSourceDialog(userSrc);

// if we know the product name and manufacturer
Source src = mgr.createSource("product name", "manufacturer");
```

Whatever approach we choose, we still have to actually open the DS.

```c++
src.open(); // not hard, is it?
```

Once open, DS allows us to negotiate capabilities.

```c++
// get supported capabilities
Capability supported(CapType::SupportedCaps);
src.capability(Msg::Get, supported);

for (CapType cap : supported.data<CapType::SupportedCaps>()){
    // iterate over supported capabilities
}

// set image transfer mechanism
Capability xferMech = Capability::createOneValue<CapType::IXferMech>(XferMech::Native);
src.capability(Msg::Set, xferMech);
```

Capabilities negotiated, we can now enable DS (show its GUI) and wait for the beginning of image transfer.

```c++
src.enable(UserInterface(true, true, handleToApplicationWindow));
src.waitReady();
```

Finally the image transfer.

```c++
ImageNativeXfer xfer;
src.imageNativeXfer(xfer);
auto lock = xfer.data(); // also xfer.data<YourDataType>()
// lock.data() returns pointer to image data
// you can also use `lock->member` to access member variables

// e.g. on Windows: 
auto bmp = xfer.data<BITMAPINFOHEADER>();
auto width = bmp->biWidth;
auto height = bmp->biHeight;
```

If we used the original API, we would have to free resources. Luckily, we use TWPP and it does this for us automatically.

This was only a demonstration of a very basic application to get you acquainted with TWPP. In order to transfer more images at once, negotiate more advanced capabilities etc. you will still have to consult [TWAIN manual](http://www.twain.org/). You will also have to move explicitly between TWAIN states in these advanced cases.

Source development
------------------
TWPP defaults to the application part of TWAIN architecture. In order to select the data source one, we need to define `TWPP_IS_DS`. This should be defined globally for the whole project, or before every inclusion of `twpp.hpp`. Failure to do so will result in undefined behaviour, and most likely some very nasty bugs. Do not mix application and data source versions in a single project! You have been warned.

DS in TWPP is represented by a class that inherits `SourceFromThis` (similar to `std::enable_shared_from_this`). This base class takes care of all the boilerplate (parameter validation, TWAIN states, and other common operations), allowing you to focus on your own implementation.

```c++
#define TWPP_IS_DS
#include <twpp.hpp>

using namespace Twpp;

class MySource : public SourceFromThis<MySource> {

public:
    static const Identity& defaultIdentity(){
        // the source Identity
        // used as base for all instances
    }

    // SourceFromThis interface
protected:
    virtual Result capabilityGet(const Identity& origin, Capability& data) override{
        // capability Msg::Get operation
    }

    virtual Result capabilityGetCurrent(const Identity& origin, Capability& data) override{
        // capability Msg::GetCurrent operation
    }

    virtual Result capabilityGetDefault(const Identity& origin, Capability& data) override{
        // capability Msg::GetDefault operation
    }

    virtual Result capabilityQuerySupport(const Identity& origin, Capability& data) override{
        // capability Msg::QuerySupport operation
    }

    virtual Result capabilityReset(const Identity& origin, Capability& data) override{
        // capability Msg::Reset operation
    }

    virtual Result capabilityResetAll(const Identity& origin) override{
        // capability Msg::ResetAll operation
        // note the missing data parameter
    }

    virtual Result capabilitySet(const Identity& origin, Capability& data) override{
        // capability Msg::Set operation
    }

    virtual Result eventProcess(const Identity& origin, Event& data) override{
        // event Msg::ProcessEvent operation
        // only required on Windows, has no meaning anywhere else
    }

    virtual Result identityOpenDs(const Identity& origin) override{
        // identity Msg::OpenDs operation
        // initialize hardware etc.
    }

    virtual Result identityCloseDs(const Identity& origin) override{
        // identity Msg::CloseDs operation
        // free resources
    }

    virtual Result pendingXfersGet(const Identity& origin, PendingXfers& data) override{
        // pending transfers Msg::Get operation
    }

    virtual Result pendingXfersEnd(const Identity& origin, PendingXfers& data) override{
        // pending transfers Msg::End operation
    }

    virtual Result pendingXfersReset(const Identity& origin, PendingXfers& data) override{
        // pending transfers Msg::Reset operation
    }

    virtual Result setupMemXferGet(const Identity& origin, SetupMemXfer& data) override{
        // setup memory transfer Msg::Get operation
    }

    virtual Result userInterfaceDisable(const Identity& origin, UserInterface& data) override{
        // user interface Msg::DisableDs operation
        // close GUI if shown
    }

    virtual Result userInterfaceEnable(const Identity& origin, UserInterface& data) override{
        // user interface Msg::EnableDs operation
        // show GUI if requested
    }

    virtual Result userInterfaceEnableUiOnly(const Identity& origin, UserInterface& data) override{
        // user interface Msg::EnableDsUiOnly operation
        // show GUI, used to change settings only
    }

    virtual Result imageInfoGet(const Identity& origin, ImageInfo& data) override{
        // image info Msg::Get operation
    }

    virtual Result imageLayoutGet(const Identity& origin, ImageLayout& data) override{
        // image layout Msg::Get operation
    }

    virtual Result imageLayoutGetDefault(const Identity& origin, ImageLayout& data) override{
        // image layout Msg::GetDefault operation
    }

    virtual Result imageLayoutSet(const Identity& origin, ImageLayout& data) override{
        // image layout Msg::Set operation
    }

    virtual Result imageLayoutReset(const Identity& origin, ImageLayout& data) override{
        // image layout Msg::Reset operation
    }

    virtual Result imageMemXferGet(const Identity& origin, ImageMemXfer& data) override{
        // image memory transfer Msg::Get operation
    }

    virtual Result imageNativeXferGet(const Identity& origin, ImageNativeXfer& data) override{
        // image native transfer Msg::Get operation
    }

};

TWPP_ENTRY(MySource) // must be placed in exactly one source file
```

`MySource` shows us all the operations a minimal DS must implement. Besides these `virtual` methods (member functions) a DS class must also provide `defaultIdentity` static method. Note `TWPP_ENTRY(MySource)`, this defines the TWAIN entrypoint `DS_Entry` and makes it use our DS class `MySource`. It *defines* a function, so it must be placed in exactly one source file.

Each TWAIN operation returns `Result`. It is a combination of `ReturnCode` and `Status`. `ReturnCode` is ultimately returned to the calling application. `Status` is saved in case the application requests it later using the according TWAIN operation.

`SourceFromThis` takes care of all calls to an unopened DS. Once a request to open it is made, a new instance of the derived class is created (`MySource`). Instance deletion is automatically performed after successfuly closing the session. There might be several opened instances of the same DS at the same time.

A method `call` is the entrypoint of DS instance. It routes the TWAIN call according to its `DataGroup` to `control`, `image`, or `audio` methods. These first check the validity of the data, and call the handler of the data type (`Dat`), e. g. capabilities are handled by `capability`. Data type handler is responsible for assuring preconditions and postconditions of action handlers (mainly state checks and transitions). Now, an action handler corresponding to `Msg` parameter is called (e. g. `capabilityGet`). This is the default code path in `SourceFromThis`. All these handlers from the root (`call`) to the action handlers are `virtual`, and may be overriden to provide special functionality. Most DS implementations will need to override only action handlers.
