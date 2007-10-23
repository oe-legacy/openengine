// Resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef IRESOURCE_H_
#define IRESOURCE_H_

#include <boost/shared_ptr.hpp>
#include <string>

namespace OpenEngine {
namespace Resources {

using std::string;

/**
 * Resource interface.
 *
 * @class IResource IResource.h Resources/IResource.h
 */
class IResource {
public:

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

/**
 * Resource smart pointer.
 */
typedef boost::shared_ptr<IResource> IResourcePtr;

/**
 * Resource plug-in interface.
 *
 * @class IResourcePlugin IResource.h Resources/IResource.h
 */
class IResourcePlugin {
public:

    /**
     * Get the file extension for this resource type.
     *
     * @return Resource type extension Lowercase
     */
    virtual string GetExtension() = 0;

    /**
     * Default destructor.
     */
    virtual ~IResourcePlugin() {}
};

} // NS Resource
} // NS OpenEngine

#endif
