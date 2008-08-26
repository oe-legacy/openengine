// Texture loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_TEXTURE_LOADER_H_
#define _OE_TEXTURE_LOADER_H_

#include <Core/IListener.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Renderers/IRenderer.h>
#include <Resources/ITextureResource.h>

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Core::IListener;
using OpenEngine::Scene::GeometryNode;
using OpenEngine::Scene::VertexArrayNode;
using OpenEngine::Scene::ISceneNodeVisitor;
using OpenEngine::Resources::ITextureResourcePtr;

/**
 * Texture loader.
 *
 * @class TextureLoader TextureLoader.h Renderers/OpenGL/TextureLoader.h
 */
class TextureLoader : public ISceneNodeVisitor, public IListener<RenderingEventArg> {
private:
    IRenderer* renderer;
public:
    TextureLoader();
    ~TextureLoader();

    virtual void VisitGeometryNode(GeometryNode* node);
    virtual void VisitVertexArrayNode(VertexArrayNode* node);
    virtual void Handle(RenderingEventArg arg);
};

} // NS Renderers
} // NS OpenEngine

#endif // _OE_TEXTURE_LOADER_H_
