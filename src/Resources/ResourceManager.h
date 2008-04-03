// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <Resources/ResourceManager.h>
#include <Resources/DirectoryManager.h>
#include <Resources/Exceptions.h>
#include <Resources/File.h>
#include <Utils/Convert.h>
#include <Resources/TGAResource.h>
#include <Resources/ResourcePlugin.h>
#include <string>
#include <map>
#include <vector>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Utils::Convert;
using namespace std;

/**
 * Resource manager.
 *
 * @class ResourceManager ResourceManager.h Resources/ResourceManager.h
 */
template<class T>
class ResourceManager {
private:
    static vector<ResourcePlugin<T>*> plugins;
    static map<string,  boost::shared_ptr<T> > resources;

public:

/**
 * Add shader resource plug-in.
 *
 * @param plugin Shader plug-in
 */
static void AddPlugin(ResourcePlugin<T>* plugin) {
  plugins.push_back(plugin);
}
  

/**
 * Create a resource object.
 *
 * @param filename Texture file
 * @return Texture resource
 * @throws ResourceException if the texture format is unsupported or the file does not exist
 */
  static boost::shared_ptr<T> Create(const string filename) {

  // check if the texture has previously been requested
    typename map<string, boost::shared_ptr<T> >::iterator res;
    res = resources.find(filename);
 
  if (res != resources.end())
    return res->second;

  // get the file extension
  string ext = Convert::ToLower(File::Extension(filename));

  typename vector< ResourcePlugin<T>* >::iterator plugin;
  for (plugin = plugins.begin(); plugin != plugins.end() ; plugin++) {
    if ((*plugin)->AcceptsExtension(ext)) {
      break;
    }
  }

  // load the resource
  if (plugin != plugins.end()) {
    string fullname = DirectoryManager::FindFileInPath(filename);
    boost::shared_ptr<T> resource = (*plugin)->CreateResource(fullname);
    resources[filename] = resource;
    return resource;
  } else
    logger.warning << "Plugin for ." << ext << " not found." << logger.end;

  throw ResourceException("Unsupported file format: " + filename);
}

  static void Shutdown() {
    resources.clear();
  }
};

  template<class T>
  vector<ResourcePlugin<T>*> ResourceManager<T>::plugins = vector<ResourcePlugin<T>*>();

  template<class T>
  map<string, boost::shared_ptr<T> > ResourceManager<T>::resources = 
    map<string, boost::shared_ptr<T> >();

} // NS Resources
} // NS OpenEngine

#endif // _RESOURCE_MANAGER_H_
