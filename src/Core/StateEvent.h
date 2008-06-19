// State Event.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_STATE_EVENT_H_
#define _OE_STATE_EVENT_H_

#include <Core/IEvent.h>
#include <Core/IListener.h>
#include <list>

namespace OpenEngine {
namespace Core {

using std::list;

/**
 * State Event.
 * A state event maintains a list of attached listeners and state
 * that decides if received events will be sent to the listeners.
 * State event implements the IListener interface in order
 * to chain event together.
 * 
 * @class StateEvent StateEvent.h Core/StateEvent.h
 * @tparam EventArg Argument type of the event.
 * @see IListener
 */
template <typename EventArg>
class StateEvent : public IEvent<EventArg>, public IListener<EventArg> {
protected:
    //! list of listeners
    list<IListener<EventArg>*> ls;

    //! current state
    bool state;

public:

    /**
     * Default constructor.
     * Starts with the event forwarding state enabled.
     */
    StateEvent() : state(true) {};

    /**
     * Selective constructor.
     * Starts with the event forwarding set to \a state.
     */
    StateEvent(bool state) : state(state) {};

    virtual void Attach(IListener<EventArg>& listener) {
        ls.push_back(&listener);
    }

    virtual void Detach(IListener<EventArg>& listener) {
        ls.remove(&listener);
    }
    
    /**
     * Notify all listeners if notification state is on.
     */
    virtual void Notify(EventArg arg) {
        if (!state) return;
        typename list<IListener<EventArg>*>::iterator itr;
        for (itr=ls.begin(); itr != ls.end(); itr++)
            (*itr)->Handle(arg);
    }

    /**
     * Turn on event notification state.
     */
    void On() {
        state = true;
    }

    /**
     * Turn off event notification state.
     */
    void Off() {
        state = false;
    }

    /**
     * Toggle the event notification state.
     */
    void Toggle() {
        state = !state;
    }
    
    /**
     * Get the current state.
     */
    bool GetState() {
        return state;
    }

    //! Forwards to Notify
    virtual void Handle(EventArg arg) {
        Notify(arg);
    }

    virtual int Size() {
        return ls.size();
    }

};

} // NS Core
} // NS OpenEngine

#endif // _OE_STATE_EVENT_H_
