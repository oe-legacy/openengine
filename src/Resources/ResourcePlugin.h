#ifndef _RESOURCE_PLUGIN_
#define _RESOURCE_PLUGIN_

#include <Resources/IResourcePlugin.h>
#include <string>

using OpenEngine::Resources::IResourcePlugin;
using std::string;

/**
 * Texture resource smart pointer.
 */
//typedef boost::shared_ptr<ITextureResource> ITextureResourcePtr;

/**
 * Resources plug-in.
 *
 * @class ResourcePlugin
 */
template<class T>
class ResourcePlugin : public virtual IResourcePlugin {
public:
    /**
     * Create a new texture resource from a file.
     *
     * @param file Texture resource file.
     * @return Texture resource pointer.
     */
  virtual boost::shared_ptr<T> CreateResource(string file) = 0;
};

#endif //_RESOURCE_PLUGIN_
