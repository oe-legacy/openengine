// Spot light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SPOT_LIGHT_NODE_H_
#define _OE_SPOT_LIGHT_NODE_H_

#include <Geometry/Light.h>
#include <Scene/ISceneNode.h>

namespace OpenEngine {
namespace Scene {

using Geometry::Light;

/**
 * Spot Light tree node.
 * 
 * @class SpotLightNode SpotLightNode.h Scene/SpotLightNode.h
 */
class SpotLightNode : public Light, public ISceneNode {
    OE_SCENE_NODE(SpotLightNode, ISceneNode)
public:
    float constAtt, linearAtt, quadAtt, cutoff, exponent;

    SpotLightNode();
    virtual ~SpotLightNode();

private:
};

} // NS Scene
} // NS OpenEngine



#endif // _SPOT_LIGHT_NODE_H_
