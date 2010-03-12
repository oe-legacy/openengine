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
#include <Resources/DataIndices.h>

using OpenEngine::Resources::GeometryPrimitive;

namespace OpenEngine {
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class GeometrySet;
        typedef boost::shared_ptr<GeometrySet> GeometrySetPtr;

        /**
         * @TODO rename to GeometryBatch?
         *
         * Gather all indice information in a container? Easier to
         * pass around and constructors will be simpler.
         * 
         * Will also make it easy to make DrawElements to the renderer
         * in case you just want to draw some indice information you
         * have. (see heightmap that doesn't fit into the Model
         * abstraction and perhaps other multi model/lod nodes)
         */

        /**
         * Draw primitive class, containing the primitive type that
         * should be used when rendering the mesh with the specified
         * material.
         */
        class DrawPrimitive {
        protected:
            Resources::DataIndicesPtr indexBuffer;
            GeometryPrimitive prim;
            MaterialPtr mat;
            GeometrySetPtr mesh;
            unsigned int indexOffset;
            unsigned int drawRange;
            
        public:
            DrawPrimitive(Resources::DataIndicesPtr indexBuffer,
                          GeometryPrimitive prim,
                          MaterialPtr mat,
                          GeometrySetPtr mesh);

            DrawPrimitive(Resources::DataIndicesPtr indexBuffer,
                          GeometryPrimitive prim,
                          MaterialPtr mat,
                          GeometrySetPtr mesh,
                          unsigned int indexOffset,
                          unsigned int drawRange);
            
            /**
             * Return the index buffer object.
             */
            inline Resources::DataIndicesPtr GetIndexBuffer() const { return indexBuffer; }
            
            /**
             * Returns the material used by this draw primitive.
             */ 
            inline MaterialPtr GetMaterial() const { return mat; }

            /**
             * Returns the mesh used by this draw primitive.
             */
            inline GeometrySetPtr GetGeometrySet() const { return mesh; }

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
