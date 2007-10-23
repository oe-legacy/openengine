// Abstract Event Listener
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _ABSTRACT_LISTENER_H_
#define _ABSTRACT_LISTENER_H_

#include <EventSystem/UntypedListener.h>

namespace OpenEngine {
namespace EventSystem {

/** 
 * Untyped Abstract Listener.
 * Forms a generic \a Observer [GoF 293] in connection with the \a
 * Listener template, allowing despatching to methods with different
 * argument types.
 *
 * @class AbstractListener AbstractListener.h EventSystem/AbstractListener.h
 * @see Listener
 */
template <class EVENT_ARG_T>
class AbstractListener : public UntypedListener {
public:

    /**
     * Default constructor.
     */
    AbstractListener() {}

    /**
     * Default destructor.
     */
    virtual ~AbstractListener() {}
    
    /**
     * Update listener function.
     * Pure virtual - must be implemented in subclass.
     *
     * @param eventArg Argument from triggered event
     */
    virtual void Update(EVENT_ARG_T eventArg) = 0;

};

} // NS EventSystem
} // NS OpenEngine

#endif
