// Implementation file for the SDL implementation of IMouse and
// IKeyboard
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// Module header
#include <Devices/SDLInput.h>

// OpenEngine key and button symbol definitions
#include <Devices/Symbols.h>

// OpenEngine logging library
#include <Logging/Logger.h>

// OpenEngine game engine
#include <Core/IGameEngine.h>

namespace OpenEngine {
namespace Devices {

/**
 * Class constructor.
 */
SDLInput::SDLInput() {
    // initialize mouse state
    state.x = 0;
    state.y = 0;
    state.buttons = BUTTON_NONE;
}

/**
 * Class destructor.
 */
SDLInput::~SDLInput() {

}

/**
 * Type lookup function.
 *
 * @see IModule::IsTypeOf()
 */
bool SDLInput::IsTypeOf(const std::type_info& inf) { 
    return (typeid(SDLInput) == inf 
            || IKeyboard::IsTypeOf(inf)
            || IMouse::IsTypeOf(inf));
}

/**
 * Module initialization method.
 * Called once on engine start up after all modules have been loaded.
 *
 * @see IModule::Initialize()
 */
void SDLInput::Initialize() {
    // Check that SDL has been initialized (SDLFrame does it)
    if (!SDL_WasInit(SDL_INIT_VIDEO))
        logger.error << "SDL was not initialized" << logger.end;
}

/**
 * Module process method.
 * This is the main processing method of the module, called for every
 * module circulation.
 *
 * @see IModule::Process()
 */
void SDLInput::Process(const float deltaTime, const float percent) {
    KeyboardEventArg karg;
    MouseMovedEventArg mmarg;
    // Loop until there are no events left on the queue
    while(SDL_PollEvent(&event) && (SDL_GetAppState() & SDL_APPINPUTFOCUS )) {
        switch (event.type) {
        case SDL_QUIT:
            OpenEngine::Core::IGameEngine::Instance().Stop();
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            // set key symbol and modifier
            karg.sym = (Key)    event.key.keysym.sym;
            karg.mod = (KeyMod) event.key.keysym.mod;
            // notify event
            if (event.type == SDL_KEYUP)
                IKeyboard::keyUpEvent.Notify(karg);
            else
                IKeyboard::keyDownEvent.Notify(karg);
            break;
        case SDL_MOUSEMOTION:
            // set mouse position and get button modifiers
            state.buttons = mmarg.buttons = (MouseButton)(int)SDL_GetMouseState(NULL, NULL);
            state.x = mmarg.x = event.motion.x;
            state.y = mmarg.y = event.motion.y;
            mmarg.dx = event.motion.xrel;
            mmarg.dy = event.motion.yrel;
            IMouse::mouseMovedEvent.Notify(mmarg);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            // set mouse position and get button modifiers
            state.buttons = (MouseButton) (int) SDL_GetMouseState(NULL, NULL);
            state.x = event.button.x;
            state.y = event.button.y;
            // create a mouse event
            MouseButtonEventArg marg;
            marg.state = state;
            marg.button = (MouseButton) (int) SDL_BUTTON(event.button.button);
            if (event.type == SDL_MOUSEBUTTONUP)
                IMouse::mouseUpEvent.Notify(marg);
            else
                IMouse::mouseDownEvent.Notify(marg);
            break;
        } // switch on event type
    } // while sdl event
}

/**
 * Module deinitialization method.
 * Called once on engine shutdown.
 *
 * @see IModule::Deinitialize()
 */
void SDLInput::Deinitialize() {

}

/**
 * Hide the mouse cursor.
 *
 * @see IMouse::HideCursor()
 */
void SDLInput::HideCursor() {
    SDL_ShowCursor(SDL_DISABLE);
}

/**
 * Show the mouse cursor.
 *
 * @see IMouse::ShowCursor()
 */
void SDLInput::ShowCursor() {
    SDL_ShowCursor(SDL_ENABLE);
}

/**
 * Set cursor position.
 *
 * @param x Position on x-axis
 * @param y Position on y-axis
 *
 * @see IMouse::SetCursor()
 */
void SDLInput::SetCursor(int x, int y) {
    if (SDL_GetAppState() & SDL_APPINPUTFOCUS)
        SDL_WarpMouse(x, y);
}

/**
 * Get the current mouse state.
 *
 * @return The current mouse state
 *
 * @see IMouse::GetState()
 */
MouseState SDLInput::GetState() {
    return state;
}

} // NS Devices
} // NS OpenEngine
