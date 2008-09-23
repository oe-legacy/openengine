// Vertex Array Node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_VERTEX_ARRAY_NODE_H_
#define _OE_VERTEX_ARRAY_NODE_H_

#include <Scene/SceneNode.h>

namespace OpenEngine {

// forward declaration
namespace Geometry { class VertexArray; }

namespace Scene {

using OpenEngine::Geometry::VertexArray;

/**
 * Vertex Array node.
 * Acts as a simple wrapper around a list of vertex arrays.
 *
 * @class VertexArrayNode VertexArrayNode.h Scene/VertexArrayNode.h
 */
class VertexArrayNode : public SceneNode {
public:
    /**
     * Set constructor.
     *
     * @param faces content of this Vertex Array Node.
     */
    VertexArrayNode();

    /**
     * Destructor.
     */
    virtual ~VertexArrayNode();

    /**
     * Get faces this Vertex Array Node contains.
     *
     * @return FaceSet pointer.
     */
    virtual std::list<VertexArray*> GetVertexArrays();

    /**
     * Set FaceSet for this Vertex Array Node.
     *
     * @param faces FaceSet pointer.
     */
    virtual void AddVertexArray(VertexArray& va);

    /**
     * Accept a visitor.
     *
     * @see ISceneNode::Accept
     */
    virtual void Accept(ISceneNodeVisitor& visitor);

protected:
    std::list<VertexArray*> vaList;
};

} // NS Scene
} // NS OpenEngine

#endif // _VERTEX_ARRAY_NODE_H_
