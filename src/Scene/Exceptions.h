// Scene exceptions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Core::Exception;
using std::string;

/**
 * Invalid scene operation exception.
 *
 * @class InvalidSceneOperation Exceptions.h Scene/Exceptions.h
 */
class InvalidSceneOperation : public Exception {
public:
    //! Exception with a string message.
    InvalidSceneOperation(string msg) : Exception(msg) {};
};

} // NS Scene
} // NS OpenEngine
