// Model node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MODEL_H_
#define _MODEL_H_

#include <boost/shared_ptr.hpp>
#include <vector>

using std::vector;

namespace OpenEngine {
    namespace Geometry{
        class DrawPrimitive;
        typedef boost::shared_ptr<DrawPrimitive> DrawPrimitivePtr;

        class Model{
        protected:
            vector<DrawPrimitivePtr> prims;

        public:
            Model();
            Model(DrawPrimitivePtr prim);
            Model(vector<DrawPrimitivePtr> prims);
            
        };

    }
}

#endif
