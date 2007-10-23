// Base for all listener types.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _UNTYPED_LISTENER_H_
#define _UNTYPED_LISTENER_H_

namespace OpenEngine {
namespace EventSystem {

class AbstractEvent;
/**
 * Untyped Listener.
 * Just acts as a base interface for all other listeners.
 *
 * @class UntypedListener UntypedListener.h EventSystem/UntypedListener.h
 */
class UntypedListener {
public:
    /**
     * Process event.
     * This function is needed in order to implement the queuing
     * functionality found in QueuedListener and can safely be
     * ignored.
     */
    virtual void ProcessEvent() {}
    virtual ~UntypedListener(){}
};

} // NS EventSystem
} // NS OpenEngine

#endif // _UNTYPED_LISTENER_H_
