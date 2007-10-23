// Queued event listener.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _QUEUED_LISTENER_H_
#define _QUEUED_LISTENER_H_

#include <EventSystem/Listener.h>
#include <EventSystem/EventQueue.h>

namespace OpenEngine {
namespace EventSystem {

/**
 * Queued event listener.
 * Special listener type that delays processing of events by queuing
 * them on a \a EventQueue.
 *
 * @see EventQueue
 * @class QueuedListener QueuedListener.h EventSystem/QueuedListener.h
 */
template <class T, class EVENT_ARG_T>
class QueuedListener : public Listener<T, EVENT_ARG_T> {
private:
    //! queue to register at
    EventQueue& queue;
    //! stack of received event arguments
    vector<EVENT_ARG_T*> argList;

public:
    /**
     * Create a queued listener object wrapping an event handler.
     * Exactly as \a Listener with an additional event queue argument.
     *
     * @see Listener
     * @see EventQueue
     *
     * @param ins Reference to handler object of type \a T
     * @param ptr Address to handler method with arg of type
     *            \a EVENT_ARG_T
     * @param queue Event queue to register to
     */
    QueuedListener( T& ins, void (T::*ptr)(EVENT_ARG_T eventArg), EventQueue& queue)
        : Listener<T,EVENT_ARG_T>(ins, ptr), queue(queue) { }

    /**
     * Default destructor.
     */
    ~QueuedListener() {};

    /**
     * Update listener function.
     * Queues the event for later processing by EventQueue::Process().
     *
     * @param eventArg Argument form triggered event
     */
    void Update(EVENT_ARG_T eventArg) {
        argList.push_back(new EVENT_ARG_T(eventArg));
        queue.Add(this);
    }

    /**
     * Process a delayed event.
     * Pops the first arg of the stack and invokes the handler method.
     */
    void ProcessEvent(){
        if( !argList.empty() ) {
            // Get event argument from list
            EVENT_ARG_T& argument = *(argList.front());
            // Handle event
            Listener<T,EVENT_ARG_T>::Update(argument);
            // Event handled now remove argument from queue
            argList.erase(argList.begin());
        }
    }
};

} // NS Core
} // NS OpenEngine

#endif
