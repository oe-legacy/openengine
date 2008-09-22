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

class IModule : public virtual IListener<InitializeEventArg>,
                public virtual IListener<ProcessEventArg>,
                public virtual IListener<DeinitializeEventArg> {
public:
    virtual ~IModule() {}
};

} // NS Core
} // NS OpenEngine

#endif // NS _OE_MODULE_INTERFACE_H_
