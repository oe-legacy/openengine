// Model resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_MODEL_RESOURCE_H_
#define _I_MODEL_RESOURCE_H_

#include <Resources/IResource.h>

// forward declaration
namespace OpenEngine { namespace Scene { class ISceneNode; } }
namespace OpenEngine { namespace Scene { class AnimationNode; } }

namespace OpenEngine {
namespace Resources {

using OpenEngine::Scene::ISceneNode;
using OpenEngine::Scene::AnimationNode;

class IModelResource;

/**
 * Model resource smart pointer.
 */
typedef boost::shared_ptr<IModelResource> IModelResourcePtr;

/**
 * Event argument of a model change event.
 *
 * @class ModelChangedEventArg IModelResource.h Resource/IModelResource.h
 */
class ModelChangedEventArg {
public:
    ModelChangedEventArg() {}
    IModelResourcePtr resource;
};

/**
 * Model resource interface.
 *
 * @class IModelResource IModelResource.h Resources/IModelResource.h
 */
class IModelResource : public IResource<ModelChangedEventArg> {
public:

    /**
     * Get a scene graph containing a hierarchical model.
     * This could be a graph containing transformation nodes and
     * geometry nodes
     */
    virtual ISceneNode* GetSceneNode() = 0;

    virtual ISceneNode* GetMeshes() = 0;
    virtual AnimationNode* GetAnimations() = 0;
    
};

} // NS Resources
} // NS OpenEngine

#endif // _I_MODEL_RESOURCE_H_
