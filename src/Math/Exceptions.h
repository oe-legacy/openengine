// Math exceptions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Math {

using OpenEngine::Core::Exception;
using std::string;

/**
 * Arithmetic exception.
 *
 * @class ArithmeticException Exceptions.h Math/Exceptions.h
 */
class ArithmeticException : public Exception {
public:
    ArithmeticException() : Exception() {};
    //! Exception with a string message.
    ArithmeticException(string msg) : Exception(msg) {};
};

/**
 * Division by zero exception.
 *
 * @class DivisionByZero Exceptions.h Math/Exceptions.h
 */
class DivisionByZero : public ArithmeticException {
public:
    DivisionByZero() : ArithmeticException("Can not divide by zero.") {};
};

/**
 * Index out of bounds exception.
 *
 * @class IndexOutOfBounds Exceptions.h Math/Exceptions.h
 */
class IndexOutOfBounds : public std::out_of_range, public Exception {
public:
    /**
     * Index out of bounds exception.
     *
     * @param i Index value.
     * @param l Lower range.
     * @param u Upper range.
     */
    IndexOutOfBounds(int i, int l, int u);
};

} // NS Math
} // NS OpenEngine
