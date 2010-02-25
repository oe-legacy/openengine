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

namespace OpenEngine {
    namespace Resources {
        
        class IndexBufferObject : public BufferObject<1, unsigned int> {
        public:
            IndexBufferObject()
                : BufferObject<1, unsigned int>() {
            }
        };
        
        /**
         * Index Buffer Object smart pointer.
         */
        typedef boost::shared_ptr<IndexBufferObject> IndexBufferObjectPtr;

    }
}

#endif
