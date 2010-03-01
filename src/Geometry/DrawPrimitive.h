// Drawing Primitive.
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
#include <Resources/IndexBufferObject.h>

using OpenEngine::Resources::GeometryPrimitive;

namespace OpenEngine {
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;

        /**
         * @TODO rename to GeometryBatch?
         *
         * Gather all indice information in a container? Easier to
         * pass around and constructors will be simpler.
         */

        /**
         * Draw primitive class, containing the primitive type that
         * should be used when rendering the mesh with the specified
         * material.
         */
        class DrawPrimitive {
        protected:
            Resources::IndexBufferObjectPtr indexBuffer;
            GeometryPrimitive prim;
            MaterialPtr mat;
            MeshPtr mesh;
            unsigned int indexOffset;
            unsigned int drawRange;
            
        public:
            DrawPrimitive(Resources::IndexBufferObjectPtr indexBuffer,
                          GeometryPrimitive prim,
                          MaterialPtr mat,
                          MeshPtr mesh);

            DrawPrimitive(Resources::IndexBufferObjectPtr indexBuffer,
                          GeometryPrimitive prim,
                          MaterialPtr mat,
                          MeshPtr mesh,
                          unsigned int indexOffset,
                          unsigned int drawRange);
            
            /**
             * Return the index buffer object.
             */
            inline Resources::IndexBufferObjectPtr GetIndexBuffer() const { return indexBuffer; }
            
            /**
             * Returns the material used by this draw primitive.
             */ 
            inline MaterialPtr GetMaterial() const { return mat; }

            /**
             * Returns the mesh used by this draw primitive.
             */
            inline MeshPtr GetMesh() const { return mesh; }

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
             * Iterate over primitives. Like how?
             */
        };

        typedef boost::shared_ptr<DrawPrimitive> DrawPrimitivePtr;

    }
}

#endif
