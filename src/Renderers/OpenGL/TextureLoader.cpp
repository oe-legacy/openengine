// OpenGL texture loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/OpenGL/TextureLoader.h>
#include <Scene/GeometryNode.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Face.h>
#include <Meta/OpenGL.h>
#include <Resources/ITextureResource.h>
#include <Logging/Logger.h>
#include <list>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

using namespace std;
using OpenEngine::Geometry::FaceSet;
using OpenEngine::Geometry::FaceList;
using OpenEngine::Resources::ITextureResourcePtr;

TextureLoader::TextureLoader() {}

TextureLoader::~TextureLoader() {}

/**
 * The Geometry nodes textures are loaded on visit
 * 
 * @param node Geometry node 
 */
void TextureLoader::VisitGeometryNode(GeometryNode* node) {
    FaceSet* faces = node->GetFaceSet();
    if (faces == NULL) return;
    for (FaceList::iterator face = faces->begin(); face != faces->end(); face++) {
        // load face textures
        LoadTextureResource((*face)->texr);
    }
}

/**
 * Load a texture resource.
 *
 * @param tex Texture resource pointer.
 */
void TextureLoader::LoadTextureResource(ITextureResourcePtr& tex) {
    if (tex == NULL) return;
    if(tex->GetID() == 0) {
        tex->Load();

        GLuint texid;
        glGenTextures(1, &texid);
        tex->SetID(texid);
            
        glBindTexture(GL_TEXTURE_2D, texid);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
        GLuint depth = 0;
        switch (tex->GetDepth()) {
        case 8:  depth = GL_LUMINANCE; break;
        case 24: depth = GL_RGB;   break;
        case 32: depth = GL_RGBA;  break;
        default: logger.warning << "Unsupported color depth: " 
                                << tex->GetDepth() << logger.end;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, depth, tex->GetWidth(), tex->GetHeight(), 0,
                     depth, GL_UNSIGNED_BYTE, tex->GetData());
        tex->Unload();
    }
}


} // NS OpenGL
} // NS Renderers
} // NS OpenEngine
