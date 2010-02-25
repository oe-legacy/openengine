// Mesh.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MESH_H_
#define _MESH_H_

#include <Resources/IndexBufferObject.h>

#include <boost/shared_ptr.hpp>
#include <vector>

using std::vector;

namespace OpenEngine {
    namespace Resources {
        class IBufferObject;
        typedef boost::shared_ptr<IBufferObject> IBufferObjectPtr;
        typedef vector<Resources::IBufferObjectPtr> IBufferObjectList;
        //class IndexBufferObject;
        //typedef boost::shared_ptr<IndexBufferObject> IndexBufferObjectPtr;
    }
    namespace Geometry{

        class Mesh {
        protected:
            Resources::IBufferObjectPtr vertices;
            Resources::IBufferObjectPtr normals;
            Resources::IBufferObjectPtr colors;
            Resources::IBufferObjectList texCoords;

            // Move into shader.
            //map<string, IBufferObjectPtr> vertexAttrib;

        public:
            Mesh(Resources::IBufferObjectPtr vertices,
                 Resources::IBufferObjectPtr normals = Resources::IBufferObjectPtr(),
                 Resources::IBufferObjectList texCoords = Resources::IBufferObjectList(),
                 Resources::IBufferObjectPtr colors = Resources::IBufferObjectPtr());

            /**
             * Get vertices.
             */
            inline Resources::IBufferObjectPtr GetVertices() const { return vertices; }

            /**
             * Get normals.
             */
            inline Resources::IBufferObjectPtr GetNormals() { return normals; }

            /**
             * Get colors.
             */
            inline Resources::IBufferObjectPtr GetColors() { return colors; }
        };

        /**
         * Shared pointer
         */
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
}

#endif
