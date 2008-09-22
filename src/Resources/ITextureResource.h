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

class ITextureResource;

/**
 * Texture resource smart pointer.
 */
typedef boost::shared_ptr<ITextureResource> ITextureResourcePtr;

class TextureChangedEventArg {
public:
 TextureChangedEventArg(ITextureResourcePtr resource) : resource(resource) {}
    ITextureResourcePtr resource;
};

enum ColorFormat { RGBA, BGRA, RGB, BGR, LUMINANCE };

/**
 * Texture resource interface.
 *
 * @class ITextureResource ITextureResource.h Resources/ITextureResource.h
 */
class ITextureResource : public IResource<TextureChangedEventArg> {
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
	virtual unsigned int GetWidth() = 0;

    /**
     * Get height in pixels on loaded texture.
     *
     * @return height in pixels.
     */
	virtual unsigned int GetHeight() = 0;

    /**
     * Get color depth on loaded texture.
     *
     * @return Color depth in pixels.
     */
    virtual unsigned int GetDepth() = 0;

    /**
     * Get pointer to loaded texture.
     *
     * @return Char pointer to loaded data.
     */
    virtual unsigned char* GetData() = 0;

    /**
     * Get color format of the texture.
     *
     * @return ColorFormat representing the way colors are stored
     */
    virtual ColorFormat GetColorFormat() = 0;

    virtual void Reverse() {
        unsigned int height = this->GetHeight();
        unsigned int depth = this->GetDepth();
        unsigned int width = this->GetWidth();
        unsigned char* data = this->GetData();
        unsigned char temp;
        int numberOfCharsPerColor = (depth/8);
        long size = width * height * numberOfCharsPerColor;
        for (int i=0,j=size-numberOfCharsPerColor; i<j;
             i+=numberOfCharsPerColor, j-=numberOfCharsPerColor) {
            for (int index=0; index<numberOfCharsPerColor; index++) {
                temp = data[i+index];
		data[i+index] = data[j+index];
		data[j+index] = temp;
            }
        }
    }

    virtual void ReverseVertecally() {
        //@todo make an optimized version that does this in one loop
        Reverse();
        ReverseHorizontally();
    }

    virtual void ReverseHorizontally() {
        unsigned int height = this->GetHeight();
        unsigned int depth = this->GetDepth();
        unsigned int width = this->GetWidth();
        unsigned char* data = this->GetData();
        unsigned char temp;
        int numberOfCharsPerColor = (depth/8);
        long size = width * height * numberOfCharsPerColor;
        for (int lineNumber=0; lineNumber<size;
             lineNumber+=width*numberOfCharsPerColor) {
            for (int i=0, j=(width-1)*numberOfCharsPerColor; i < j;
                 i+=numberOfCharsPerColor, j-=numberOfCharsPerColor) {
                for(int index=0; index<numberOfCharsPerColor;index++) {
                    temp = data[lineNumber+i+index];
                    data[lineNumber+i+index] = data[lineNumber+j+index];
                    data[lineNumber+j+index] = temp;
                }
            }
        }
    }

    //! Serialization support
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ;
    }
};

} // NS Resources
} // NS OpenEngine

#endif // _I_TEXTURE_RESOURCE_H_
