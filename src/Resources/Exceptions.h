// Resource exceptions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _RESOURCE_EXCEPTIONS_H_
#define _RESOURCE_EXCEPTIONS_H_

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Core::Exception;
using std::string;

/**
 * Resource exception.
 *
 * @class ResourceException Exceptions.h Resources/Exceptions.h
 */
class ResourceException : public Exception {
public:
    ResourceException() : Exception() {};
    //! Exception with a string message.
    ResourceException(string msg) : Exception(msg) {};
};

} // NS Resources
} // NS OpenEngine

#endif // _RESOURCE_EXCEPTIONS_H_
