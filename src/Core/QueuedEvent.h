// Queued Event.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_QUEUED_EVENT_H_
#define _OE_QUEUED_EVENT_H_

#include <Core/IEvent.h>
#include <Core/IListener.h>
#include <list>

namespace OpenEngine {
namespace Core {

using std::list;

/**
 * Queued Event.
 * A queued event maintains a list of attached listeners and queued
 * events that have been sent. On release the queued events are sent
 * to the listener handlers. Sending of events happens in order and
 * all listeners will have received the first event before the next is
 * processed. Queued event implements the IListener interface in order
 * to chain event together.
 * 
 * @class QueuedEvent QueuedEvent.h Core/QueuedEvent.h
 * @tparam EventArg Argument type of the event.
 * @see IListener
 */
template <typename EventArg>
class QueuedEvent : public IEvent<EventArg>, public IListener<EventArg> {
protected:
    //! list of listeners
    list<IListener<EventArg>*> ls;

    //! event queue
    list<EventArg> eq;

public:

    virtual void Attach(IListener<EventArg>& listener) {
        ls.push_back(&listener);
    }

    virtual void Detach(IListener<EventArg>& listener) {
        ls.remove(&listener);
    }
    
    /**
     * Notify all listeners.
     * This will queue the event to be sent on Release.
     */
    virtual void Notify(EventArg arg) {
        eq.push_back(arg);
    }

    /**
     * Release all queued events to the attached listeners.
     * This will empty the event queue.
     */
    void Release() {
        typename list<EventArg>::iterator e;
        typename list<IListener<EventArg>*>::iterator l;
        for (e = eq.begin(); e != eq.end(); e++)
            for (l = ls.begin(); l != ls.end(); l++)
                (*l)->Handle(*e);
        eq.clear();
    }

    virtual void Handle(EventArg arg) {
        eq.push_back(arg);
    }

    virtual unsigned int Size() {
        return ls.size();
    }

};

} // NS Core
} // NS OpenEngine

#endif // _OE_QUEUED_EVENT_H_
