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
 - GCC: working on >= 4.8.0
 - MSVC: unknown
 - CLang: unknown

Platforms
---------
 - Windows: working on Windows 7 32/64bit, expected to work fine on any 32/64bit version
 - Linux: working on Ubuntu 10.04 i386
 - Mac OS: unknown, issues expected

Installation
------------
Being header-only, installation consists of simply copying `twpp.hpp` and `twpp/` directory to one of your include directories or to your project directory itself.

Usage
-----
TWPP framework is designed to ease both application and data source development. There are certain differences between the two, but the common thing is that you always include only *twpp.hpp* and use stuff from *Twpp* namespace. See [Application development](#application-development) or  [Source development](#source-development) for more information.

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

With these two operations done, we can now perform operations on DSM, and ultimately open a data source (DS). Don't forget to check return values, any operation on DSM may fail! There are several ways to get a *Source* object:

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
>TODO

