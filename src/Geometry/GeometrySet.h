// GeometrySet.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_SET_H_
#define _GEOMETRY_SET_H_

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
         * Forward decleration used for shared pointer.
         */
        class GeometrySet;

        /**
         * Shared pointer
         */
        typedef boost::shared_ptr<GeometrySet> GeometrySetPtr;

        /**
         * The geometry set class contains all of the pr. vertex
         * information of a mesh.
         *
         * @TODO All of the information is assumed to be in floats?
         */
        class GeometrySet {
        protected:
            Resources::IDataBlockPtr vertices;
            Resources::IDataBlockPtr normals;
            Resources::IDataBlockList texCoords;
            Resources::IDataBlockPtr colors;

            Resources::IDataBlockPtr debugNormals;

            // Move into shader?
            //map<string, IDataBlockPtr> vertexAttrib;

        public:
            GeometrySet(Resources::IDataBlockPtr vertices,
                 Resources::IDataBlockPtr normals = Resources::IDataBlockPtr(),
                 Resources::IDataBlockList texCoords = Resources::IDataBlockList(),
                 Resources::IDataBlockPtr colors = Resources::IDataBlockPtr());

            /**
             * Clones the data in the geometry set.
             *
             * @return A new GeometrySet with the cloned data.
             */
            GeometrySetPtr Clone();

            /**
             * Get vertices.
             */
            inline Resources::IDataBlockPtr GetVertices() const { return vertices; }

            /**
             * Get normals.
             */
            inline Resources::IDataBlockPtr GetNormals() const { return normals; }

            /**
             * Get colors.
             */
            inline Resources::IDataBlockPtr GetColors() const { return colors; }

            /**
             * Get list of texcoords.
             */
            inline Resources::IDataBlockList GetTexCoords() const { return texCoords; }

            /**
             * Get a list of lines representing the normals.
             */
            Resources::IDataBlockPtr GetDebugNormals();

        };

    }
}

#endif
