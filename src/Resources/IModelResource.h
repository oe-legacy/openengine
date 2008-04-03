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
namespace OpenEngine { namespace Geometry { class FaceSet; } }

namespace OpenEngine {
namespace Resources {

using OpenEngine::Geometry::FaceSet;

/**
 * Model resource interface.
 *
 * @class IModelResource IModelResource.h Resources/IModelResource.h
 */
class IModelResource : public IResource {
public:
    /**
     * Get the face set of the model.
     */
    virtual FaceSet* GetFaceSet() = 0;
};

/**
 * Model resource smart pointer.
 */
typedef boost::shared_ptr<IModelResource> IModelResourcePtr;

} // NS Resources
} // NS OpenEngine

#endif // _I_MODEL_RESOURCE_H_
