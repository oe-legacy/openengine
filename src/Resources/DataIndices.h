// Data indices.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DATA_INDICES_H_
#define _DATA_INDICES_H_

#include <Resources/DataBlock.h>

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

        class DataIndices : public DataBlock<1, unsigned int> {
        public:
            DataIndices()
                : DataBlock<1, unsigned int>() {
                this->bufferType = INDEX_ARRAY;
            }

            DataIndices(unsigned int* d, unsigned int s)
                : DataBlock<1, unsigned int>(d, s) {
                this->bufferType = INDEX_ARRAY;
            }
        };
        
        /**
         * Data indices smart pointer.
         */
        typedef boost::shared_ptr<DataIndices> DataIndicesPtr;

    }
}

#endif
