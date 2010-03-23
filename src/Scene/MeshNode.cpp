// Mesh node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/MeshNode.h>
#include <Geometry/Mesh.h>

using namespace OpenEngine::Geometry;

namespace OpenEngine {
    namespace Scene {
        
        MeshNode::MeshNode() {
            mesh = MeshPtr();
        }

        MeshNode::MeshNode(const MeshNode& node) 
            : ISceneNode(node) {
            mesh = node.GetMesh();
        }

        MeshNode::MeshNode(MeshPtr mesh) {
            this->mesh = mesh;
        }
        
        MeshPtr MeshNode::GetMesh() const{
            return mesh;
        }

        void MeshNode::SetMesh(MeshPtr mesh){
            this->mesh = mesh;
        }
        
    }
}
