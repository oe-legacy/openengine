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
        class Indices;
        typedef boost::shared_ptr<Indices> IndicesPtr;
    }
    namespace Geometry {
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;
        typedef list<MeshPtr> MeshList;
        
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class GeometrySet;
        typedef boost::shared_ptr<GeometrySet> GeometrySetPtr;        

        /**
         * Geometry Types (just happens to have the same values
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
         * The Mesh class contains the primitive type and indices that
         * should be used when rendering the geometry set with the
         * specified material.
         */
        class Mesh {
        protected:
            Resources::IndicesPtr indexBuffer;
            Type type;
            MaterialPtr mat;
            GeometrySetPtr geom;
            unsigned int indexOffset;
            unsigned int drawRange;
            
        public:
            Mesh(Resources::IndicesPtr indexBuffer,
                 Type type,
                 GeometrySetPtr geom,
                 MaterialPtr mat);

            Mesh(Resources::IndicesPtr indexBuffer,
                 Type type,
                 GeometrySetPtr geom,
                 MaterialPtr mat,
                 unsigned int indexOffset,
                 unsigned int drawRange);
            
            /**
             * Copy constructor.
             */
            Mesh(const Mesh& mesh);

            /**
             * Clone mesh
             */
            virtual MeshPtr Clone();

            /**
             * Return the index buffer object.
             */
            inline Resources::IndicesPtr GetIndices() const { return indexBuffer; }
            
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
             *
             * Perhaps allow a triangle class to capture the most
             * generel dimensions, eg 3 for normals and 4 for
             * vertices. Template it with the type we want?
             */
        };


    }
}

#endif
