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
#include <list>

using std::list;

namespace OpenEngine {
    namespace Resources {
        class IDataBlock;
        typedef boost::shared_ptr<IDataBlock> IDataBlockPtr;
        typedef list<Resources::IDataBlockPtr> IDataBlockList;
    }
    namespace Geometry{

        /**
         * The mesh class contains all of the pr. vertex information
         * of a mesh.
         *
         * All of the information is assumed to be in floats.
         */
        class Mesh {
        protected:
            Resources::IDataBlockPtr vertices;
            Resources::IDataBlockPtr normals;
            Resources::IDataBlockList texCoords;
            Resources::IDataBlockPtr colors;

            // Move into shader?
            //map<string, IDataBlockPtr> vertexAttrib;

        public:
            Mesh(Resources::IDataBlockPtr vertices,
                 Resources::IDataBlockPtr normals = Resources::IDataBlockPtr(),
                 Resources::IDataBlockList texCoords = Resources::IDataBlockList(),
                 Resources::IDataBlockPtr colors = Resources::IDataBlockPtr());

            /**
             * Get vertices.
             */
            inline Resources::IDataBlockPtr GetVertices() const { return vertices; }

            /**
             * Get normals.
             */
            inline Resources::IDataBlockPtr GetNormals() { return normals; }

            /**
             * Get colors.
             */
            inline Resources::IDataBlockPtr GetColors() { return colors; }

            /**
             * Get list of texcoords.
             */
            inline Resources::IDataBlockList GetTexCoords() { return texCoords; }
        };

        /**
         * Shared pointer
         */
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
}

#endif
