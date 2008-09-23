// Vertex Array node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/VertexArrayNode.h>

namespace OpenEngine {
namespace Scene {

VertexArrayNode::VertexArrayNode()  {
}
    
VertexArrayNode::~VertexArrayNode() {
    vaList.clear();
}

std::list<VertexArray*> VertexArrayNode::GetVertexArrays(){
    return vaList;
}

void VertexArrayNode::AddVertexArray(VertexArray& vertexArray){
    vaList.push_back(&vertexArray);
}

void VertexArrayNode::Accept(ISceneNodeVisitor& v) {
    v.VisitVertexArrayNode(this);
}
    
} //NS Scene
} //NS OpenEngine
