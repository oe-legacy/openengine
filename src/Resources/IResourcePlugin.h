#ifndef _RESOURCE_PLUGIN_INTERFACE_
#define _RESOURCE_PLUGIN_INTERFACE_

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

/**
 * Resources plug-in interface.
 *
 * @class ResourcePlugin
 */
template<class T>
class IResourcePlugin {
public:
    /**
     * Create a new texture resource from a file.
     *
     * @param file Texture resource file.
     * @return Texture resource pointer.
     */
    virtual boost::shared_ptr<T> CreateResource(std::string file) = 0;

    /**
     * Default destructor.
     */
    virtual ~IResourcePlugin() {}

	/** 
	 * Checks if this plugin accepts the given extension.
	 * 
	 * @param ext Resource type extension Lowercase
	 * 
	 * @return If the given extension is accepted by this plugin
	 */
    bool AcceptsExtension(std::string ext) {
        std::list<std::string>::iterator itr = extensions.begin();
		for (; itr != extensions.end(); itr++ ) {
			if ( (*itr) == ext) {
				return true;
			}
		}
		return false;
	}

private:
	
	/// List of extensions this plugins knows how to handle
    std::list<std::string> extensions;

protected:

	/** 
	 * Add new extension this plugin can handle
	 * 
	 * @param ext Resource type extension in Lowercase
	 */
	void AddExtension(std::string ext) {
		extensions.push_back(ext);
	}

};

#endif //_RESOURCE_PLUGIN_INTERFACE_
