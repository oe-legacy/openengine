// Shader loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/OpenGL/ShaderLoader.h>
#include <Scene/GeometryNode.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Face.h>
#include <Meta/OpenGL.h>
#include <Renderers/OpenGL/Renderer.h>
#include <Resources/IShaderResource.h>
#include <list>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

using namespace std;
using OpenEngine::Geometry::FaceSet;
using OpenEngine::Geometry::FaceList;
using OpenEngine::Resources::IShaderResourcePtr;
using OpenEngine::Resources::ShaderTextureMap;

ShaderLoader::ShaderLoader() {
    textureLoader = new TextureLoader();
}

ShaderLoader::~ShaderLoader() {
    delete textureLoader;
}

/**
 * The Geometry nodes shaders are loaded on visit
 * 
 * @param node Geometry node 
 */
void ShaderLoader::VisitGeometryNode(GeometryNode* node) {
    FaceList::iterator face;
    ShaderTextureMap::iterator itr;
    FaceSet* faces = node->GetFaceSet();
    if (faces == NULL) return;
    for (face = faces->begin(); face != faces->end(); face++) {
        IShaderResourcePtr shad = (*face)->shad;
        if (shad != NULL) {
            // load shader and its textures
            shad->Load();
            for (itr = shad->textures.begin(); itr != shad->textures.end(); itr++)
                textureLoader->LoadTextureResource( (*itr).second );
        }
    }
}

} // NS OpenGL
} // NS Renderers
} // NS OpenEngine
