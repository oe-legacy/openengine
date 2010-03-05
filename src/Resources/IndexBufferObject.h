// Index buffer object.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INDEX_BUFFER_OBJECT_H_
#define _INDEX_BUFFER_OBJECT_H_

#include <Resources/BufferObject.h>
#include <list>

using std::list;

namespace OpenEngine {
    namespace Resources {

        /**
         * Geometry primitives (just happens to have the same values
         * as OpenGL...)
         */
        enum GeometryPrimitive {
            POINTS         = 0x0000,
            LINES          = 0x0001,
            LINE_STRIP     = 0x0003,
            TRIANGLES      = 0x0004,
            TRIANGLE_STRIP = 0x0005,
            QUADS          = 0x0007};

        /**
         * RenderBatch contains information about the batch to be
         * rendered.
         *
         * @TODO Change name to GeometryBatch? IndiceBatch?
         */
        class IndexBatch {
        private:
            GeometryPrimitive prim;
            unsigned int indexOffset;
            unsigned int drawRange;
        public:
            IndexBatch(GeometryPrimitive prim,
                    unsigned int offset,
                    unsigned int range)
                : prim(prim), indexOffset(offset), drawRange(range) {
            }
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
        };

        typedef list<Resources::IndexBatch> IndexBatchList;
        
        class IndexBufferObject : public BufferObject<1, unsigned int> {
        public:
            IndexBufferObject()
                : BufferObject<1, unsigned int>() {
                this->bufferType = INDEX_ARRAY;
            }

            IndexBufferObject(unsigned int s)
                : BufferObject<1, unsigned int>(s) {
                this->bufferType = INDEX_ARRAY;
            }

            IndexBufferObject(unsigned int* d, unsigned int s)
                : BufferObject<1, unsigned int>(d, s) {
                this->bufferType = INDEX_ARRAY;
            }
        };
        
        /**
         * Index Buffer Object smart pointer.
         */
        typedef boost::shared_ptr<IndexBufferObject> IndexBufferObjectPtr;

    }
}

#endif
