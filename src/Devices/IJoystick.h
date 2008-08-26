
#ifndef _OE_INTERFACE_JOYSTICK_H_
#define _OE_INTERFACE_JOYSTICK_H_

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
     JoystickState state; //!< current joystick state
     JoystickButton button; //!< button that triggered the event
     JoystickButtonEventArg() : button(JBUTTON_NONE) {}
 };

    class IJoystick : public virtual IModule {
    public:
	
	virtual ~IJoystick() {};

	virtual IEvent<JoystickButtonEventArg>& JoystickButtonEvent() = 0;
	
	virtual IEvent<JoystickAxisEventArg>& JoystickAxisEvent() = 0;
    };

}
}


#endif
