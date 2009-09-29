// Math extensions and utilities
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MATH_H_
#define _OE_MATH_H_

namespace OpenEngine { 
namespace Math {

const float PI = 3.14159265f;   //!< Circumference of a half unit circle.
const float EPS = 0.00001f;     //!< Default epsilon value for equality tests.

unsigned int GCD(const unsigned int left, const unsigned int right);

}
}

#endif // _OE_MATH_H_
