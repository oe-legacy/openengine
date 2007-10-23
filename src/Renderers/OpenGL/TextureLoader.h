// Texture loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include <Scene/ISceneNodeVisitor.h>
#include <Resources/ITextureResource.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

using OpenEngine::Scene::GeometryNode;
using OpenEngine::Scene::ISceneNodeVisitor;
using OpenEngine::Resources::ITextureResourcePtr;

/**
 * OpenGL specific texture loader.
 *
 * @class TextureLoader TextureLoader.h Renderers/OpenGL/TextureLoader.h
 */
class TextureLoader : public ISceneNodeVisitor {
public:
    TextureLoader();
    ~TextureLoader();

    static void LoadTextureResource(ITextureResourcePtr& tex);
    void VisitGeometryNode(GeometryNode* node);
};

} // NS OpenGL
} // NS Renderers
} // NS OpenEngine

#endif
