// Search tool for finding nodes in a scene.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SCENE_SEARCH_TOOL_H_
#define _OE_SCENE_SEARCH_TOOL_H_

#include <Scene/ISceneNode.h>
#include <list>
#include <string>

namespace OpenEngine {
namespace Scene {

// forward declaration of all nodes (include is in cpp file)
#define SCENE_NODE(type)                        \
    class type;
#include "SceneNodes.def"
#undef SCENE_NODE

/**
 * Search tool for finding nodes in a scene.
 * This tool provides a simple API for finding nodes in a scene
 * structure.
 * @code
 * // Find the first transformation node of the first property node
 * // with the key/value pair: id=gun in 'scene'. 
 * SearchTool tool;
 * TransformationNode* gun;
 * gun = tool.DescendantTransformationNode(
 *            tool.DescendantPropertyNodeWith("id","gun",
 *                 scene));
 * if (gun != NULL)
 *   // we found the gun!
 * @endcode
 * Please refer to tests/SearchTool.cpp for further usage.
 *
 * @class SearchTool SearchTool.h Scene/SearchTool.h
 * @see tests/SearchTool.cpp
 *
 * @todo Include documentation about the macro generated selector
 * functions. Currently I can not find a way to force Doxygen to
 * include documentation about functions it can not see exist :(
 */
class SearchTool {
public:
    // constructor / destructor
    SearchTool() {}
    virtual ~SearchTool() {}

    /**
     * @fn SomeNode* ChildSomeNode(ISceneNode* scene)
     * @brief Find first child of type \a SomeNode.
     * Searches the direct children of \a scene (i.e. only the first
     * generation of the tree) for the first occurrence of a node of
     * type \a SomeNode. If no such node is among the children the
     * result is \a NULL.
     * @param scene Scene to search
     * @result Child or NULL
     */


// Macro for defining the set of operation along a single axis
#define AXIS(type,axis)                                             \
    static type* axis##type(ISceneNode*);                           \
    static type* axis##type(std::list<ISceneNode*>);                \
    static std::list<type*> axis##type##s(ISceneNode*);             \
    static std::list<type*> axis##type##s(std::list<ISceneNode*>);

// Macro for defining with-operations along an axis (for key/value filtering)
#define AXIS_WITH(type,axis)                                            \
    static type* axis##type##With(std::string, std::string, ISceneNode*); \
    static type* axis##type##With(std::string, std::string, std::list<ISceneNode*>); \
    static std::list<type*> axis##type##sWith(std::string, std::string, ISceneNode*); \
    static std::list<type*> axis##type##sWith(std::string, std::string, std::list<ISceneNode*>);

// Create an implementation pr. scene node
#define SCENE_NODE(type)   \
    AXIS(type, Descendant) \
    AXIS(type, Ancestor)   \
    AXIS(type, Child)
#include "SceneNodes.def"
#undef SCENE_NODE

    // Create special with-selectors for PropertyNode
    AXIS_WITH(PropertyNode, Descendant)
    AXIS_WITH(PropertyNode, Ancestor)
    AXIS_WITH(PropertyNode, Child)

#undef AXIS
#undef AXIS_WITH

};

} // NS Scene
} // NS OpenEngine

#endif // _OE_SCENE_SEARCH_TOOL_H_
