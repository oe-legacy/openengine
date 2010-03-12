// Mesh.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Mesh.h>

#include <Resources/DataBlock.h>

using namespace OpenEngine::Resources;

namespace OpenEngine {
    namespace Geometry{

        Mesh::Mesh(IDataBlockPtr vertices,
                   IDataBlockPtr normals,
                   IDataBlockList texCoords,
                   IDataBlockPtr colors)
            : vertices(vertices), normals(normals), texCoords(texCoords), colors(colors){
#ifdef OE_SAFE
            if (vertices != NULL && vertices->GetType() != FLOAT)
                throw Exception("Vertices not of type float.");
            if (normals != NULL && normals->GetType() != FLOAT)
                throw Exception("Normals not of type float.");
            if (colors != NULL && colors->GetType() != FLOAT)
                throw Exception("Colors not of type float.");
            IDataBlockList::iterator itr = texCoords.begin();
            while (itr != texCoords.end()){
                if ((*itr)->GetType() != FLOAT)
                    throw Exception("Texture coords not of type float.");
                ++itr;
            }
#endif

        }
        

    }
}
