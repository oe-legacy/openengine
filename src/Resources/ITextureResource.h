// Texture resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_TEXTURE_RESOURCE_H_
#define _I_TEXTURE_RESOURCE_H_

#include <Resources/IResource.h>

namespace OpenEngine {
namespace Resources {

/**
 * Texture resource interface.
 *
 * @class ITextureResource ITextureResource.h Resources/ITextureResource.h
 */
class ITextureResource : public IResource {
public:

	/**
     * Get texture id.
     *
     * @return Texture id.
     */
    virtual int GetID() = 0;
	
    /**
     * Set texture id.
     *
     * @param id Texture id.
     */
    virtual void SetID(int id) = 0;

    /**
     * Get width in pixels on loaded texture.
     *
     * @return width in pixels.
     */
	virtual int GetWidth() = 0;

    /**
     * Get height in pixels on loaded texture.
     *
     * @return height in pixels.
     */
	virtual int GetHeight() = 0;

    /**
     * Get color depth on loaded texture.
     *
     * @return Color depth in pixels.
     */
    virtual int GetDepth() = 0;

    /**
     * Get pointer to loaded texture.
     *
     * @return Char pointer to loaded data.
     */
	virtual unsigned char* GetData() = 0;
};

/**
 * Texture resource smart pointer.
 */
typedef boost::shared_ptr<ITextureResource> ITextureResourcePtr;

/**
 * Texture resources plug-in.
 *
 * @class ITextureResourcePlugin ITextureResource.h Resources/ITextureResource.h
 */
class ITextureResourcePlugin : public virtual IResourcePlugin {
public:
    /**
     * Create a new texture resource from a file.
     *
     * @param file Texture resource file.
     * @return Texture resource pointer.
     */
    virtual ITextureResourcePtr CreateResource(string file) = 0;
};

} // NS Resources
} // NS OpenEngine

#endif // _I_TEXTURE_RESOURCE_H_
