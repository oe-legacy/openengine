// Point light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/LightNode.h>

namespace OpenEngine {
namespace Scene {

LightNode::LightNode(): active(true), 
        ambient(Vector<4,float>(1.0,1.0,1.0,1.0)),
        diffuse(Vector<4,float>(1.0,1.0,1.0,1.0)),
        specular(Vector<4,float>(1.0,1.0,1.0,1.0)) {
    
}

LightNode::~LightNode() {

}

//! Accept of visitors
void LightNode::Accept(ISceneNodeVisitor& v) { 
    //    v.VisitLightNode(this);
    // commented out as we really don't wanna visit lightnode
}


} // NS Scene
} // NS OpenEngine
