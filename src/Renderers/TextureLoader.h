// Texture loader utility.
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
#include <boost/shared_ptr.hpp>

// forward declarations
namespace OpenEngine {
    namespace Scene { class ISceneNode; }
    namespace Renderers { class IRenderer; class RenderingEventArg; }
    namespace Resources{
        class ITexture2D;
        class ITexture3D;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;
        typedef boost::shared_ptr<ITexture3D> ITexture3DPtr;
    }
}

namespace OpenEngine {
namespace Renderers {

/**
 * Texture loader.
 * Loads texture data for a renderer.
 *
 * @code
 * // Example loading textures from an entire scene and reloading any
 * // changes before the rendering phase.
 * TextureLoader texload
 *     = new TextureLoader(*renderer, TextureLoader::RELOAD_QUEUED);
 * renderer->PreProcessEvent().Attach(*texload);
 * texload->Load(scene);
 * @endcode
 * 
 * @class TextureLoader TextureLoader.h Renderers/TextureLoader.h
 */
class TextureLoader : public Core::IListener<RenderingEventArg> {
public:

    /**
     * Reload policies.
     * RELOAD_NEVER means that textures will only be loaded if the
     * have not already been loaded (their id is not zero) and all
     * change events will be ignored.
     * RELOAD_IMMEDIATE means that the texture will be reloaded as
     * soon as a changed event occurs.
     * RELOAD_QUEUED means that the texture will be reloaded on the
     * first call to ReloadQueue or event to Handle(RenderingEventArg)
     * after a change event has occurred.
     * RELOAD_DEFAULT is not a policy, but can be used to flag
     * that the load should use whatever the default policy is.
     */
    enum ReloadPolicy {
        RELOAD_NEVER,
        RELOAD_QUEUED,
        RELOAD_IMMEDIATE,
        RELOAD_DEFAULT
    };

    TextureLoader(Renderers::IRenderer& renderer,
                  ReloadPolicy policy = RELOAD_NEVER);
    virtual ~TextureLoader();

    void Handle(RenderingEventArg arg);
    void ReloadQueue();
    void Load(Scene::ISceneNode& node,
              ReloadPolicy policy = RELOAD_DEFAULT);
    void Load(Resources::ITexture2DPtr texr,
              ReloadPolicy policy = RELOAD_DEFAULT);
    void Load(Resources::ITexture3DPtr texr,
              ReloadPolicy policy = RELOAD_DEFAULT);
    void SetDefaultReloadPolicy(ReloadPolicy policy);

private:
    class InitLoader;
    class Reloader;
    class SceneLoader;
    IRenderer& renderer;
    Reloader* reloader;
    InitLoader* initloader;
    ReloadPolicy defaultpolicy;
    ReloadPolicy my(ReloadPolicy p) {
        return (p == RELOAD_DEFAULT) ? defaultpolicy : p;
    }
};

} // NS Renderers
} // NS OpenEngine

#endif // _OE_TEXTURE_LOADER_H_
