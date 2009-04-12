// Limit utilities.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/Limits.h>
#include <limits.h>
#include <float.h>

namespace OpenEngine {
namespace Utils {

// define the min values for unsigned types (just to keep things consistent)
#define UCHAR_MIN  0
#define USHRT_MIN  0
#define UINT_MIN   0
#define ULONG_MIN  0
#define ULLONG_MIN 0

// macro to implement min and max
#define MK_MINMAX(type, name)                                           \
    template <> type minValue<type> () { return name##_MIN; }           \
    template <> type maxValue<type> () { return name##_MAX; }

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

} // NS Utils
} // NS OpenEngine
