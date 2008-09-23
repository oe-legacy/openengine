// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/VertexArrayTransformer.h>
#include <Scene/VertexArrayNode.h>
#include <Scene/GeometryNode.h>
#include <Geometry/VertexArray.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Material.h>
#include <map>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Geometry::FaceList;
using OpenEngine::Geometry::FacePtr;
using OpenEngine::Geometry::MaterialPtr;
using OpenEngine::Geometry::VertexArray;

VertexArrayTransformer::VertexArrayTransformer() {
}

VertexArrayTransformer::~VertexArrayTransformer() {
}

void VertexArrayTransformer::Transform(ISceneNode& node) {
    node.Accept(*this);
}

void VertexArrayTransformer::VisitGeometryNode(GeometryNode* node) {    

    // Create VertexArrayNode
    VertexArrayNode* vaNode = new VertexArrayNode();

    // Move sub nodes to the new VA node
    std::list<ISceneNode*> sn = node->subNodes;
    node->RemoveAllNodes();
    std::list<ISceneNode*>::iterator itr;
    for (itr = sn.begin(); itr != sn.end(); itr++)
        vaNode->AddNode(*itr);

    // We only process the geometry if it contains a face set
    FaceSet* faces = node->GetFaceSet();
    if (faces != NULL) {

        FaceSet*    fs;
        FacePtr     f;
        MaterialPtr m;
        std::map<MaterialPtr, FaceSet*>   fmap;
        std::map<MaterialPtr, FaceSet*>::iterator imap;

        // Run through all faces and group them by materials
        for (FaceList::iterator itr = faces->begin(); itr != faces->end(); itr++) {
            // Get the face and material
            f = *itr;
            m = f->mat;

            // Check if a faceset for faces with this texture resource already exists
            imap = fmap.find(m);
            if (imap == fmap.end()) {
                // No face set was in the map so we create it.
                fs = new FaceSet();
                fmap[m] = fs; 
            } else {
                // A face set with the material exists so we use that
                fs = imap->second;
            }
            // Add the face to the correct faceset
            fs->Add(f);
        }

        // Now that all faces has been sorted into face sets with same
        // material we create a vertex array for each face set and add it
        // to the vertex array node.
        for (imap = fmap.begin(); imap != fmap.end(); imap++) {
            fs = imap->second;
            VertexArray* va = new VertexArray(*fs);
            vaNode->AddVertexArray(*va);
            delete fs;
        }
    }

    // Replace existing node with newly created Vertex Array Node
    node->GetParent()->ReplaceNode(node,vaNode);

    // Continue the transformation on all the VA-nodes children
    vaNode->Accept(*this);

}

} // NS Scene
} // NS OpenEngine
