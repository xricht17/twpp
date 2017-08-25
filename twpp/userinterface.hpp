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

#ifndef TWPP_DETAIL_FILE_USERINTERFACE_HPP
#define TWPP_DETAIL_FILE_USERINTERFACE_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure holding parameters for enabling or disabling data source.
class UserInterface {

public:
    /// Creates a new UserInterface.
    /// \param showUi Whether to show internal DS GUI. Disabling DS GUI might not be supported.
    /// \param modalUi Whether DS GUI should be modal. Not used on Linux. Might not be supported on Windows.
    /// \param parent Windows-only, others set to null. Handle to parent window. This object does NOT take ownership.
#if defined(TWPP_DETAIL_OS_WIN)
    constexpr UserInterface(Bool showUi, Bool modalUi, Handle parent) noexcept :
        m_showUi(showUi), m_modalUi(modalUi), m_parent(parent){}
#elif defined(TWPP_DETAIL_OS_MAC) || defined(TWPP_DETAIL_OS_LINUX)
    constexpr UserInterface(Bool showUi, Bool modalUi, Handle parent = Handle()) noexcept :
        m_showUi(showUi), m_modalUi(modalUi), m_parent(parent){}
#else
#   error "UserInterface constructor for your platform here"
#endif

    /// Whether to show internal DS GUI.
    constexpr Bool showUi() const noexcept{
        return m_showUi;
    }

    /// Whether DS GUI should be modal
    constexpr Bool modalUi() const noexcept{
        return m_modalUi;
    }

    /// Handle to parent window.
    constexpr Handle parent() const noexcept{
        return m_parent;
    }

private:
    Bool m_showUi;
    Bool m_modalUi;
    Handle m_parent;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_USERINTERFACE_HPP

