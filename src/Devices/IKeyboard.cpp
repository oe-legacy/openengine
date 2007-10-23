// Interface for handling keyboard input
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Devices/IKeyboard.h>

namespace OpenEngine {
namespace Devices {

Event<KeyboardEventArg> IKeyboard::keyUpEvent;
Event<KeyboardEventArg> IKeyboard::keyDownEvent;

IKeyboard::IKeyboard() {}
IKeyboard::~IKeyboard() {}
bool IKeyboard::IsTypeOf(const std::type_info& inf) { 
    return typeid(IKeyboard) == inf; 
}

} // NS Devices
} // NS OpenEngine
