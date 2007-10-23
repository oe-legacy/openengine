// Header file for the SDL implementation of IMouse and IKeyboard.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SDL_INPUT_MODULE_H_
#define _SDL_INPUT_MODULE_H_

// Cross platform SDL header
#include <Meta/SDL.h>

// OpenEngine input device interfaces
#include <Devices/IMouse.h>
#include <Devices/IKeyboard.h>

namespace OpenEngine {
namespace Devices {

/**
 * SDL implementation of IMouse and IKeyboard.
 *
 * Implementation and method documentation is in the SDLInput.cpp
 * file. Additional documentation is in the interface files IMouse.h
 * and IKeyboard.h
 */
class SDLInput : public IKeyboard, public IMouse {

private:

    SDL_Event        event;
    MouseState       state;

public:

    SDLInput();
    ~SDLInput();

    bool IsTypeOf(const std::type_info& inf);

    // IModule methods
    void Initialize();
    void Process(const float deltaTime, const float percent);
    void Deinitialize();

    // IMouse methods
    void HideCursor();
    void ShowCursor();
    void SetCursor(int x, int y);
    MouseState GetState();

};

} // NS Devices
} // NS OpenEngine

#endif // _SDL_INPUT_MODULE_H_
