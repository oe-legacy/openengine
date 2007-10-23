// Engine module interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/IModule.h>
#include <Core/IGameEngine.h>

namespace OpenEngine {
namespace Core {

/**
 * Default constructor.
 */
IModule::IModule() {}

/**
 * Default destructor.
 * Removes module form engine.
 */
IModule::~IModule() {
    // Remove from Engine if ever added.
    OpenEngine::Core::IGameEngine::Instance().RemoveModule(*this);
}

} // NS Core
} // NS OpenEngine
