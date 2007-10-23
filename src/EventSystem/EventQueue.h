// Event queue for the QueueListener system.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _EVENT_QUEUE_H_
#define _EVENT_QUEUE_H_

#include <EventSystem/UntypedListener.h>
#include <vector>

namespace OpenEngine {
namespace EventSystem {

using std::vector;

/**
 * Event queue for the QueueListener system.
 *
 * @class EventQueue EventQueue.h EventSystem/EventQueue.h
 */
class EventQueue {
private:
    //! listeners of queued events
    vector<UntypedListener*> q;
public:    
    void Add(UntypedListener* l);
    void Process();
};

} // NS EventSystem
} // NS OpenEngine

#endif // _EVENT_QUEUE_H_
