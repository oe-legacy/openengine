// Index buffer object.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/IndexBufferObject.h>

namespace OpenEngine {
    namespace Resources {
        
        Indices::Indices(unsigned int range) 
            : prim(TRIANGLES), offset(0), range(range) { }
        
        Indices::Indices(GeometryPrimitive prim,
                         unsigned int range)
            : prim(prim), offset(0), range(range) { }

        Indices::Indices(GeometryPrimitive prim,
                         unsigned int offset,
                         unsigned int range)
            : prim(prim), offset(offset), range(range) { }
        
        GeometryPrimitive Indices::GetPrimitive() const {
            return prim;
        }
        
        unsigned int Indices::GetOffset() const {
            return offset;
        }
        
        unsigned int Indices::GetRange() const{
            return range;
        }
    }
}
