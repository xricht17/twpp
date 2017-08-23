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

#ifndef TWPP_DETAIL_FILE_TWPP_HPP
#define TWPP_DETAIL_FILE_TWPP_HPP

#include "twpp/env.hpp"

#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <utility>
#include <iterator>
#include <type_traits>
#include <limits>
#include <stdexcept>
#include <mutex>
#include <condition_variable>
#include <map>
#include <string>
#include <list>
#include <cstring>
#include <array>
#include <utility>
#include <cassert>

#include "twpp/utils.hpp"

#include "twpp/types.hpp"
#include "twpp/strings.hpp"
#include "twpp/fix32.hpp"
#include "twpp/frame.hpp"
#include "twpp/exception.hpp"
#include "twpp/typesops.hpp"

#include "twpp/memoryops.hpp"
#include "twpp/memory.hpp"

#include "twpp/enums.hpp"
#include "twpp/status.hpp"
#include "twpp/identity.hpp"
#include "twpp/imageinfo.hpp"
#include "twpp/imagelayout.hpp"
#include "twpp/deviceevent.hpp"
#include "twpp/element8.hpp"

#include "twpp/audio.hpp"
#include "twpp/capability.hpp"
#include "twpp/customdata.hpp"
#include "twpp/cie.hpp"
#include "twpp/curveresponse.hpp"
#include "twpp/event.hpp"
#include "twpp/extimageinfo.hpp"
#include "twpp/filesystem.hpp"
#include "twpp/imagememxfer.hpp"
#include "twpp/imagenativexfer.hpp"
#include "twpp/internal.hpp"
#include "twpp/jpegcompression.hpp"
#include "twpp/palette8.hpp"
#include "twpp/passthrough.hpp"
#include "twpp/pendingxfers.hpp"
#include "twpp/setupfilexfer.hpp"
#include "twpp/setupmemxfer.hpp"
#include "twpp/userinterface.hpp"

#if !defined(TWPP_IS_DS)
#   include "twpp/application.hpp"
#else
#   include "twpp/datasource.hpp"
#endif


#if !defined(TWPP_NO_NOTES)
#   if !defined(TWPP_IS_DS)
#       pragma message ("note: using APPLICATION version of TWPP library, define TWPP_IS_DS before including twpp.hpp if you want DATA SOURCE version")
#       if defined(TWPP_DETAIL_OS_WIN32)
#           pragma message ("note: place the following into your module-definition (.def) file: EXPORTS DS_Entry @1")
#       endif
#   else
#       pragma message ("note: using DATA SOURCE version of TWPP library, undefine TWPP_IS_DS if you want APPLICATION version")
#       pragma message ("note: make sure to place TWPP_ENTRY(<your-source-class-type>) macro in exactly one source file")
#   endif
#   if defined(TWPP_DETAIL_OS_MAC)
#       pragma message "warning: Str32, Str64, Str128 and Str255 are not null-terminated"
#   endif
#   pragma message ("note: to disable notes and warnings, define TWPP_NO_NOTES before including TWPP header")
#endif


#endif // TWPP_DETAIL_FILE_TWPP_HPP
