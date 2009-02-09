// Texture loader utility.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/TextureLoader.h>

#include <Core/Exceptions.h>
#include <Core/QueuedEvent.h>
#include <Renderers/IRenderer.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Scene/GeometryNode.h>
#include <Scene/VertexArrayNode.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Face.h>
#include <Geometry/VertexArray.h>
#include <Resources/ITextureResource.h>
#include <list>
#include <set>

namespace OpenEngine {
namespace Renderers {

using std::list;
using std::set;

using Core::Exception;
using Core::IListener;
using Core::QueuedEvent;
using Geometry::FaceList;
using Geometry::FaceSet;
using Geometry::VertexArray;
using Renderers::RenderingEventArg;
using Resources::ITextureResource;
using Resources::ITextureResourcePtr;
using Resources::TextureChangedEventArg;
using Scene::ISceneNode;
using Scene::ISceneNodeVisitor;
using Scene::GeometryNode;
using Scene::VertexArrayNode;

/**
 * Utility class to find textures in a scene.
 * All textures found will be loaded with
 * TextureLoader::Load(ITextureResourcePtr, ReloadPolicy)
 * While searching a cache is used so no texture in the scene is
 * loaded two times.
 */
class TextureLoader::SceneLoader
    : public ISceneNodeVisitor {
    TextureLoader& loader;
    TextureLoader::ReloadPolicy policy;
    set<ITextureResource*> cache;
public:
    SceneLoader(TextureLoader& loader, TextureLoader::ReloadPolicy policy)
        : loader(loader), policy(policy) {}
    virtual ~SceneLoader() { }
    void VisitGeometryNode(GeometryNode* node) {
        FaceSet* faces = node->GetFaceSet();
        if (faces == NULL) return;
        FaceList::iterator face;
        for (face = faces->begin(); face != faces->end(); face++) {
            // load face textures if not already loaded or in the cache
            ITextureResourcePtr t = (*face)->mat->texr;
            if (t != NULL && t->GetID() == 0 &&
                cache.find(t.get()) == cache.end()) {
                cache.insert(t.get());
                loader.Load(t, policy);
            }
        }
    }
    void VisitVertexArrayNode(VertexArrayNode* node) {
        list<VertexArray*> vaList = node->GetVertexArrays();
        list<VertexArray*>::iterator itr;
        for (itr = vaList.begin(); itr!=vaList.end(); itr++) {
            // Load vertex array texture if not already loaded or in the cache
            ITextureResourcePtr t = (*itr)->mat->texr;
            if (t != NULL && t->GetID() == 0 &&
                cache.find(t.get()) == cache.end()) {
                cache.insert(t.get());
                loader.Load(t, policy);
            }
        }
    }
};

/**
 * Utility class to watch for texture change events.
 */
class TextureLoader::Reloader
    : public IListener<TextureChangedEventArg> {
    IRenderer& renderer;
    QueuedEvent<TextureChangedEventArg> queue;
public:
    virtual ~Reloader() { }
    Reloader(IRenderer& renderer)
        : renderer(renderer) {
        queue.Attach(*this);
    }
    // Reload the events in the queue.
    // @todo: This should preferably only send off one change event
    // per texture. However, care must be taken to make sure the
    // dimension field reflects the accumulated changes of the
    // texture.
    void ReloadQueue() {
        queue.Release(); // will dispatch to: this->Handle(...)
    }
    // Rebind a textures that has changed.
    // This call can come through the queue or directly from the
    // texture depending on the reload policy it was loaded with.
    void Handle(TextureChangedEventArg arg) {
        renderer.LoadTexture(arg.resource);
    }
    // Add a texture depending on the reload policy.
    // In both cases we first remove any reference to this loader
    // so we do not listen multiple times. 
    void Add(ITextureResourcePtr texr, ReloadPolicy policy) {
        if (RELOAD_IMMEDIATE == policy) {
            // Reload immediately on texture change.
            texr->ChangedEvent().Detach(*this);
            texr->ChangedEvent().Attach(*this);
        } else if (RELOAD_QUEUED == policy) {
            // Observe a texture for texture change with a queue.
            texr->ChangedEvent().Detach(queue);
            texr->ChangedEvent().Attach(queue);
        }
    }
};

/**
 * Utility class to delay texture loading to the renderer init phase
 * where a context should exist.
 */
class TextureLoader::InitLoader
    : public IListener<RenderingEventArg> {
    struct pair {
        ITextureResourcePtr t; ReloadPolicy p;
        pair(ITextureResourcePtr t, ReloadPolicy p)
            : t(t), p(p) {}
    };
    list<pair> queue;
    Reloader& reloader;
public:
    InitLoader(Reloader& reloader) : reloader(reloader) { }
    virtual ~InitLoader() {}
    void Add(ITextureResourcePtr t, ReloadPolicy p) {
        queue.push_back(pair(t,p));
    }
    // This is called on the render initialize event. After processing
    // the queue we may clear it as no more init events can occur.
    void Handle(RenderingEventArg arg) {
        list<pair>::iterator itr;
        for (itr = queue.begin(); itr != queue.end(); itr++) {
            // Add for re-loading.
            reloader.Add((*itr).t, (*itr).p);
            // If an id is set we need not load it again.
            if ((*itr).t->GetID() != 0) continue;
            arg.renderer.LoadTexture((*itr).t);
        }
        queue.clear();
    }
};

/**
 * Create a texture loader.
 * The default reload policy is \a RELOAD_NEVER.
 */
TextureLoader::TextureLoader(IRenderer& renderer, ReloadPolicy policy)
    : renderer(renderer)
    , reloader(new Reloader(renderer))
    , initloader(new InitLoader(*reloader))
    , defaultpolicy(policy)
{
    // If the renderer has not passed the init phases we attach the
    // utility loader so no textures are loaded before a context is
    // ready.
    if (renderer.GetCurrentStage() == IRenderer::RENDERER_INITIALIZE)
        renderer.InitializeEvent().Attach(*initloader);
    // Check that the default policy is not RELOAD_DEFAULT
    if (defaultpolicy == RELOAD_DEFAULT)
        throw Exception("Invalid default reload policy.");
}

TextureLoader::~TextureLoader() {
    renderer.InitializeEvent().Detach(*initloader);
    delete initloader;
    delete reloader;
}

/**
 * Set the default reload policy.
 * This will initially be \a RELOAD_NEVER.
 * For a description of the policies see: ReloadPolicy
 * @see ReloadPolicy
 */
void TextureLoader::SetDefaultReloadPolicy(ReloadPolicy policy) {
    // The default policy must never be RELOAD_DEFAULT
    if (policy == RELOAD_DEFAULT)
        throw Exception("Invalid default reload policy.");
    defaultpolicy = policy;
}

/**
 * Run ReloadQueue() on a rendering event.
 * It is useful to attach to the rendering pre-process event, so all
 * changed textures are loaded proper before rendering.
 *
 * @see ReloadQueue
 * @see IRenderer::PreProcessEvent
 */
void TextureLoader::Handle(RenderingEventArg arg) {
    ReloadQueue();
}

/**
 * Reload all the queued textures changes.
 * This will reload all textures originally loaded with a
 * \a RELOAD_QUEUED flag that have signaled a texture change event.
 */
void TextureLoader::ReloadQueue() {
    reloader->ReloadQueue();
}

/**
 * Load all texture resources in a scene.
 * This will account for all textures found is the material structure
 * of faces that are found under a \a GeometryNode or \a
 * VertexArrayNode. 
 * If no reload policy flag is supplied the default policy will be
 * used (\a RELOAD_NEVER). 
 */
void TextureLoader::Load(ISceneNode& node, ReloadPolicy policy) {
    SceneLoader loader(*this, policy);
    node.Accept(loader);
}

/**
 * Load a texture.
 * If no reload policy flag is supplied the default policy will be
 * used (\a RELOAD_NEVER). 
 */
void TextureLoader::Load(ITextureResourcePtr texr, ReloadPolicy policy) {
    // Here we must remember to calculate the exact policy as it could
    // change before the actual loading is performed.
    policy = my(policy);
    if (IRenderer::RENDERER_UNINITIALIZE == renderer.GetCurrentStage()) {
        // Queue for later loading as no context exists for the renderer.
        initloader->Add(texr, policy);
    } else {
        // If the texture has not already been loaded load it.
        if (texr->GetID() == 0)
            renderer.LoadTexture(texr);
        // Listen for reload events (based on policy)
        reloader->Add(texr, policy);
    }
}

} // NS Renderers
} // NS OpenEngine
