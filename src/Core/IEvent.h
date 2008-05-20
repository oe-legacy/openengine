// Event List Interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_EVENT_H_
#define _OE_INTERFACE_EVENT_H_

#include <Core/IListener.h>

namespace OpenEngine {
namespace Core {

/**
 * Event Interface.
 * The Event class template is responsible for maintaining a list of 
 * event listeners implementing the Listener interface and sending
 * events to them.
 * Corrsponds to the \a subject role in the \a observer pattern [GoF 293].
 * 
 * @class IEvent IEvent.h Core/IEvent.h
 * @tparam EventArg Argument type of the event.
 * @see IListener
 */
template <typename EventArg>
class IEvent {
public:

    /**
     * Attach a listener to the event.
     * All attached listeners will by notified of events. If a
     * listener is attached several times it will receive the
     * notification as many times as it is attached.
     *
     * @param listener Listener to attach
     */
    virtual void Attach(IListener<EventArg>& listener) = 0;

    /**
     * Detach a listener from the event.
     * After detaching a listener it will no longer receive
     * notifications. If the same listener has been attached several
     * times it must also be detached that same amount of times.
     *
     * @param listener Listener to detach
     */
    virtual void Detach(IListener<EventArg>& listener) = 0;
    
    /**
     * Notify all attached listeners with the supplied event argument.
     *
     * @param arg Argument to send with notification.
     * @see Listener::Handle(EventArg)
     */
    virtual void Notify(EventArg arg) = 0;

    /**
     * Get the event list size.
     *
     * @return Number of attached listeners
     */
    virtual int Size() = 0;

};

} // NS Core
} // NS OpenEngine

#endif // _OE_INTERFACE_EVENT_H_
