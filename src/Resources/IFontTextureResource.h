// Texture that will use a font to render a string.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This extension is based on the sdlimage extension and uses sdl_ttf
// to handle font loading and rendering. 
//
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_FONT_TEXTURE_RESOURCE_H_
#define _I_FONT_TEXTURE_RESOURCE_H_

#include <Resources/ITextureResource.h>
#include <Math/Vector.h>
#include <string>

namespace OpenEngine {
namespace Resources {

using std::string;
using Math::Vector;

class IFontTextureResource;
typedef boost::shared_ptr<IFontTextureResource> IFontTextureResourcePtr;

/**
 * Font Texture resource.
 * 
 * A texture that updates its pixels based on a text string. The font
 * texture is tightly coupled with the IFontResource abstraction and
 * should only be instantiated through the CreateFontTexture method of
 * the IFontResource class.
 *
 * @see IFontResource
 *
 * @class IFontTextureResource IFontTextureResource.h Resources/IFontTextureResource.h
 */
class IFontTextureResource : public ITextureResource {
public:
    IFontTextureResource() : ITextureResource() {}
    virtual ~IFontTextureResource() {}
    // /**
    //  * Set the clear color of the font texture.
    //  *
    //  * @param color the clear color in an RGBA float vector.
    //  **/
    // virtual void SetClearColor(Vector<4,float> color) = 0;

    // /**
    //  * Get the current clear color of the font texture.
    //  *
    //  * @return the current clear color in an RGBA float vector.
    //  **/
    // virtual Vector<4,float> GetClearColor() = 0;

    /**
     * Clear the font texture to a specific color.
     *
     * @param color the clear color given in an RGBA float vector.
     **/
    virtual void Clear(Vector<4,float> color) = 0;
};

} //NS Resources
} //NS OpenEngine

#endif // _FONT_TEXTURE_RESOURCE_H_
