// Blending node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/BlendingNode.h>

namespace OpenEngine {
namespace Scene {

BlendingNode::BlendingNode() {    
    source = SRC_ALPHA;
    destination = ONE_MINUS_SRC_ALPHA;
    equation = ADD;
}

//! Accept of visitors
void BlendingNode::Accept(ISceneNodeVisitor& v) { 
    v.VisitBlendingNode(this);
}

BlendingNode::BlendingFactor BlendingNode::GetSource() {
    return source;
}

void BlendingNode::SetSource(BlendingFactor source) {
    this->source = source;
}

BlendingNode::BlendingFactor BlendingNode::GetDestination() {
    return destination;
}

void BlendingNode::SetDestination(BlendingFactor destination) {
    this->destination = destination;
}

BlendingNode::BlendingEquation BlendingNode::GetEquation() {
    return equation;
}

void BlendingNode::SetEquation(BlendingEquation equation) {
    this->equation = equation;
}

} // NS Scene
} // NS OpenEngine
