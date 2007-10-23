// Game factory interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_GAME_FACTORY_H_
#define _INTERFACE_GAME_FACTORY_H_

#include <Core/IGameEngine.h>
#include <Display/IFrame.h>
#include <Renderers/IRenderer.h>

namespace OpenEngine {
namespace Core {

using OpenEngine::Display::IFrame;
using OpenEngine::Renderers::IRenderer;

/**
 * Abstract game factory interface.
 *
 * The game factory is responsible for populating a game engine with
 * modules and customizing various engine settings. It is an example
 * of the Abstract Factory pattern from [GoF 87].
 *
 * The game factory must be initiated and passed to the
 * IGameEngine::Start method.
 *
 * @see IGameEngine::Start
 *
 * @class IGameFactory IGameFactory.h Core/IGameFactory.h
 */
class IGameFactory {
public:

    virtual ~IGameFactory() {};
    
    /**
     * Setup a game engine.
     * 
     * @param engine The game engine to setup.
     * @return True if setup went well and the main loop should
     *         start, false if we should abort.
     */
    virtual bool SetupEngine(IGameEngine& engine) = 0;

    /**
     * Frame factory method.
     * This method allows users to customize the engine frame.
     *
     * @see Display::IFrame
     * @return An implementation of the frame interface.
     */
    virtual IFrame* GetFrame() = 0;

    /**
     * Renderer factory method.
     * This method allows users to customize the engine rendering module.
     *
     * @see Renderers::IRenderer
     * @return An implementation of the renderer interface.
     */
    virtual IRenderer* GetRenderer() = 0;

};

} // NS Core
} // NS OpenEngine

#endif // _INTERFACE_GAME_FACTORY_H_
