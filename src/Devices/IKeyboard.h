// Interface for handling keyboard input
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_KEYBOARD_H_
#define _OE_INTERFACE_KEYBOARD_H_

#include <Devices/Symbols.h>
#include <Core/IModule.h>
#include <Core/IEvent.h>

namespace OpenEngine {
namespace Devices {

using OpenEngine::Core::IModule;
using OpenEngine::Core::IEvent;

/**
 * Keyboard Event Argument.
 * Received as argument on key up/down events.
 *
 * @struct KeyboardEventArg IKeyboard.h Devices/IKeyboard.h
 */
struct KeyboardEventArg {
    enum KeyEventType { UNKNOWN, PRESS, RELEASE };
    KeyEventType type; //!< Key event type.
    Key          sym;  //!< Key symbol. @see Symbols.h
    KeyMod       mod;  //!< Key modifier. Possibly or'ed together
    KeyboardEventArg() : type(UNKNOWN), sym(KEY_UNKNOWN), mod(KEY_MOD_NONE) {}
};

/**
 * Keyboard input interface.
 *
 * @class IKeyboard IKeyboard.h Devices/IKeyboard.h
 */
class IKeyboard : public virtual IModule {
public:

    /**
     * Keyboard destructor.
     */
    virtual ~IKeyboard() {};

    /**
     * Key event list.
     */
    virtual IEvent<KeyboardEventArg>& KeyEvent() = 0;

};

} // NS Devices
} // NS OpenEngine

#endif // _OE_INTERFACE_KEYBOARD_H_
