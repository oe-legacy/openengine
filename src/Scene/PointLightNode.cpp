// Point light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/PointLightNode.h>

namespace OpenEngine {
namespace Scene {

PointLightNode::PointLightNode()
  : constAtt(1.0)
  , linearAtt(0.0)
  , quadAtt(0.0)
{
    
}

PointLightNode::~PointLightNode() {

}

} // NS Scene
} // NS OpenEngine
