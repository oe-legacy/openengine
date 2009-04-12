// A visitor with visiting strategies.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_STRATEGY_VISITOR_H_
#define _OE_STRATEGY_VISITOR_H_

#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
namespace Scene {

/**
 *
 * @class StrategyVisitor StrategyVisitor.h Scene/StrategyVisitor.h
 */
class StrategyVisitor : public ISceneNodeVisitor {
public:

    /**
     * Base class for visitor strategy
     */
    template <class NODE>
    class Strategy {        
    public: 
        virtual ~Strategy() {}
        virtual void Visit(NODE* node) = 0;        
    };

    StrategyVisitor();
    ~StrategyVisitor();

    // get/set for strategies
#define SCENE_NODE(type)                       \
    Strategy<type>* Get##type##Strategy();     \
    void Set##type##Strategy(Strategy<type>*); \
    void Visit##type(type*);
#include <Scene/SceneNodes.def>
#undef SCENE_NODE

private:

    // member variables for each node strategy
#define SCENE_NODE(type)                        \
    Strategy<type>* strategy_##type;
#include <Scene/SceneNodes.def>
#undef SCENE_NODE

};

} // NS Scene
} // NS OpenEngine

#endif // _OE_STRATEGY_VISITOR_H_
