// OpenGL texture loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/TextureLoader.h>
#include <Scene/GeometryNode.h>
#include <Scene/VertexArrayNode.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Face.h>
#include <Geometry/VertexArray.h>
#include <Resources/ITextureResource.h>
#include <Logging/Logger.h>
#include <list>

namespace OpenEngine {
namespace Renderers {

using std::list;
using OpenEngine::Geometry::FaceSet;
using OpenEngine::Geometry::FaceList;
using OpenEngine::Geometry::VertexArray;
using OpenEngine::Resources::ITextureResourcePtr;

TextureLoader::TextureLoader() : renderer(NULL) {}

TextureLoader::~TextureLoader() {}

void TextureLoader::Handle(RenderingEventArg arg) {
    renderer = &arg.renderer;
    renderer->GetSceneRoot()->Accept(*this);
    renderer = NULL;
}

/**
 * The Geometry nodes textures are loaded on visit
 * 
 * @param node Geometry node 
 */
void TextureLoader::VisitGeometryNode(GeometryNode* node) {
    FaceSet* faces = node->GetFaceSet();
    if (faces == NULL) return;
    for (FaceList::iterator face = faces->begin(); face != faces->end(); face++) {
        // load face textures if not already loaded
        if ((*face)->mat->texr != NULL && (*face)->mat->texr->GetID() == 0)
            renderer->LoadTexture((*face)->mat->texr);
    }
}

/**
 * The textures for each vertex array in the nodes list are loaded on visit.
 * 
 * @param node Vertex Array Node
 */
void TextureLoader::VisitVertexArrayNode(VertexArrayNode* node) {
    list<VertexArray*> vaList = node->GetVertexArrays();
    // Iterate through list of Vertex Arrays
    for (list<VertexArray*>::iterator itr = vaList.begin(); itr!=vaList.end(); itr++) {
        // Load vertex array texture if not already loaded
        if ((*itr)->mat->texr != NULL && (*itr)->mat->texr->GetID() == 0)
            renderer->LoadTexture((*itr)->mat->texr);
    }
}

} // NS Renderers
} // NS OpenEngine
