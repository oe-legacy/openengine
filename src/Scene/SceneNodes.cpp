
#include <Scene/SceneNodes.h>
#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
namespace Scene {

// Accept
#define SCENE_NODE(type)                                        \
void type::Accept(ISceneNodeVisitor& v) {                       \
    IncAcceptStack();                                           \
    v.Visit##type(this);                                        \
    DecAcceptStack();                                           \
}
#include "SceneNodes.def"
#undef SCENE_NODE

// Clone
#define SCENE_NODE(type)                                        \
ISceneNode* type::Clone() const {                               \
    type* clone = new type(*this);                              \
    std::list<ISceneNode*>::const_iterator itr;                 \
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)  \
        clone->AddNode((*itr)->Clone());                        \
    return clone;                                               \
}
#include "SceneNodes.def"
#undef SCENE_NODE
        
// Type string
#define SCENE_NODE(type)                                        \
const std::string type::GetNodeName() const {                   \
    return #type;                                               \
}
#include "SceneNodes.def"
#undef SCENE_NODE

} // NS Scene
} // NS OpenEngine
