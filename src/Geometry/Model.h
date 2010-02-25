// Model node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MODEL_H_
#define _OE_MODEL_H_

#include <boost/shared_ptr.hpp>
#include <vector>

using std::vector;

namespace OpenEngine {
    namespace Geometry{
        class DrawPrimitive;
        typedef boost::shared_ptr<DrawPrimitive> DrawPrimitivePtr;

        typedef vector<DrawPrimitivePtr> DrawPrimitiveList;

        /**
         * Model class. Contains batches of draw primitives.
         */
        class Model{
        protected:
            DrawPrimitiveList prims;

        public:
            Model();
            Model(DrawPrimitivePtr prim);
            Model(DrawPrimitiveList prims);

            /**
             * Add a new draw primitive to the model.
             */
            void AddDrawPrimitive(DrawPrimitivePtr prim);

            /**
             * Get the i'th draw primitive.
             */
            void GetDrawPrimitive(unsigned int i);

            /**
             * Get a list of all draw primitives.
             */
            DrawPrimitiveList GetDrawPrimitives();

            /**
             * Remove the i'th draw primitive.
             */
            void RemoveDrawPrimitive(unsigned int i);
            
        };

    }
}

#endif
