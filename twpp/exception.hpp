#ifndef TWPP_DETAIL_FILE_EXCEPTION_HPP
#define TWPP_DETAIL_FILE_EXCEPTION_HPP

#include "../twpp.hpp"

namespace Twpp {

/// Base class of TWPP exceptions.
class Exception : public std::exception {

public:
    virtual const char* what() const noexcept override{
        return "General TWPP error.";
    }

};

/// Invalid type exception.
/// Used when an invalid or unsupported type identifier is used.
class TypeException : public Exception {

public:
    virtual const char* what() const noexcept override{
        return "Invalid type.";
    }

};

/// Value out of valid range exception.
class RangeException : Exception {

public:
    virtual const char* what() const noexcept override{
        return "Value out of allowed range.";
    }

};

}

#endif // TWPP_DETAIL_FILE_EXCEPTION_HPP

