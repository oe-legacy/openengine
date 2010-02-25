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
#include <Resources/IndexBufferObject.h>

using namespace OpenEngine::Resources;

namespace OpenEngine {
    namespace Geometry {

        DrawPrimitive::DrawPrimitive(GeometryPrimitive prim,
                                     MaterialPtr mat,
                                     MeshPtr mesh)
            : prim(prim), mat(mat), mesh(mesh){
            indexOffset = 0;
            Resources::IndexBufferObjectPtr p = mesh->GetIndexBuffer();
            drawRange = p->GetSize();

        }

        DrawPrimitive::DrawPrimitive(GeometryPrimitive primitive,
                                     unsigned int offset,
                                     unsigned int range,
                                     MaterialPtr mat,
                                     MeshPtr mesh)
            : prim(prim), indexOffset(offset), drawRange(range), mat(mat), mesh(mesh){
        }

    }
}
