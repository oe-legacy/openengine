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
#include <list>
#include <string>

namespace OpenEngine {
namespace Resources {

using std::string;
using std::list;

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
private:
	
	/// List of extensions this plugins knows how to handle
	list<string> extensions;

protected:

	/** 
	 * Add new extension this plugin can handle
	 * 
	 * @param ext Resource type extension in Lowercase
	 */
	void AddExtension(string ext) {
		extensions.push_back(ext);
	};

public:
	
	/** 
	 * Checks if this plugin accepts the given extension.
	 * 
	 * @param ext Resource type extension Lowercase
	 * 
	 * @return If the given extension is accepted by this plugin
	 */
    bool AcceptsExtension(string ext) {
		for (list<string>::iterator itr = extensions.begin(); itr != extensions.end(); itr++ ) {
			if ( (*itr) == ext) {
				return true;
			}
		}
		return false;
	};

    /**
     * Default destructor.
     */
    virtual ~IResourcePlugin() {}
};

} // NS Resource
} // NS OpenEngine

#endif
