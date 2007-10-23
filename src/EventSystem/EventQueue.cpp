// Event queue for the QueueListener system.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <EventSystem/EventQueue.h>

namespace OpenEngine {
namespace EventSystem {

/**
 * Add a listener to the event queue.
 *
 * @param l Listener of the triggered event
 */
void EventQueue::Add(UntypedListener* l) {
    q.push_back(l);
}

/**
 * Process all waiting event listeners.
 */
void EventQueue::Process() {
    for( unsigned int i=0; i<q.size(); i++ )
        ((UntypedListener*)q[i])->ProcessEvent();
    // reset queue
    q = vector<UntypedListener*>();
}

} // NS EventSystem
} // NS OpenEngine
