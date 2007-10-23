// Base exception.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CORE_EXCEPTIONS_H_
#define  _CORE_EXCEPTIONS_H_

#include <stdexcept>
#include <string>

namespace OpenEngine {
namespace Core {

using std::runtime_error;
using std::string;

/**
 * Base exception.
 * All custom exceptions must inherit from this.
 *
 * @class Exception Exceptions.h Core/Exception.h
 */
class Exception : public runtime_error {
public:
    /**
     * Default constructor.
     */
    Exception() : runtime_error("Unspecified exception.") {};

    /**
     * Set constructor.
     *
     * @param msg string defining error message.
     */
    Exception(string msg) : runtime_error(msg) {};
};

/**
 * Invalid argument exception.
 *
 * @class InvalidArgument Exceptions.h Core/Exceptions.h
 */
class InvalidArgument : public Exception {
public:
    InvalidArgument() : Exception("Invalid argument exception.") {};
    //! Exception with a string message.
    InvalidArgument(string msg) : Exception(msg) {};
};

/**
 * Not implemented exception
 *
 * @class NotImplemented Exceptions.h Core/Exceptions.h
 */
class NotImplemented : public Exception {
public:
    NotImplemented() : Exception("Functionality not implemented.") {};
    //! Exception with a string message.
    NotImplemented(string msg) : Exception(msg) {};
};

} // NS Core
} // NS OpenEngine

#endif // _CORE_EXCEPTIONS_H_
