// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#ifndef _OE_SERIALIZATION_RESOURCE_H_
#define _OE_SERIALIZATION_RESOURCE_H_

#include <string>
#include <Resources/IModelResource.h>
#include <Resources/IResourcePlugin.h>
#include <Scene/ISceneNode.h>
#include <Scene/AnimationNode.h>

namespace OpenEngine {
namespace Resources {

/**
 * Short description.
 *
 * @class SerializationResource SerializationResource.h ils/SerializationResource.h
 */
class SerializationResource : public IModelResource {
private:
    std::string file;
    Scene::ISceneNode* node;
    Scene::AnimationNode* animations;
public:
    SerializationResource(std::string file);
    Scene::ISceneNode* GetSceneNode();
    Scene::ISceneNode* GetMeshes();
    Scene::AnimationNode* GetAnimations();


    void Load();
    void Unload();
};
    
class SerializationPlugin : public IResourcePlugin<IModelResource> {
public:
    SerializationPlugin();
    IModelResourcePtr CreateResource(std::string file);
};

} // NS Resources
} // NS OpenEngine

#endif // _OE_SERIALIZATION_RESOURCE_H_
