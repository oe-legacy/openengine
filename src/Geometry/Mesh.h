// Mesh.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MESH_H_
#define _OE_MESH_H_

#include <boost/shared_ptr.hpp>

#include <list>

using std::list;

namespace OpenEngine {
    namespace Resources {
        class DataIndices;
        typedef boost::shared_ptr<DataIndices > DataIndicesPtr;
    }
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class GeometrySet;
        typedef boost::shared_ptr<GeometrySet> GeometrySetPtr;        

        /**
         * Geometry primitives (just happens to have the same values
         * as OpenGL...)
         */
        enum Type {
            POINTS         = 0x0000,
            LINES          = 0x0001,
            LINE_STRIP     = 0x0003,
            TRIANGLES      = 0x0004,
            TRIANGLE_STRIP = 0x0005,
            QUADS          = 0x0007};
        
        /**
         * Draw primitive class, containing the primitive type that
         * should be used when rendering the mesh with the specified
         * material.
         */
        class Mesh {
        protected:
            Resources::DataIndicesPtr indexBuffer;
            Type type;
            MaterialPtr mat;
            GeometrySetPtr geom;
            unsigned int indexOffset;
            unsigned int drawRange;
            
        public:
            Mesh(Resources::DataIndicesPtr indexBuffer,
                 Type type,
                 GeometrySetPtr geom,
                 MaterialPtr mat);

            Mesh(Resources::DataIndicesPtr indexBuffer,
                 Type type,
                 GeometrySetPtr geom,
                 MaterialPtr mat,
                 unsigned int indexOffset,
                 unsigned int drawRange);
            
            Mesh(const Mesh& mesh);
            
            /**
             * Return the index buffer object.
             */
            inline Resources::DataIndicesPtr GetDataIndices() const { return indexBuffer; }
            
            /**
             * Returns the material used by this draw primitive.
             */ 
            inline MaterialPtr GetMaterial() const { return mat; }

            /**
             * Returns the mesh used by this draw primitive.
             */
            inline GeometrySetPtr GetGeometrySet() const { return geom; }

            /**
             * Returns the primitive type.
             */
            inline Type GetType() const { return type; }
            
            /**
             * Returns the specified offset into the index buffer.
             */
            inline unsigned int GetIndexOffset() const { return indexOffset; }
            
            /**
             * Returns the number of elements drawn by this draw primitive.
             */
            inline unsigned int GetDrawingRange() const { return drawRange; }

            /**
             * Iterate over primitives. Like how?
             */
        };

        typedef boost::shared_ptr<Mesh> MeshPtr;
        typedef list<MeshPtr> MeshList;

    }
}

#endif
