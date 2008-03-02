// Resource Manager.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>


#include <Resources/ResourceManager.h>
#include <Resources/Exceptions.h>
#include <Resources/File.h>
#include <Logging/Logger.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Utils::Convert;
namespace fs = boost::filesystem;

// initialization of static members
list<string> ResourceManager::paths = list<string>();
map<string, string> ResourceManager::pathcache = map<string, string>();

map<string, ITextureResourcePtr> ResourceManager::textures = map<string, ITextureResourcePtr>();
map<string, IModelResourcePtr>   ResourceManager::models   = map<string, IModelResourcePtr>();
map<string, IShaderResourcePtr>  ResourceManager::shaders  = map<string, IShaderResourcePtr>();

vector<ITextureResourcePlugin*>  ResourceManager::texturePlugins = vector<ITextureResourcePlugin*>();
vector<IModelResourcePlugin*>	 ResourceManager::modelPlugins	 = vector<IModelResourcePlugin*>();
vector<IShaderResourcePlugin*>	 ResourceManager::shaderPlugins	 = vector<IShaderResourcePlugin*>();

/** 
 * Append given path to the global path list
 * 
 * @param str File path to append
 */
void ResourceManager::AppendPath(string str) {
    paths.push_back(str);
}

/** 
 * Prepend given path to the global path list
 * 
 * @param str File path to prepend
 */
void ResourceManager::PrependPath(string str) {
	paths.push_front(str);
}

/** 
 * Test if the given path p is already in the search path
 * 
 * @param p Path to test
 * 
 * @return If the given path is already added
 */
bool ResourceManager::IsInPath(string p) {
	list<string>::iterator itr;
	for (itr = paths.begin(); itr != paths.end() ; itr++) {
		if ((*itr) == p) {
			return true;
		}
	}
	return false;
}

/** 
 * Find a given file in the search paths
 * 
 * @param file Filename to find in path
 * 
 * @return The complete file path or the empty string if file is not found in path
 */
string ResourceManager::FindFileInPath(string file) { 
	// looking in path cache for file -> fullpath
	map<string, string>::iterator thefile = pathcache.find(file);
	if (thefile != pathcache.end())
        return thefile->second;

	// file not found in cache, looking it up!
	list<string> possibles;
	
	for (list<string>::iterator itr = paths.begin(); itr != paths.end(); itr++) {
		string p = (*itr) + file;
		if (fs::exists(p)) {
			possibles.push_back(p);
		}
	}

	if (possibles.size() == 1) {
		pathcache[file] = *possibles.begin();
		return *possibles.begin();
	} else if (possibles.size() > 1) {
		string s = *possibles.begin();
		logger.warning << "Found more then one file matching the name given: " << file << logger.end;
		for (list<string>::iterator itr = possibles.begin(); itr != possibles.end(); itr++) {
			logger.warning << (*itr) << logger.end;
		}
		pathcache[file] = s;
		return s;
	} 
	throw ResourceException("Could not locate: " + file);
}

/**
 * Add texture resource plug-in.
 *
 * @param plugin Texture plug-in
 */
void ResourceManager::AddTexturePlugin(ITextureResourcePlugin* plugin) {
	texturePlugins.push_back(plugin);
}

/**
 * Add model resource plug-in.
 *
 * @param plugin Model plug-in
 */
void ResourceManager::AddModelPlugin(IModelResourcePlugin* plugin) {
		modelPlugins.push_back(plugin);
}

/**
 * Add shader resource plug-in.
 *
 * @param plugin Shader plug-in
 */
void ResourceManager::AddShaderPlugin(IShaderResourcePlugin* plugin) {
		shaderPlugins.push_back(plugin);
}

/**
 * Create a texture resource object.
 *
 * @param filename Texture file
 * @return Texture resource
 * @throws ResourceException if the texture format is unsupported or the file does not exist
 */
ITextureResourcePtr ResourceManager::CreateTexture(const string filename) {
    // check if the texture has previously been requested
	map<string, ITextureResourcePtr>::iterator tex = textures.find(filename);
	if (tex != textures.end())
        return tex->second;

    // get the file extension
    string ext = Convert::ToLower(File::Extension(filename));
	vector<ITextureResourcePlugin*>::iterator plugin;
	for (plugin = texturePlugins.begin(); plugin != texturePlugins.end() ; plugin++) {
		if ((*plugin)->AcceptsExtension(ext)) {
			break;
		}
	}
	
    // load the resource
	if (plugin != texturePlugins.end()) {
		string fullname = FindFileInPath(filename);
		ITextureResourcePtr texture = (*plugin)->CreateResource(fullname);
        textures[filename] = texture;
        return texture;
    } else
        logger.warning << "Plugin for ." << ext << " not found." << logger.end;

	throw ResourceException("Unsupported file format: " + filename);
}

/**
 * Create a model resource object.
 *
 * @param filename Model file. 
 * @return Model resource.
 * @throws ResourceException if the model format is unsupported or the file does not exist
 */
IModelResourcePtr ResourceManager::CreateModel(const string filename) {
    // check if the model has previously been requested
	map<string, IModelResourcePtr>::iterator res = models.find(filename);
	if(res != models.end())
  		return res->second;

    // get the file extension
    string ext = Convert::ToLower(File::Extension(filename));
	vector<IModelResourcePlugin*>::iterator plugin;
	for (plugin = modelPlugins.begin(); plugin != modelPlugins.end() ; plugin++) {
		if ((*plugin)->AcceptsExtension(ext)) {
			break;
		}
	}
	
	// load the resource
	if (plugin != modelPlugins.end()) {
		string fullname = FindFileInPath(filename);
		IModelResourcePtr model = (*plugin)->CreateResource(fullname);
        models[filename] = model;
        return model;
    } else
        logger.warning << "Plugin for ." << ext << " not found." << logger.end;

    throw ResourceException("Unsupported file format: " + filename);
}

/**
 * Create a shader resource object.
 *
 * @param filename Shader file
 * @return Shader resource
 * @throws ResourceException if the shader format is unsupported or the file does not exist
 */
IShaderResourcePtr ResourceManager::CreateShader(const string filename) {
    // check if the shader has previously been requested
 	map<string, IShaderResourcePtr>::iterator res = shaders.find(filename);
 	if (res != shaders.end())
   		return res->second;

    // get the file extension
    string ext = Convert::ToLower(File::Extension(filename));
	vector<IShaderResourcePlugin*>::iterator plugin;
	for (plugin = shaderPlugins.begin(); plugin != shaderPlugins.end(); plugin++) {
		if ((*plugin)->AcceptsExtension(ext)) {
			break;
		}
	}

    // load the resource
	if (plugin != shaderPlugins.end()) {
		string fullname = FindFileInPath(filename);
		IShaderResourcePtr shader = (*plugin)->CreateResource(fullname);
        shaders[filename] = shader;
        return shader;
    } else
        logger.warning << "Plugin for ." << ext << " not found." << logger.end;

    throw ResourceException("Unsupported shader format: " + filename);
}

/**
 * Shutdown the resource manager.
 * Flushes the resource object lists.
 */
void ResourceManager::Shutdown() {
    textures.clear();
    models.clear();
    shaders.clear();
}

} // NS Resources
} // NS OpenEngine
