// Model interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/ModelNode.h>

#include <Resources/IndexBufferObject.h>
#include <Geometry/Material.h>
#include <Geometry/Mesh.h>

using namespace OpenEngine::Geometry;
using namespace OpenEngine::Resources;

namespace OpenEngine {
    namespace Scene {

        ModelNode::ModelNode() {
            
        }

        ModelNode::ModelNode(MeshPtr m) {
            mesh = m;
            mats.clear();
        }

        inline MeshPtr ModelNode::GetMesh() const {
            return mesh;
        }

        inline void ModelNode::AddIndices(Indices i, MaterialPtr m){
#ifdef OE_SAFE
            if (i.GetOffset() + i.GetRange() > mesh->GetIndexBuffer()->GetSize())
                throw Exception("Indices index outside IndexBufferObject.");
#endif
            mats.push_back(pair<Indices, MaterialPtr>(i, m));
        }

    }
}
