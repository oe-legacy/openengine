// Directional light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/DirectionalLightNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Create a directional light node
 *
 * Initial direction is assumed to be [0,-1,0] 
 * Light direction is affected by rotation of transformation nodes.
 */

DirectionalLightNode::DirectionalLightNode()
    : Light()
{

}

DirectionalLightNode::~DirectionalLightNode() {

}

} // NS Scene
} // NS OpenEngine
