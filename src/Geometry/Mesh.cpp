// Mesh.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Mesh.h>

#include <Geometry/GeometrySet.h>
#include <Geometry/Material.h>
#include <Math/Exceptions.h>

using namespace OpenEngine::Resources;
using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Geometry {

        Mesh::Mesh(Resources::DataIndicesPtr indexBuffer,
                                     GeometryPrimitive prim,
                                     MaterialPtr mat,
                                     GeometrySetPtr mesh)
            : indexBuffer(indexBuffer), prim(prim), mat(mat), mesh(mesh) {
            indexOffset = 0;
            drawRange = indexBuffer->GetSize();
        }
        
        Mesh::Mesh(Resources::DataIndicesPtr indexBuffer,
                                     GeometryPrimitive prim,
                                     MaterialPtr mat,
                                     GeometrySetPtr mesh,
                                     unsigned int indexOffset,
                                     unsigned int drawRange)
            : indexBuffer(indexBuffer), prim(prim), mat(mat), mesh(mesh),
              indexOffset(indexOffset), drawRange(drawRange) {
#ifdef OE_SAFE
            unsigned int size = indexBuffer->GetSize();
            if (indexOffset > size)
                throw IndexOutOfBounds(indexOffset, 0, size);
            if (indexOffset + drawRange > size)
                throw IndexOutOfBounds(indexOffset + drawRange, 0, size);
#endif
        }
    }
}
