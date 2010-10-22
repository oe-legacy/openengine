// Vertex Array node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/VertexArrayNode.h>
#include <Geometry/VertexArray.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Scene {

using Geometry::VertexArray;

VertexArrayNode::VertexArrayNode()  {

}
    
VertexArrayNode::~VertexArrayNode() {
    std::list<VertexArray*>::iterator itr;
    for (itr=vaList.begin(); itr!=vaList.end(); itr++)
        delete *itr;
    vaList.clear();
}

std::list<VertexArray*> VertexArrayNode::GetVertexArrays() {
    return vaList;
}

void VertexArrayNode::AddVertexArray(VertexArray& vertexArray) {
    vaList.push_back(&vertexArray);
}

const std::string VertexArrayNode::ToString() const {
    return GetNodeName()
        + "\nArrays: "
        + Utils::Convert::ToString(vaList.size());
}
    
} //NS Scene
} //NS OpenEngine
