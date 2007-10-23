// IMouse interface stub
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Devices/IMouse.h>

namespace OpenEngine {
namespace Devices {

Event<MouseButtonEventArg> IMouse::mouseUpEvent;
Event<MouseButtonEventArg> IMouse::mouseDownEvent;
Event<MouseMovedEventArg> IMouse::mouseMovedEvent;

IMouse::IMouse() {}
IMouse::~IMouse() {}
bool IMouse::IsTypeOf(const std::type_info& inf) { 
    return typeid(IMouse) == inf; 
}

/**
 * Check if a button sequence is pressed.
 *
 * @param b Mouse button to check (possibly several OR'd together)
 * @return Are the buttons currently pressed
 */
bool IMouse::IsPressed(MouseButton b) {
    return (b & GetState().buttons) == b;
}

} // NS Devices
} // NS OpenEngine
