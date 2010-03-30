// Light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_DIRECTIONAL_LIGHT_NODE_H_
#define _OE_DIRECTIONAL_LIGHT_NODE_H_

#include <Geometry/Light.h>
#include <Scene/ISceneNode.h>

namespace OpenEngine {
namespace Scene {

using Geometry::Light;

/**
 * Directional Light tree node.
 * 
 * @class DirectionalLightNode DirectionalLightNode.h Scene/DirectionalLightNode.h
 */
class DirectionalLightNode : public Light, public ISceneNode {
    OE_SCENE_NODE(DirectionalLightNode, ISceneNode)
public:
    DirectionalLightNode();
    virtual ~DirectionalLightNode();

private:
};

} // NS Scene
} // NS OpenEngine


#endif // _DIRECTIONAL_LIGHT_NODE_H_
