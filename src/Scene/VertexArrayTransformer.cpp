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
#include <list>

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

        std::list<FaceSet*> flist;

        // Run through all faces and group them by materials
        for (FaceList::iterator itr = faces->begin(); 
	     itr != faces->end(); itr++) {
	  
	  FaceSet* fs = NULL;
	  FacePtr f = *itr;

	  std::list<FaceSet*>::iterator ilist = flist.begin();
	  for (;ilist != flist.end(); ilist++) {
              // Get the face and material
	      FaceSet* fset = *ilist;
	      MaterialPtr mat = (*fset->begin())->mat;

              // Check if a faceset for faces
	      // with this material already exists
	      if (f->mat->Equals(mat))
		  fs = fset;
	  }

	  if (fs == NULL) {
	      fs = new FaceSet();
	      flist.push_back(fs);
	  }
	  
	  fs->Add(f);
        }

        // Now that all faces has been sorted into face sets with same
        // material we create a vertex array for each face set and add it
        // to the vertex array node.
	std::list<FaceSet*>::iterator ilist = flist.begin();
        for (ilist = flist.begin(); ilist != flist.end(); ilist++) {
	    FaceSet* fs = *ilist;
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
