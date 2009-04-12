// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/StrategyVisitor.h>
#include <Scene/SceneNodes.h>

namespace OpenEngine {
namespace Scene {

StrategyVisitor::StrategyVisitor() {
#define SCENE_NODE(type)                                   \
    strategy_##type = 0;
#include <Scene/SceneNodes.def>
#undef SCENE_NODE
}

StrategyVisitor::~StrategyVisitor() {
#define SCENE_NODE(type)                                   \
    if (strategy_##type) delete strategy_##type;
#include <Scene/SceneNodes.def>
#undef SCENE_NODE
}


#define SCENE_NODE(type)                                                \
StrategyVisitor::Strategy<type>* StrategyVisitor::Get##type##Strategy() { \
    return strategy_##type;                                             \
}                                                                       \
void StrategyVisitor::Set##type##Strategy(Strategy<type>* s) {          \
    strategy_##type = s;                                                \
}                                                                       \
void StrategyVisitor::Visit##type(type* node) {                         \
    if (strategy_##type) strategy_##type->Visit(node);                  \
    else DefaultVisitNode(node);                                        \
}
#include <Scene/SceneNodes.def>
#undef SCENE_NODE

} // NS Scene
} // NS OpenEngine
