// Meta timer for better platform independence.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_META_TIME_H_
#define _OE_META_TIME_H_

#if defined(_WIN32)
  #include <time.h>
#else
  #include <sys/time.h>
#endif

#endif // _OE_META_TIME_H_
