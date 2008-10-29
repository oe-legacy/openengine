// Geometry node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_GEOMETRY_NODE_H_
#define _OE_GEOMETRY_NODE_H_

#include <Scene/ISceneNode.h>
#include <Geometry/FaceSet.h>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

namespace OpenEngine {
namespace Scene {

/**
 * Geometry node.
 * Acts as a simple node wrapping a face set.
 *
 * @class GeometryNode GeometryNode.h Scene/GeometryNode.h
 */
class GeometryNode : public ISceneNode {
    OE_SCENE_NODE(GeometryNode, ISceneNode)

public:
    GeometryNode();
    GeometryNode(const GeometryNode& node);
    explicit GeometryNode(Geometry::FaceSet* faces);
    ~GeometryNode();

    Geometry::FaceSet* GetFaceSet();
    void SetFaceSet(Geometry::FaceSet* faces);

private:
    Geometry::FaceSet* faces;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & faces;
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::GeometryNode)

#endif // _OE_GEOMETRY_NODE_H_
