// Geometry node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_NODE_H_
#define _GEOMETRY_NODE_H_

#include <Scene/SceneNode.h>
#include <Geometry/FaceSet.h>
#include <Math/Vector.h>
#include <Math/Quaternion.h>
#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Geometry::FaceSet;
using OpenEngine::Math::Vector;
using OpenEngine::Math::Quaternion;


/**
 * Geometry node.
 * Acts as a simple node wrapping a face set.
 *
 * @class GeometryNode GeometryNode.h Scene/GeometryNode.h
 */
class GeometryNode : public SceneNode {
private:
    FaceSet* faces;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // serialize base class information
        ar & boost::serialization::base_object<SceneNode>(*this);
        ar & faces;
    }

protected:
    ISceneNode* CloneSelf();

public:
    /**
     * Default constructor.
     */
    GeometryNode();

    GeometryNode(GeometryNode& node);

    /**
     * Set constructor.
     * The face set will be deleted if replaced by SetFaceSet or upon
     * destruction of the geometry node.
     *
     * @param faces Content of this Geometry Node.
     */
    explicit GeometryNode(FaceSet* faces);

    /**
     * Destructor.
     */
    ~GeometryNode();

    /**
     * Get faces this Geometry Node contains.
     *
     * @return FaceSet pointer.
     */
    FaceSet* GetFaceSet();

    /**
     * Set FaceSet for this geometry node.
     * This will delete the current face set and bind the new one to
     * the node.
     *
     * @param faces FaceSet pointer.
     */
    void SetFaceSet(FaceSet* faces);

    /**
     * Accept a visitor.
     *
     * @see ISceneNode::Accept
     */
    void Accept(ISceneNodeVisitor& visitor);

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::GeometryNode)


#endif // _GEOMETRY_NODE_H_
