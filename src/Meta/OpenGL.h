// Meta header for OpenGL components.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OPENENGINE_OPENGL_H_
#define _OPENENGINE_OPENGL_H_

#include <GL/glew.h>

#if defined __APPLE__
  #include <GL/glew.h> //only included here for windows to supprot glMultTransposeMatrix
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>

#else

  #ifdef _WIN32
    #include <Windows.h>
  #endif

  #include <GL/gl.h>
  #include <GL/glu.h>

#endif

#endif // _OPENENGINE_OPENGL_H_
