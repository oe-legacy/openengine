//  Drawing Primitive.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DRAW_PRIMITIVE_H_
#define _DRAW_PRIMITIVE_H_

#include <boost/shared_ptr.hpp>

namespace OpenEngine {
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;

        /**
         * Geometry primitives.
         */
        enum GeometryPrimitive {
            GL_POINTS,
            LINES,
            LINE_STRIP,
            TRIANGLES,
            TRIANGLE_STRIP,
            QUADS};

        /**
         * Draw primitive class, containing the primitive type that
         * should be used when rendering the mesh with the specified
         * material.
         */
        class DrawPrimitive {
        protected:
            GeometryPrimitive prim;
            unsigned int indexOffset;
            unsigned int drawRange;
            MaterialPtr mat;
            MeshPtr mesh;
            
        public:
            DrawPrimitive(GeometryPrimitive prim,
                          MaterialPtr mat,
                          MeshPtr mesh);
            
            DrawPrimitive(GeometryPrimitive primitive,
                          unsigned int offset,
                          unsigned int range,
                          MaterialPtr mat,
                          MeshPtr mesh);

            /**
             * Returns the primitive drawn.
             */
            inline GeometryPrimitive GetPrimitive() const { return prim; }

            /**
             * Returns the specified offset into the index buffer.
             */
            inline unsigned int GetIndexOffset() const { return indexOffset; }

            /**
             * Returns the number of elements drawn by this draw primitive.
             */
            inline unsigned int GetDrawingRange() { return drawRange; }

            /**
             * Returns the material used by this draw primitive.
             */
            inline MaterialPtr GetMaterial() const { return mat; }

            /**
             * Returns the mesh used by this draw primitive.
             */
            inline MeshPtr GetMesh() const { return mesh; }
            
        };

        typedef boost::shared_ptr<DrawPrimitive> DrawPrimitivePtr;

    }
}

#endif
