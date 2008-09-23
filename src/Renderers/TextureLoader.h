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
#include <Resources/ITextureResource.h>

// forward declarations
namespace OpenEngine {
namespace Scene { class ISceneNode; }
namespace Renderers { class IRenderer; }
}

namespace OpenEngine {
namespace Renderers {

/**
 * Texture loader.
 *
 * @class TextureLoader TextureLoader.h Renderers/TextureLoader.h
 */
class TextureLoader {
public:
    enum ReloadPolicy { RELOAD_ALWAYS, RELOAD_NEVER, RELOAD_DEFAULT };

    TextureLoader(Renderers::IRenderer& renderer);
    virtual ~TextureLoader();

    void Load(Scene::ISceneNode& node,             ReloadPolicy policy = RELOAD_DEFAULT);
    void Load(Resources::ITextureResourcePtr texr, ReloadPolicy policy = RELOAD_DEFAULT);
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
