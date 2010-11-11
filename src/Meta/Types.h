// Meta types for better platform independence.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_META_TYPES_H_
#define _OE_META_TYPES_H_

#if defined(_MSC_VER)    
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int64 uint64_t;
#else
    #include <stdint.h>
#endif

#endif // _OE_META_TYPES_H_
