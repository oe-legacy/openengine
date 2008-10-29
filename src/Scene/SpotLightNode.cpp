// Spot light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/SpotLightNode.h>

namespace OpenEngine {
namespace Scene {

SpotLightNode::SpotLightNode()
  : constAtt(1.0)
  , linearAtt(0.0)
  , quadAtt(0.0)
  , cutoff(180.0)
  , exponent(0.0)
{
    
}

SpotLightNode::~SpotLightNode() {

}

} // NS Scene
} // NS OpenEngine
