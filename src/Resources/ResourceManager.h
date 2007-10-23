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

#include <Resources/ITextureResource.h>
#include <Resources/IModelResource.h>
#include <Resources/IShaderResource.h>
#include <string>
#include <map>
#include <iostream>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Resource manager.
 *
 * @class ResourceManager ResourceManager.h Resources/ResourceManager.h
 */
class ResourceManager {
private:
    static map<string, ITextureResourcePtr> textures;
    static map<string, IModelResourcePtr>   models;
    static map<string, IShaderResourcePtr>  shaders;
    static map<string, ITextureResourcePlugin*> texturePlugins;
    static map<string, IModelResourcePlugin*>   modelPlugins;
    static map<string, IShaderResourcePlugin*>  shaderPlugins;
    static string path;
public:
    static string SetPath(string);
    static string GetPath();
    static void AddTexturePlugin(ITextureResourcePlugin* plugin);
    static void AddModelPlugin(IModelResourcePlugin* plugin);
    static void AddShaderPlugin(IShaderResourcePlugin* plugin);
	static ITextureResourcePtr CreateTexture(const string filename);
	static IModelResourcePtr   CreateModel(const string filename);
    static IShaderResourcePtr  CreateShader(const string filename);
	static void Shutdown();
};

} // NS Resources
} // NS OpenEngine

#endif // _RESOURCE_MANAGER_H_
