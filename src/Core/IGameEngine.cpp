// Game engine interface
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/IGameEngine.h>

namespace OpenEngine {
namespace Core {

// Initialize static instance pointer to NULL
IGameEngine* IGameEngine::instance = NULL;

// Documentation in header file.
IGameEngine::IGameEngine() {}

// Documentation in header file.
IGameEngine::~IGameEngine() {
    instance = NULL;
}
// Documentation in header file.
IGameEngine& IGameEngine::Instance() {
    return *instance;
}

} // NS Core
} // NS OpenEngine
