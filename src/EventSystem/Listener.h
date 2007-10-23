// Event Listener
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _LISTENER_H_
#define _LISTENER_H_

#include <EventSystem/AbstractListener.h>

namespace OpenEngine {
namespace EventSystem {

/**
 * Untyped Listener.
 * Forms a generic \a Observer [GoF 293] in connection with the \a
 * AbstractListener template, allowing despatching to methods with
 * different argument types.
 *
 * @class Listener Listener.h EventSystem/Listener.h
 * @see AbstractListener
 */
template <class T, class EVENT_ARG_T>
class Listener : public AbstractListener<EVENT_ARG_T> {
protected:
    //! reference to handler instance
    T& instance;
    //! handler method
    void (T::*memberFunc)(EVENT_ARG_T eventArg);

public:

    /**
     * Creates a new listener object wrapping a user method.
     * Used to forward variable event arguments to variable handler
     * functions.
     *
     * Usage:
     * \code
     * \\ say we have a handle function:
     * MyHandler::HandelEvent(SomeEventArg e) { handler code; }
     * \\ create a listener wrapper
     * MyHandler* myObj = new MyHandler();
     * Listener<MyHandler, SomeEventArg> listener(*myObj,
     *                                            &MyHandler::HandelEvent);
     * \\ now we register it with a known event:
     * someEventList.Add(&listener);
     * \\ were someEventList must be of type Event<SomeEventArg>.
     * \endcode
     *
     * @param ins Reference to handler object of type \a T
     * @param ptr Address to handler method with arg of type \a EVENT_ARG_T
     */
    Listener(T& ins, void (T::*ptr)(EVENT_ARG_T eventArg)): instance(ins) {
        memberFunc = ptr;
    }

    /**
     * Default destructor.
     */
    ~Listener() { }
    
    /**
     * Update listener function.
     * Invoke the callback method on the specific class type.
     *
     * @param eventArg Argument form triggered event
     */
    virtual void Update(EVENT_ARG_T eventArg) {
        (instance.*memberFunc)(eventArg);
    }
    
};

} // NS EventSystem
} // NS OpenEngine

#endif
