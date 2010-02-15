// Meta header for OpenEngine.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OPENENGINE_RESOURCE_FORMATS_H_
#define _OPENENGINE_RESOURCE_FORMATS_H_

namespace OpenEngine {
    namespace Resources {
        /**
         * Type enumeration.
         */
        enum Type {NOTYPE,
                   UBYTE, BYTE,
                   UINT, INT,
                   FLOAT};
        
        /**
         * Color Format enumeration.
         */
        enum ColorFormat { RGBA, BGRA, RGB, BGR, LUMINANCE, DEPTH, RGBA32F };

        /**
         * Texture Wrapping options
         */
        enum Wrapping {CLAMP, CLAMP_TO_EDGE, REPEAT};

    }
}
        
#endif
