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
#include <Scene/MeshNode.h>
#include <Scene/VertexArrayNode.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Face.h>
#include <Geometry/Mesh.h>
#include <Geometry/VertexArray.h>
#include <Resources/ITexture2D.h>
#include <Resources/ITexture3D.h>
#include <Resources/IShaderResource.h>
#include <list>
#include <set>
#include <Logging/Logger.h>

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
using Geometry::MaterialPtr;
using Geometry::Mesh;
using Geometry::MeshList;
using Renderers::RenderingEventArg;
using Resources::ITexture2D;
using Resources::ITexture2DPtr;
using Resources::Texture2DChangedEventArg;
using Resources::ITexture3D;
using Resources::ITexture3DPtr;
using Resources::Texture3DChangedEventArg;
using Resources::IShaderResourcePtr;
using Resources::TextureList;
using Scene::ISceneNode;
using Scene::ISceneNodeVisitor;
using Scene::GeometryNode;
using Scene::MeshNode;
using Scene::VertexArrayNode;

typedef boost::shared_ptr<Mesh> MeshPtr;
 
/**
 * Utility class to find textures in a scene.
 * All textures found will be loaded with
 * TextureLoader::Load(ITexture2DPtr, ReloadPolicy)
 * While searching a cache is used so no texture in the scene is
 * loaded two times.
 */
class TextureLoader::SceneLoader
    : public ISceneNodeVisitor {
    TextureLoader& loader;
    TextureLoader::ReloadPolicy policy;
    set<ITexture2D*> cache;
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
            LoadMaterial((*face)->mat);
        }
    }

    void VisitMeshNode(MeshNode* node) {
        MeshPtr m = node->GetMesh();
        // load face textures if not already loaded or in the cache
        LoadMaterial(m->GetMaterial());
    }

    void VisitVertexArrayNode(VertexArrayNode* node) {
        list<VertexArray*> vaList = node->GetVertexArrays();
        list<VertexArray*>::iterator itr;
        for (itr = vaList.begin(); itr!=vaList.end(); itr++) {
            // Load vertex array texture if not already loaded or in the cache
            LoadMaterial((*itr)->mat);
        }
    }

    void LoadMaterial(MaterialPtr mat){
        list<pair <string, ITexture2DPtr> > texs2D = mat->Get2DTextures();
        list<pair <string, ITexture2DPtr> >::iterator itr = texs2D.begin();
        while(itr != texs2D.end()){
            ITexture2DPtr t = itr->second;
            if (t != NULL && t->GetID() == 0 &&
                cache.find(t.get()) == cache.end()) {
                cache.insert(t.get());
                loader.Load(t, policy);
            }
            ++itr;
        }

        IShaderResourcePtr shad = mat->shad;
        if (shad != NULL) {
            // load shader and its textures
            shad->Load();
            TextureList texs = shad->GetTextures();
            for (unsigned int i = 0; i < texs.size(); ++i)
                loader.Load(texs[i]);
        }
    }
};

/**
 * Utility class to watch for texture change events.
 */
class TextureLoader::Reloader
    : public IListener<Texture2DChangedEventArg>,
      public IListener<Texture3DChangedEventArg> {
    IRenderer& renderer;
    QueuedEvent<Texture2DChangedEventArg> queue2d;
    QueuedEvent<Texture3DChangedEventArg> queue3d;
public:
    virtual ~Reloader() { }
    Reloader(IRenderer& renderer)
        : renderer(renderer) {
        queue2d.Attach(*this);
        queue3d.Attach(*this);
    }
    // Reload the events in the queue.
    // @todo: This should preferably only send off one change event
    // per texture. However, care must be taken to make sure the
    // dimension field reflects the accumulated changes of the
    // texture.
    void ReloadQueue() {
        queue2d.Release(); // will dispatch to: this->Handle(...)
        queue3d.Release(); // will dispatch to: this->Handle(...)
    }
    // Rebind a textures that has changed.
    // This call can come through the queue or directly from the
    // texture depending on the reload policy it was loaded with.
    void Handle(Texture2DChangedEventArg arg) {
        renderer.RebindTexture(arg.resource.get(), 
                               arg.xOffset,
                               arg.yOffset,
                               arg.width,
                               arg.height);
    }
    // Rebind a 3D textures that has changed.
    // This call can come through the queue or directly from the
    // texture depending on the reload policy it was loaded with.
    void Handle(Texture3DChangedEventArg arg) {
        renderer.RebindTexture(arg.resource.get(), 
                               arg.xOffset,
                               arg.yOffset,
                               arg.zOffset,
                               arg.width,
                               arg.height,
                               arg.depth);
    }
    // Add a texture depending on the reload policy.
    // In both cases we first remove any reference to this loader
    // so we do not listen multiple times. 
    void Add(ITexture2DPtr texr, ReloadPolicy policy) {
        if (RELOAD_IMMEDIATE == policy) {
            // Reload immediately on texture change.
            texr->ChangedEvent().Detach(*this);
            texr->ChangedEvent().Attach(*this);
        } else if (RELOAD_QUEUED == policy) {
            // Observe a texture for texture change with a queue.
            texr->ChangedEvent().Detach(queue2d);
            texr->ChangedEvent().Attach(queue2d);
        }
    }
    // Add a 3D texture depending on the reload policy.
    // In both cases we first remove any reference to this loader
    // so we do not listen multiple times. 
    void Add(ITexture3DPtr texr, ReloadPolicy policy) {
        if (RELOAD_IMMEDIATE == policy) {
            // Reload immediately on texture change.
            texr->ChangedEvent().Detach(*this);
            texr->ChangedEvent().Attach(*this);
        } else if (RELOAD_QUEUED == policy) {
            // Observe a texture for texture change with a queue.
            texr->ChangedEvent().Detach(queue3d);
            texr->ChangedEvent().Attach(queue3d);
        }
    }
};

/**
 * Utility class to delay texture loading to the renderer init phase
 * where a context should exist.
 */
class TextureLoader::InitLoader
    : public IListener<RenderingEventArg> {
    struct pair2d {
        ITexture2DPtr t; ReloadPolicy p;
        pair2d(ITexture2DPtr t, ReloadPolicy p)
            : t(t), p(p) {}
    };
    struct pair3d {
        ITexture3DPtr t; ReloadPolicy p;
        pair3d(ITexture3DPtr t, ReloadPolicy p)
            : t(t), p(p) {}
    };
    list<pair2d> queue2d;
    list<pair3d> queue3d;
    Reloader& reloader;
public:
    InitLoader(Reloader& reloader) : reloader(reloader) { }
    virtual ~InitLoader() {}
    void Add(ITexture2DPtr t, ReloadPolicy p) {
        queue2d.push_back(pair2d(t,p));
    }
    void Add(ITexture3DPtr t, ReloadPolicy p) {
        queue3d.push_back(pair3d(t,p));
    }
    // This is called on the render initialize event. After processing
    // the queue we may clear it as no more init events can occur.
    void Handle(RenderingEventArg arg) {
        list<pair2d>::iterator itr2d;
        for (itr2d = queue2d.begin(); itr2d != queue2d.end(); itr2d++) {
            // Add for re-loading.
            reloader.Add((*itr2d).t, (*itr2d).p);
            // If an id is set we need not load it again.
            if ((*itr2d).t->GetID() != 0) continue;
            arg.renderer.LoadTexture((*itr2d).t);
        }
        queue2d.clear();

        list<pair3d>::iterator itr3d;
        for (itr3d = queue3d.begin(); itr3d != queue3d.end(); itr3d++) {
            // Add for re-loading.
            reloader.Add((*itr3d).t, (*itr3d).p);
            // If an id is set we need not load it again.
            if ((*itr3d).t->GetID() != 0) continue;
            arg.renderer.LoadTexture((*itr3d).t);
        }
        queue3d.clear();
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
    // If the renderer has not reached the init phases we attach the
    // utility loader so no textures are loaded before a context is
    // ready.
    if (renderer.GetCurrentStage() == IRenderer::RENDERER_UNINITIALIZE)
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
void TextureLoader::Load(ITexture2DPtr texr, ReloadPolicy policy) {
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

/**
 * Load a 3D texture.
 * If no reload policy flag is supplied the default policy will be
 * used (\a RELOAD_NEVER). 
 */
void TextureLoader::Load(ITexture3DPtr texr, ReloadPolicy policy) {
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
