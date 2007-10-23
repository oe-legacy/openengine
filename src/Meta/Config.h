// Meta header to configure platform specific definitions and includes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// necessary as SDL on mac needs to do a take over on main()
#if __APPLE__
#include <Meta/SDL.h> 
#endif
