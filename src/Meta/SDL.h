// Meta header for SDL components.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#if __APPLE__
  #include <SDL/SDL.h>
  #include <SDL/SDL_events.h>
  #include <SDL/SDL_thread.h>
#else
  #include <SDL.h>
  #include <SDL_events.h>
  #include <SDL_thread.h>
#endif
