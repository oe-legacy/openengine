// Model interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Model.h>

#include <Geometry/DrawPrimitive.h>

namespace OpenEngine {
    namespace Geometry {

        Model::Model() {

        }

        Model::Model(DrawPrimitivePtr prim){
            prims.push_back(prim);
        }
        
        Model::Model(DrawPrimitiveList prims){
            this->prims = prims;
        }

    }
}
