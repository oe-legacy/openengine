// Mesh.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Mesh.h>

#include <Resources/BufferObject.h>

using namespace OpenEngine::Resources;

namespace OpenEngine {
    namespace Geometry{

        Mesh::Mesh(){
            size = 0;
            vertices = IBufferObjectPtr();
            normals = IBufferObjectPtr();
            colors = IBufferObjectPtr();
            texCoords.empty();
        }

        Mesh::Mesh(unsigned int size, 
                   unsigned int vDim,
                   unsigned int nDim){
            this->size = size;

            switch(vDim){
            case 2:
                vertices = IBufferObjectPtr(new BufferObject<2, float>(size));
                break;
            case 3:
                vertices = IBufferObjectPtr(new BufferObject<3, float>(size));
                break;
            default:
                vertices = IBufferObjectPtr(new BufferObject<4, float>(size));
                break;
            }

            switch(nDim){
            case 2:
                normals = IBufferObjectPtr(new BufferObject<2, float>(size));
                break;
            default:
                normals = IBufferObjectPtr(new BufferObject<3, float>(size));
                break;
            }
        }

    }
}
