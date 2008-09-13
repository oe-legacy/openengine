// Shader resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_SHADER_RESOURCE_H_
#define _I_SHADER_RESOURCE_H_

#include <Resources/IResource.h>
#include <Resources/ITextureResource.h>
#include <Math/Vector.h>
#include <string>
#include <vector>
#include <map>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Math::Vector;
using std::string;
using std::vector;
using std::map;

class IShaderResource;

/**
 * Shader resource smart pointer.
 */
typedef boost::shared_ptr<IShaderResource> IShaderResourcePtr;

class ShaderChangedEventArg {
public:
    ShaderChangedEventArg() {}
    IShaderResourcePtr resource;
};

/**
 * Map of texture names and resources.
 */
typedef map<string,ITextureResourcePtr> ShaderTextureMap;

/**
 * Shader resource interface.
 *
 * @class IShaderResource IShaderResource.h Resources/IShaderResource.h
 */
class IShaderResource : public IResource<ShaderChangedEventArg> {
protected:

    /**
     * Set a shader attribute.
     *
     * @param name Attribute name.
     * @param value Attribute vector value.
     */
    virtual void SetAttribute(string name, vector<float> value)=0;

public:

    ShaderTextureMap textures;  //!< shader textures.

    /**
     * Apply the shader.
     * Corresponds to binding a texture.
     */
    virtual void ApplyShader()=0;

    /**
     * Release the shader.
     * Corresponds to unbind a texture.
     */
    virtual void ReleaseShader()=0;

    /**
     * Binds an attribute by id.
     *
     * @param id Id to bind.
     * @param name Name to bind it to.
     */
    virtual void BindAttribute(int id, string name)=0;

    /**
     * Bind a single vertex attribute.
     *
     * @param id Attribute id to bind.
     * @param vec Vector value to bind to.
     */
    virtual void VertexAttribute(int id, Vector<3,float> vec)=0;

    /**
     * Get the id an attribute is bound to.
     *
     * @param name Attribute name.
     * @return id Bound id.
     */
    virtual int GetAttributeID(const string name) = 0;

};

} // NS Resources
} // NS OpenEngine

#endif 
