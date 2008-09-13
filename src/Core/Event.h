// Basic Event.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_EVENT_H_
#define _OE_EVENT_H_

#include <Core/IEvent.h>
#include <Core/IListener.h>
#include <list>

namespace OpenEngine {
namespace Core {

using std::list;

/**
 * Basic Event.
 * This is a basic implementation of a event list. It maintains a list
 * of attached listeners and invokes their handlers immediately on
 * event notification.
 * 
 * @class Event Event.h Core/Event.h
 * @tparam EventArg Argument type of the event.
 * @see Listener
 */
template <typename EventArg>
class Event : public IEvent<EventArg> {
protected:
    //! list of listeners
    list<IListener<EventArg>*> ls;

public:

    virtual void Attach(IListener<EventArg>& listener) {
        ls.push_back(&listener);
    }

    virtual void Detach(IListener<EventArg>& listener) {
        ls.remove(&listener);
    }
    
    /**
     * Notify all listeners.
     * This will immediately invoke the Handle(EventArg) method on each
     * attached listener.
     */
    virtual void Notify(EventArg arg) {
        typename list<IListener<EventArg>*>::iterator itr;
        for (itr=ls.begin(); itr != ls.end(); itr++)
            (*itr)->Handle(arg);
    }

    unsigned int Size() {
        return ls.size();
    }

};

} // NS Core
} // NS OpenEngine

#endif // _OE_EVENT_H_
