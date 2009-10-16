// Font resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_FONT_RESOURCE_H_
#define _I_FONT_RESOURCE_H_

#include <Resources/IResource.h>
#include <Math/Vector.h>

#include <string.h>

namespace OpenEngine {
namespace Resources {

// define font styles (same as sdl_ttf)
#define FONT_STYLE_NORMAL	    0x00
#define FONT_STYLE_BOLD		    0x01
#define FONT_STYLE_ITALIC	    0x02
#define FONT_STYLE_UNDERLINE	0x04

using OpenEngine::Resources::ITextureResourcePtr;
using OpenEngine::Math::Vector;
using std::string;

class IFontResource;
class IFontTextureResource;

/**
 * Model resource smart pointer.
 */
typedef boost::shared_ptr<IFontResource> IFontResourcePtr;
typedef boost::shared_ptr<IFontTextureResource> IFontTextureResourcePtr;

/**
 * Event argument of a font change event.
 *
 * @class FontChangedEventArg IFontResource.h Resources/IFontResource.h
 */
class FontChangedEventArg {
public:
    FontChangedEventArg(IFontResourcePtr font): font(font) {}
    IFontResourcePtr font;
};

/**
 * Font resource interface.
 *
 * The font abstraction handles the loading of various font files and
 * subsequently generates font textures based on the current state of
 * the font (texture rendering is handled by the font).
 *
 * The generated font textures are automatically re-rendered whenever
 * the font changes state and whenever a font texture changes its text.
 *
 * @see IFontTextureResource
 *
 * @class IFontResource IFontResource.h Resources/IFontResource.h
 */
class IFontResource : public IResource<FontChangedEventArg> {
public:
    /**
     * Create a new IFontTextureResource. The texture will be bound to this
     * Font and will be re-rendered by the Font each time either the
     * text of the IFontTexture changes or the Font is updated.
     * 
     * @return a smart pointer to the new IFontTextureResource.
     **/
    virtual IFontTextureResourcePtr CreateFontTexture() = 0;
    virtual void SetPointSize(int ptsize) = 0;
    virtual int GetPointSize() = 0;
    virtual void SetFontStyle(int style) = 0;
    virtual int GetFontStyle() = 0;
    virtual void SetFontColor(Vector<3,float> colr) = 0;
    virtual Vector<3,float> GetFontColor() = 0;
};

} // NS Resources
} // NS OpenEngine

#endif // _I_FONT_RESOURCE_H_
