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


        void DrawPrimitive::AddPrimitive(GeometryPrimitive prim){
            Indices i = Indices(prim, 0, indexBuffer->GetSize());
            indices.push_back(i);
        }

        void DrawPrimitive::AddPrimitive(GeometryPrimitive prim, 
                                         unsigned int offset, unsigned int range){
#ifdef OE_SAFE
            unsigned int size = indexBuffer->GetSize();
            if (offset > size)
                throw IndexOutOfBounds(offset, 0, size);
            if (offset + range > size)
                throw IndexOutOfBounds(offset + range, 0, size);
#endif
            Indices i = Indices(prim, offset, range);
            indices.push_back(i);
        }

    }
}
