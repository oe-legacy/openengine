// Point light tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/ModelNode.h>

#include <Geometry/Model.h>

namespace OpenEngine {
namespace Scene {

using namespace Geometry;

ModelNode::ModelNode(Model* model)
    : model(model)
{
    
}

ModelNode::~ModelNode() {

}

} // NS Scene
} // NS OpenEngine
