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

        Mesh::Mesh(IBufferObjectPtr vertices,
                   IBufferObjectPtr normals,
                   IBufferObjectList texCoords,
                   IBufferObjectPtr colors)
            : vertices(vertices), normals(normals), texCoords(texCoords), colors(colors){
#ifdef OE_SAFE
            if (vertices->GetType() != FLOAT)
                throw Exception("Vertices not of type float.");
            if (normals->GetType() != FLOAT)
                throw Exception("Normals not of type float.");
            if (colors->GetType() != FLOAT)
                throw Exception("Colors not of type float.");
            IBufferObjectList::iterator itr = texCoords.begin();
            while (itr != texCoords.end()){
                if ((*itr)->GetType() != FLOAT)
                    throw Exception("Texture coords not of type float.");
                ++itr;
            }
#endif

        }
        

    }
}
