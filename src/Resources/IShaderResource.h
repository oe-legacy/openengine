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
#include <Math/Vector.h>
#include <string>
#include <vector>
#include <map>

namespace OpenEngine {
namespace Resources {

// Forward declerations
class ITexture2D;
typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;

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
typedef map<string,ITexture2DPtr> ShaderTextureMap;
typedef vector<ITexture2DPtr> TextureList;

/**
 * Shader resource interface.
 *
 * @class IShaderResource IShaderResource.h Resources/IShaderResource.h
 */
class IShaderResource : public IResource<ShaderChangedEventArg> {
protected:

    vector<string> texNames;
    TextureList texs;

public:

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
     * Set a shader uniform.
     *
     * @param name Uniform name.
     * @param value Uniform vector value.
     */
    virtual void SetUniform(string name, int arg) = 0;
    virtual void SetUniform(string name, float value)=0;
    virtual void SetUniform(string name, Vector<2, float> value)=0;
    virtual void SetUniform(string name, Vector<3, float> value)=0;
    virtual void SetUniform(string name, Vector<4, float> value)=0;

    /**
     * Binds a texture to variable with the name in the shader.
     * @param name Name to bind to.
     * @param tex Texture to bind.
     */
    virtual void SetTexture(string name, ITexture2DPtr tex) = 0;

    /**
     * Get the Textures associated with the shader.
     * @return List of textures.
     */
    virtual TextureList GetTextures() = 0;

    /**
     * Set a shader attribute.
     *
     * @param name Attribute name.
     * @param value Attribute vector value.
     */
    virtual void SetAttribute(string name, Vector<3, float> value)=0;

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
