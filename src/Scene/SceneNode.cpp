// A scene node stub.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/SceneNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Default constructor.
 */
SceneNode::SceneNode()
    : ISceneNode() {
    
}

/**
 * Copy constructor.
 * Required to perform a shallow copy of the node.
 * In this case we need not do anything.
 *
 * @param node Node to copy.
 */
SceneNode::SceneNode(const SceneNode& node) : ISceneNode(node) {
    // the copy constructor does not copy the sub nodes.
}

/**
 * Destructor.
 * In this case we need not do anything.
 */
SceneNode::~SceneNode() {

}



void SceneNode::Serialize(Resources::IArchiveWriter& w) {

}

void SceneNode::Deserialize(Resources::IArchiveReader& r) {

}

} // NS Scene
} // NS OpenEngine
