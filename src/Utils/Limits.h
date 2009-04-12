// Limit utilities.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_LIMITS_H_
#define _OE_LIMITS_H_

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Utils {

// template functions to obtain the minimum value of some type
template <typename T> T minValue() { throw Core::Exception("Unknown minimum element of type T."); }
template <typename T> T maxValue() { throw Core::Exception("Unknown maximum element of type T."); }

// macro for min and max headers
#define MK_MINMAX(type, name)           \
    template <> type minValue<type> (); \
    template <> type maxValue<type> ();

// macro for both signed and unsigned
#define MK_MINMAX_SU(type, name)                                        \
    MK_MINMAX(type, name)                                               \
    MK_MINMAX(unsigned type, U##name)

// min/max implementations for all of the usual suspects
MK_MINMAX_SU(char,      CHAR)
MK_MINMAX_SU(short,     SHRT)
MK_MINMAX_SU(int,       INT)
MK_MINMAX_SU(long,      LONG)
MK_MINMAX_SU(long long, LLONG)
MK_MINMAX   (float,     FLT)
MK_MINMAX   (double,    DBL)

#undef MK_MINMAX
#undef MK_MINMAX_SU

} // NS Utils
} // NS OpenEngine

#endif // _OE_LIMITS_H_
