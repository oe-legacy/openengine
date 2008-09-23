// Joystick interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_JOYSTICK_H_
#define _OE_INTERFACE_JOYSTICK_H_

#include <Devices/Symbols.h>
#include <Core/IModule.h>
#include <Core/IEvent.h>

namespace OpenEngine {
namespace Devices {

/**
 * Joystick state
 * Container for joystick state information.
 * Each axis has a number with a value attached to it, that number
 * is used as entry into the axisState array.
 *
 * @struct JoystickState IJoystick.h Devices/IJoystick.h
 */
struct JoystickState {
    int axisState[28]; //!<optimized ie made for Logitech Rumblepad
    JoystickButton buttons; //!< currently activated buttons
    JoystickState() : buttons(JBUTTON_NONE) {}
};


struct JoystickAxisEventArg {
	JoystickState state;
	int axis;
	int value;
};

/**
 * Joystick button change event argument
 * Sent to handlers listening on joystickUpEvent and joystickDownEvent.
 *
 * @struct JoystickButtonEventArg IJoystick.h Devices/IJoystick.h
 */
struct JoystickButtonEventArg {
    enum JButtonEventType { UNKNOWN, PRESS, RELEASE };
    JButtonEventType type;
    JoystickState state;        //!< current joystick state
    JoystickButton button;      //!< button that triggered the event
    JoystickButtonEventArg() : button(JBUTTON_NONE) {}
};

class IJoystick : public virtual Core::IModule {
public:
	virtual ~IJoystick() {};
	virtual Core::IEvent<JoystickButtonEventArg>& JoystickButtonEvent() = 0;
	virtual Core::IEvent<JoystickAxisEventArg>& JoystickAxisEvent() = 0;
};

}
}


#endif
