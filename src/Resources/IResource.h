// Resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef IRESOURCE_H_
#define IRESOURCE_H_

#include <boost/shared_ptr.hpp>
#include <Core/IEvent.h>
#include <Core/Event.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Core::IEvent;
using OpenEngine::Core::Event;

/**
 * Resource interface.
 *
 * @class IResource IResource.h Resources/IResource.h
 */
template <class EventType>
class IResource {
protected:
    Event<EventType> changedEvent;

public:

    virtual IEvent<EventType>& ChangedEvent() {
        return changedEvent;
    }

    /**
     * Load the resource.
     * Calling load several times in a row must have the same result
     * as just calling it once. In order to force reload one must call
     * Unload and then Load again.
     */
	virtual void Load() = 0;

    /**
     * Unload the resource.
     */
	virtual void Unload() = 0;
    
    /**
     * Default destructor.
     */
    virtual ~IResource() {}

};

} // NS Resource
} // NS OpenEngine

#endif
