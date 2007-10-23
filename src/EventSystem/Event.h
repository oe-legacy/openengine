// Abstract Event Type
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _EVENT_H_
#define _EVENT_H_

#include <list>
#include <EventSystem/AbstractListener.h>
#include <EventSystem/AbstractEvent.h>

namespace OpenEngine {
namespace EventSystem {

using std::list;

/**
 * Event Type.
 * The Event class template is responsible for maintaining the list of 
 * event listeners created with the Listener template.
 * Corrsponds to the \a subject role in the \a observer pattern [GoF 293].
 * 
 * @class Event Event.h EventSystem/Event.h
 * @see Listener
 */
template <class T>
class Event : public AbstractEvent {
private:
    //! list of listeners
    list< AbstractListener<T>* > callbackList;

public:

    /**
     * Add type specified listener
     *
     * @param listener Listener to add
     */
    void Add(AbstractListener<T>* listener) {
        callbackList.push_back(listener);
    }

    /**
     * Remove listener from event
     *
     * @param listener Listener to remove
     */
    void Remove(AbstractListener<T>* listener) {
        callbackList.remove(listener);
    }
    
    /**
     * Notify event trigger
     *
     * @param eventArg Argument to send with notification
     */
    void Notify(T eventArg) {
        typename list<AbstractListener<T>*>::iterator itr;
        for (itr=callbackList.begin(); itr != callbackList.end(); itr++)
            (*itr)->Update(eventArg);
    }

    /**
     * Get number of event listeners.
     *
     * @return Number of event listeners
     */
    int NumListeners() {
        return callbackList.size();
    }
};

} // NS EventSystem
} // NS OpenEngine

#endif
