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
#include <Resources/IndexBufferObject.h>

namespace OpenEngine {
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;

        /**
         * Draw primitive class, containing the primitive type that
         * should be used when rendering the mesh with the specified
         * material.
         */
        class DrawPrimitive {
        protected:
            Resources::IndexBufferObjectPtr indexBuffer;
            Resources::RenderBatchList batches;
            MaterialPtr mat;
            MeshPtr mesh;
            
        public:
            DrawPrimitive(Resources::IndexBufferObjectPtr indexBuffer,
                          MaterialPtr mat,
                          MeshPtr mesh);
            
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
             * Returns a list of all indice containers.
             *
             * @return IndiceList The list.
             */
            inline Resources::RenderBatchList GetRenderBatches() const { return batches; }

            /**
             * Adds a primitive to draw the entire index buffer object
             * with. Is usually TRIANGLES, which draws the entire mesh
             * with triangles.
             *
             * @param prim The primitive.
             */
            void AddRenderBatch(Resources::GeometryPrimitive prim);

            /**
             * Adds a render batch to be drawn.
             *
             * @param prim The primitive.
             * @param offset The offset into the index buffer.
             * @param range The number of elements to draw.
             */
            void AddRenderBatch(Resources::GeometryPrimitive prim, 
                                unsigned int offset, unsigned int range);

            /**
             * Removes the render batch specified by the iterator.
             */
            void RemoveRenderBatch(Resources::RenderBatchList::iterator batch);
        };

        typedef boost::shared_ptr<DrawPrimitive> DrawPrimitivePtr;

    }
}

#endif
