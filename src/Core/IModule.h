// Engine Module Interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MODULE_INTERFACE_H_
#define _OE_MODULE_INTERFACE_H_

#include <Core/IListener.h>
#include <Core/EngineEvents.h>

namespace OpenEngine {
namespace Core {

/**
 * Mix-in class for classes that implement an "engine module".
 * A module is exactly a class the implements the listener interface
 * on all engine events: \a InitializeEventArg, \a ProcessEventArg and
 * \a DeinitializeEventArg.
 */
class IModule : public virtual IListener<Core::InitializeEventArg>,
                public virtual IListener<Core::ProcessEventArg>,
                public virtual IListener<Core::DeinitializeEventArg> {
public:
    virtual ~IModule() {}
};

} // NS Core
} // NS OpenEngine

#endif // NS _OE_MODULE_INTERFACE_H_
