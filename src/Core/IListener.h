// Event Listener Interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_LISTENER_H_
#define _OE_INTERFACE_LISTENER_H_

namespace OpenEngine {
namespace Core {

/**
 * Listener Interface.
 * The listener interface must be implemented in order to listen for
 * an event. The interface is instantiated with the \a EventArg
 * corresponding to that of the \a Event object.
 * A listener is the \a observer in the \a Observer Pattern [GoF 293].
 *
 * Usage:
 * @code
 * // given that KeyEvent is a the EventArg type for IKeyboard::Events
 * class MyListener : public IListener<KeyEvent> {
 *   virtual void Handle(KeyEvent arg) {
 *     // do something on event
 *   }
 * }
 * // listening on an event is then done with
 * MyListener listener;
 * IKeyboard::keyEvent.Attach(listener);
 *
 * // to listen on several events multiple inheritance can be used
 * class MyListener : public IListener<EventArg1>, public IListener<EventArg2> {
 *   virtual void Handle(EventArg1 arg) {
 *     // do something on event type 1
 *   }
 *   virtual void Handle(EventArg2 arg) {
 *     // do something on event type 2
 *   }
 * }
 * @endcode
 *
 * @class IListener IListener.h Core/IListener.h
 * @tparam EventArg Argument type of the event handler.
 * @see IEvent
 */
template <typename EventArg>
class IListener {
public:

    /**
     * Handle event.
     * Callback method invoked by events parameterized by \a EventArg
     * that the listener is attached to.
     *
     * @param arg Argument supplied by the triggered event.
     */
    virtual void Handle(EventArg arg) = 0;
    
};

} // NS EventSystem
} // NS OpenEngine

#endif
