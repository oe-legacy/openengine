// Index buffer object.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INDEX_BUFFER_OBJECT_H_
#define _INDEX_BUFFER_OBJECT_H_

#include <Resources/BufferObject.h>

namespace OpenEngine {
    namespace Resources {
        
        enum GeometryPrimitive {
            GL_POINTS,
            LINES,
            LINE_STRIP,
            TRIANGLES,
            TRIANGLE_STRIP,
            QUADS};

        class Indices {
        protected:
            GeometryPrimitive prim;
            unsigned int offset;
            unsigned int range;            
        public:
            Indices(unsigned int range);
            Indices(GeometryPrimitive prim,
                    unsigned int range);
            Indices(GeometryPrimitive prim,
                    unsigned int offset,
                    unsigned int range);

            GeometryPrimitive GetPrimitive() const;
            unsigned int GetOffset() const;
            unsigned int GetRange() const;
        };

        class IndexBufferObject : public BufferObject<1, unsigned int> {
        public:
            IndexBufferObject()
                : BufferObject<1, unsigned int>() {
            }
        };
        
        /**
         * Buffer Object interface smart pointer.
         */
        typedef boost::shared_ptr<IndexBufferObject> IndexBufferObjectPtr;

    }
}

#endif
