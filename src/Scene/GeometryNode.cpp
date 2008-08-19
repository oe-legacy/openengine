// Geometry node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/GeometryNode.h>
#include <Scene/TransformationNode.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Scene {

    GeometryNode::GeometryNode() {
        faces = new FaceSet();
    }

    /**
     * Copy constructor.
     * Performs a shallow copy.
     *
     * @param node Geometry node to copy.
     */
    GeometryNode::GeometryNode(GeometryNode& node) : SceneNode(node) {
        faces = node.faces;
    }

    GeometryNode::GeometryNode(FaceSet* faces)
        : faces(faces) {

    }
    
    GeometryNode::~GeometryNode() {
        delete faces;
    }

    ISceneNode* GeometryNode::CloneSelf() {
        GeometryNode* clone = new GeometryNode(*this);
        clone->faces = new FaceSet(*faces);
        return clone;
    }

    FaceSet* GeometryNode::GetFaceSet() {
        return faces;
    }

    void GeometryNode::SetFaceSet(FaceSet* faces){
        delete this->faces;
        this->faces = faces;
    }

    void GeometryNode::Accept(ISceneNodeVisitor& v) {
        v.VisitGeometryNode(this);
    }

} //NS Scene
} //NS OpenEngine
