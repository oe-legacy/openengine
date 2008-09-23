// OpenGL texture loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/TextureLoader.h>

#include <Core/QueuedEvent.h>
#include <Renderers/IRenderer.h>
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

using Core::IListener;
using Core::QueuedEvent;
using Geometry::FaceList;
using Geometry::FaceSet;
using Geometry::VertexArray;
using Renderers::RenderingEventArg;
using Resources::ITextureResourcePtr;
using Resources::TextureChangedEventArg;
using Scene::ISceneNode;
using Scene::ISceneNodeVisitor;
using Scene::GeometryNode;
using Scene::VertexArrayNode;


class TextureLoader::InitLoader
    : public IListener<RenderingEventArg> {
    list<ITextureResourcePtr> queue;
public:
    virtual ~InitLoader() { }
    void Add(ITextureResourcePtr texr) {
        queue.push_back(texr);
    }
    void Handle(RenderingEventArg arg) {
        list<ITextureResourcePtr>::iterator itr;
        for (itr = queue.begin(); itr != queue.end(); itr++)
            arg.renderer.LoadTexture(*itr);
    }
};

class TextureLoader::SceneLoader
    : public ISceneNodeVisitor {
    TextureLoader& loader;
    TextureLoader::ReloadPolicy policy;
public:
    virtual ~SceneLoader() { }
    SceneLoader(TextureLoader& loader, TextureLoader::ReloadPolicy policy)
        : loader(loader), policy(policy) {}
    void VisitGeometryNode(GeometryNode* node) {
        FaceSet* faces = node->GetFaceSet();
        if (faces == NULL) return;
        FaceList::iterator face;
        for (face = faces->begin(); face != faces->end(); face++) {
            // load face textures if not already loaded
            if ((*face)->mat->texr != NULL && (*face)->mat->texr->GetID() == 0)
                loader.Load((*face)->mat->texr, policy);
        }
    }
    void VisitVertexArrayNode(VertexArrayNode* node) {
        list<VertexArray*> vaList = node->GetVertexArrays();
        // Iterate through list of Vertex Arrays
        list<VertexArray*>::iterator itr;
        for (itr = vaList.begin(); itr!=vaList.end(); itr++) {
            // Load vertex array texture if not already loaded
            if ((*itr)->mat->texr != NULL && (*itr)->mat->texr->GetID() == 0)
                loader.Load((*itr)->mat->texr, policy);
        }
    }
};

class TextureLoader::Reloader
    : public IListener<RenderingEventArg>
    , public IListener<TextureChangedEventArg> {
    IRenderer& renderer;
    QueuedEvent<TextureChangedEventArg> queue;
public:
    virtual ~Reloader() { }
    Reloader(IRenderer& renderer)
        : renderer(renderer) {
        queue.Attach(*this);
    }
    // run on render pre-process
    void Handle(RenderingEventArg arg) {
        queue.Release(); // this->Handle
    }
    // rebind all textures that have changed
    void Handle(TextureChangedEventArg arg) {
        renderer.LoadTexture(arg.resource);
    }
    // observe a texture for incomming events and queue them
    void ListenOn(IEvent<TextureChangedEventArg>& event) {
        event.Detach(queue);
        event.Attach(queue);
    }
};


TextureLoader::TextureLoader(IRenderer& renderer)
    : renderer(renderer)
    , reloader(new Reloader(renderer))
    , initloader(new InitLoader())
    , defaultpolicy(RELOAD_NEVER)
{
    if (renderer.GetCurrentStage() == IRenderer::RENDERER_INITIALIZE)
        renderer.InitializeEvent().Attach(*initloader);
}

TextureLoader::~TextureLoader() {
    //renderer.InitializeEvent().Detach(*initloader);
    //delete initloader;
    //delete reloader;
}

void TextureLoader::Load(ISceneNode& node, ReloadPolicy policy) {
    SceneLoader loader(*this, policy);
    node.Accept(loader);
}

void TextureLoader::Load(ITextureResourcePtr texr, ReloadPolicy policy) {
    if (my(policy) == RELOAD_ALWAYS) {
        reloader->ListenOn(texr->ChangedEvent());
        //texr->ChangedEvent().Detach(queue); // remove any reference to this loader
        //texr->ChangedEvent().Attach(queue); // so we do not listen multiple times.
    }
    if (texr->GetID() != 0) return;
    if (renderer.GetCurrentStage() == IRenderer::RENDERER_INITIALIZE)
        initloader->Add(texr);
    else
        renderer.LoadTexture(texr);
}

} // NS Renderers
} // NS OpenEngine
