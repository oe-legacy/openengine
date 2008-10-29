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

#include <Scene/ISceneNode.h>

// We must include VertexArray for serialization to work proper.
#include <Geometry/VertexArray.h>

namespace OpenEngine {
namespace Scene {

/**
 * Vertex Array node.
 * Acts as a simple wrapper around a list of vertex arrays.
 *
 * @class VertexArrayNode VertexArrayNode.h Scene/VertexArrayNode.h
 */
class VertexArrayNode : public ISceneNode {
    OE_SCENE_NODE(VertexArrayNode, ISceneNode);

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
    virtual std::list<Geometry::VertexArray*> GetVertexArrays();

    /**
     * Set FaceSet for this Vertex Array Node.
     *
     * @param faces FaceSet pointer.
     */
    virtual void AddVertexArray(Geometry::VertexArray& va);

    virtual const std::string ToString() const;

private:
    std::list<Geometry::VertexArray*> vaList;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & vaList;
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::VertexArrayNode)

#endif // _VERTEX_ARRAY_NODE_H_
