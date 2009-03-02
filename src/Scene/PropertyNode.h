// Property node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_PROPERTY_NODE_H_
#define _OE_PROPERTY_NODE_H_

#include <Scene/ISceneNode.h>
#include <map>

namespace OpenEngine {
namespace Scene {

/**
 * Property node.
 * Contains a key/value map of type string/string.
 *
 * @class PropertyNode PropertyNode.h Sceene/PropertyNode.h
 */
class PropertyNode : public ISceneNode {
    OE_SCENE_NODE(PropertyNode, ISceneNode)

public:
    std::map<std::string,std::string> properties;
};

} // NS Scene
} // NS OpenEngine

#endif // _OE_PROPERTY_NODE_H_
