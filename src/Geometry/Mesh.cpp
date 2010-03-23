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
#include <Resources/DataBlock.h>
#include <Math/Exceptions.h>

using namespace OpenEngine::Resources;
using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Geometry {

        Mesh::Mesh(Resources::DataIndicesPtr indexBuffer,
                                     GeometryPrimitive prim,
                                     GeometrySetPtr geom,
                                     MaterialPtr mat)
            : indexBuffer(indexBuffer), prim(prim), mat(mat), geom(geom) {
            indexOffset = 0;
            drawRange = indexBuffer->GetSize();
        }
        
        Mesh::Mesh(Resources::DataIndicesPtr indexBuffer,
                                     GeometryPrimitive prim,
                                     GeometrySetPtr geom,
                                     MaterialPtr mat,
                                     unsigned int indexOffset,
                                     unsigned int drawRange)
            : indexBuffer(indexBuffer), prim(prim), mat(mat), geom(geom),
              indexOffset(indexOffset), drawRange(drawRange) {
#ifdef OE_SAFE
            unsigned int size = indexBuffer->GetSize();
            if (indexOffset > size)
                throw IndexOutOfBounds(indexOffset, 0, size);
            if (indexOffset + drawRange > size)
                throw IndexOutOfBounds(indexOffset + drawRange, 0, size);
#endif
        }

        Mesh::Mesh(const Mesh& mesh){
            indexBuffer = mesh.GetDataIndices();
            prim = mesh.GetPrimitive();
            mat = mesh.GetMaterial();
            geom = mesh.GetGeometrySet();
            indexOffset = mesh.GetIndexOffset();
            drawRange = mesh.GetDrawingRange();
        }
    }

}
