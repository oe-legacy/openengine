// Collected geometry transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/CollectedGeometryTransformer.h>
#include <Scene/SearchTool.h>
#include <list>

namespace OpenEngine {
namespace Scene {

    using Geometry::FaceSet;
    using std::list;

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
        // new empty face set
        faces = new FaceSet();
        // find all descendant geometry nodes
        list<GeometryNode*> nodes = SearchTool::DescendantGeometryNodes(&node);
        // for each node add the faces to the new face set
        list<GeometryNode*>::iterator itr;
        for (itr = nodes.begin(); itr != nodes.end(); itr++)
            faces->Add((*itr)->GetFaceSet());
        // delete all nodes of the root node
        node.DeleteAllNodes();
        // create and attach a geometry with the collected faces
        georoot = new GeometryNode(faces);
        node.AddNode(georoot);
    }

    /**
     * Get the geometry node containing all the collected faces.
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
    
} // NS Scene
} // NS OpenEngine
