// Collected geometry transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "CollectedGeometryTransformer.h"

namespace OpenEngine {
namespace Scene {

    /**
     * Constructs a collected geometry node transformer that collects
     * all face sets in the scene graph and merges them into one
     * geometry node.
     */
    CollectedGeometryTransformer::CollectedGeometryTransformer()
        : faces(NULL)
        , georoot(NULL) {

    }
    
    /**
     * Destructor
     */
    CollectedGeometryTransformer::~CollectedGeometryTransformer() {
        // the constructed face sets are always bound to a geometry
        // node so we are never responsible for deleting faces. 
    }

    /**
     * Transforms the entire scene into one geometry node and attaches
     * it to the passed root node.
     *
     * @warning The result of supplying a scene with a geometry node
     *          as root is unspecified. 
     *
     * @param node Root node of a scene to build from.
     */
    void CollectedGeometryTransformer::Transform(ISceneNode &node) {
        faces = new FaceSet();
        node.Accept(*this);
        node.DeleteAllNodes();
        georoot = new GeometryNode(faces);
        node.AddNode(georoot);
    }

    /**
     * Get the geometry node that has contains all the collected faces.
     * NULL if no transformation has been applied.
     */
    GeometryNode* CollectedGeometryTransformer::GetCollectedGeometryNode() const {
        return georoot;
    }

    /**
     * Get the face set that has contains all the collected faces.
     * NULL if no transformation has been applied.
     */
    FaceSet* CollectedGeometryTransformer::GetCollectedFaceSet() const {
        return faces;
    }

    /**
     * Build a list of all faces found in the structure.
     *
     * @param node Geometry node.
     */
    void CollectedGeometryTransformer::VisitGeometryNode(GeometryNode *node){
        faces->Add(node->GetFaceSet());
    }
    
} // NS Scene
} // NS OpenEngine
