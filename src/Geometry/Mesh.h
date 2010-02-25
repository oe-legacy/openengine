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

#include <boost/shared_ptr.hpp>
#include <vector>

using std::vector;

namespace OpenEngine {
    namespace Resources {
        class IBufferObject;
        typedef boost::shared_ptr<IBufferObject> IBufferObjectPtr;
        class IndexBufferObject;
        typedef boost::shared_ptr<IndexBufferObject> IndexBufferObjectPtr;
    }
    namespace Geometry{

        class Mesh {
        protected:
            unsigned int size;
            Resources::IBufferObjectPtr vertices;
            Resources::IBufferObjectPtr normals;
            Resources::IBufferObjectPtr colors;
            vector<Resources::IBufferObjectPtr> texCoords;

            Resources::IndexBufferObjectPtr indices;

            // Move into shader.
            //map<string, IBufferObjectPtr> vertexAttrib;

        public:
            /**
             * Mesh default constructor.
             */
            Mesh();
            
            /**
             * Mesh constructor. The type of all buffer objects are
             * asumed to be float.
             *
             * @param size The size of the mesh, ie the number of
             * distinct vertices.
             * @param vDim The dimension of the vertices.
             * @param nDim The dimension of the normals.
             */
            Mesh(unsigned int size, 
                 unsigned int vDim,
                 unsigned int nDim);

            inline Resources::IBufferObjectPtr GetVertices() const { return vertices; }
            inline void SetVertices(Resources::IBufferObjectPtr v) { vertices = v; }
            inline Resources::IBufferObjectPtr GetNormals() { return normals; }
            inline void SetNormals(Resources::IBufferObjectPtr n) { normals = n; }
            inline Resources::IBufferObjectPtr GetColors() { return colors; }
            inline void SetColors(Resources::IBufferObjectPtr c) { colors = c; }
            inline Resources::IBufferObjectPtr GetTexCoords(unsigned int i) { return texCoords[i]; }
            inline void SetTexCoords(Resources::IBufferObjectPtr t) { texCoords.push_back(t); }
            inline void SetTexCoords(Resources::IBufferObjectPtr t, unsigned int i) { texCoords[i] = t; }
            inline Resources::IndexBufferObjectPtr GetIndexBuffer() const { return indices; }
        };

        /**
         * Shared pointer
         */
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
}

#endif
