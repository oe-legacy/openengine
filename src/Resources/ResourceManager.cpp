// Resource Manager.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <list>

#include <Resources/ResourceManager.h>
#include <Resources/Exceptions.h>
#include <Resources/ITextureResource.h>
#include <Resources/IModelResource.h>
#include <Resources/IShaderResource.h>
#include <Resources/File.h>
#include <Logging/Logger.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Utils::Convert;

// initialization of static members
string ResourceManager::path = "";
map<string, ITextureResourcePtr> ResourceManager::textures = map<string, ITextureResourcePtr>();
map<string, IModelResourcePtr>   ResourceManager::models   = map<string, IModelResourcePtr>();
map<string, IShaderResourcePtr>  ResourceManager::shaders  = map<string, IShaderResourcePtr>();

map<string, ITextureResourcePlugin*> ResourceManager::texturePlugins = map<string, ITextureResourcePlugin*>();
map<string, IModelResourcePlugin*>   ResourceManager::modelPlugins   = map<string, IModelResourcePlugin*>();
map<string, IShaderResourcePlugin*>  ResourceManager::shaderPlugins  = map<string, IShaderResourcePlugin*>();

/**
 * Set the resource root directory.
 *
 * @param str New resource directory
 * @return Old resource directory path
 */
string ResourceManager::SetPath(string str) {
    string old(path);
    path = str;
    return old;
}

/**
 * Get the current path to the resource root directory
 *
 * @return Resource directory path
 */
string ResourceManager::GetPath() {
    return path;
}

/**
 * Add texture resource plug-in.
 *
 * @param plugin Texture plug-in
 */
void ResourceManager::AddTexturePlugin(ITextureResourcePlugin* plugin) {
	for(ExtListItr itr = plugin->begin(); itr != plugin->end(); itr++) {
		texturePlugins[(*itr)] = plugin;
	}
}

/**
 * Add model resource plug-in.
 *
 * @param plugin Model plug-in
 */
void ResourceManager::AddModelPlugin(IModelResourcePlugin* plugin) {
	for(ExtListItr itr = plugin->begin(); itr != plugin->end(); itr++) {
		modelPlugins[(*itr)] = plugin;
	}
}

/**
 * Add shader resource plug-in.
 *
 * @param plugin Shader plug-in
 */
void ResourceManager::AddShaderPlugin(IShaderResourcePlugin* plugin) {
	for(ExtListItr itr = plugin->begin(); itr != plugin->end(); itr++) {
		shaderPlugins[(*itr)] = plugin;
	}
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
    map<string,ITextureResourcePlugin*>::iterator plugin = texturePlugins.find(ext);

    // load the resource
	if (plugin != texturePlugins.end()) {
		ITextureResourcePtr texture = plugin->second->CreateResource(path+filename);
        textures[filename] = texture;
        return texture;
    }

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
    map<string,IModelResourcePlugin*>::iterator plugin = modelPlugins.find(ext);

    // load the resource
	if (plugin != modelPlugins.end()) {
		IModelResourcePtr model = plugin->second->CreateResource(path+filename);
        models[filename] = model;
        return model;
    } 
    else
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
    map<string,IShaderResourcePlugin*>::iterator plugin = shaderPlugins.find(ext);

    // load the resource
	if (plugin != shaderPlugins.end()) {
		IShaderResourcePtr shader = plugin->second->CreateResource(path+filename);
        shaders[filename] = shader;
        return shader;
    }

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
