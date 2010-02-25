//  Drawing Primitive.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/DrawPrimitive.h>

#include <Geometry/Mesh.h>
#include <Geometry/Material.h>
#include <Math/Exceptions.h>

using namespace OpenEngine::Resources;
using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Geometry {

        DrawPrimitive::DrawPrimitive(IndexBufferObjectPtr indexBuffer,
                                     MaterialPtr mat,
                                     MeshPtr mesh)
            : indexBuffer(indexBuffer), mat(mat), mesh(mesh){ }


        void DrawPrimitive::AddIndexBatch(GeometryPrimitive prim){
            IndexBatch b = IndexBatch(prim, 0, indexBuffer->GetSize());
            batches.push_back(b);
        }

        void DrawPrimitive::AddIndexBatch(GeometryPrimitive prim, 
                                           unsigned int offset, unsigned int range){
#ifdef OE_SAFE
            unsigned int size = indexBuffer->GetSize();
            if (offset > size)
                throw IndexOutOfBounds(offset, 0, size);
            if (offset + range > size)
                throw IndexOutOfBounds(offset + range, 0, size);
#endif
            IndexBatch b = IndexBatch(prim, offset, range);
            batches.push_back(b);
        }

    }
}
