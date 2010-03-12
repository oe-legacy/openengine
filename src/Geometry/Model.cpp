// Model interface.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Model.h>

#include <Geometry/Mesh.h>

namespace OpenEngine {
    namespace Geometry {

        Model::Model() {

        }

        Model::Model(MeshPtr prim){
            prims.push_back(prim);
        }
        
        Model::Model(MeshList prims){
            this->prims = prims;
        }
        void Model::AddMesh(MeshPtr prim) {
            prims.push_back(prim);
        }
        
    }
}
