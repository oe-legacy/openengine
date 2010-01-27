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

class TextureChangedEventArg;

enum ColorFormat { RGBA, BGRA, RGB, BGR, LUMINANCE };

/**
 * Texture resource interface.
 *
 * @class ITextureResource ITextureResource.h Resources/ITextureResource.h
 */
class ITextureResource : public IResource<TextureChangedEventArg> {
protected:
    unsigned int id;
    unsigned int width, height;
    unsigned char channels;
    unsigned char* data;
    ColorFormat format;
public:
    ITextureResource() {
        id = width = height = channels = 0;
        data = NULL;
    }
    
    virtual ~ITextureResource() {
        if (data)
            delete [] data;
    }

	/**
     * Get texture id.
     *
     * @return Texture id.
     */
    inline unsigned int GetID() { return id; }
	
    /**
     * Set texture id.
     *
     * @param id Texture id.
     */
    inline void SetID(int id) { this->id = id; }

    /**
     * Get width in pixels on loaded texture.
     *
     * @return width in pixels.
     */
	inline unsigned int GetWidth() { return width; }

    /**
     * Get height in pixels on loaded texture.
     *
     * @return height in pixels.
     */
	inline unsigned int GetHeight() { return height; }

    /**
     * Get number of channels in the texture.
     *
     * @return Channels the number of channels.
     */
    inline unsigned char GetChannels() const {
        return channels;
    }

    /**
     * Get pointer to loaded texture.
     *
     * @return Char pointer to loaded data.
     */
    inline unsigned char* GetData() { return data; }

    /**
     * Unloads the texture data, but leaves the other texture info
     * intact.
     */
    virtual void Unload() {
        if (data) {
            delete[] data;
            data = NULL;
        }
    }
        
        
    /**
     * Get color format of the texture.
     *
     * @return ColorFormat representing the way colors are stored
     */
    inline ColorFormat GetColorFormat() { return format; }

    virtual void Reverse() {
        unsigned int height = this->GetHeight();
        unsigned int width = this->GetWidth();
        unsigned char* data = this->GetData();
        unsigned char temp;
        long size = width * height * channels;
        for (int i = 0, j = size-channels; i < j;
             i += channels, j -= channels) {
            for (int index = 0; index < channels; index++) {
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
        unsigned int width = this->GetWidth();
        unsigned char* data = this->GetData();
        unsigned char temp;
        long size = width * height * channels;
        for (int lineNumber=0; lineNumber<size;
             lineNumber+=width*channels) {
            for (int i=0, j=(width-1)*channels; i < j;
                 i+=channels, j-=channels) {
                for(int index=0; index<channels;index++) {
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

/**
 * Texture resource smart pointer.
 */
typedef boost::shared_ptr<ITextureResource> ITextureResourcePtr;

/**
 * Texture change event argument.
 * Contains a pointer to the texture that changed.
 *
 * @class TextureChangedEventArg ITextureResource.h Resource/ITextureResource.h
 */
class TextureChangedEventArg {
public:
    ITextureResource* resource;
    unsigned int xOffset, yOffset, width, height;
    TextureChangedEventArg(ITextureResource* resource) : resource(resource) {
        xOffset = yOffset = 0;
        width = resource->GetWidth();
        height = resource->GetHeight();
    }
    TextureChangedEventArg(ITextureResource* resource, unsigned int x, unsigned int y, unsigned int w, unsigned int h) 
        : resource(resource), xOffset(x), yOffset(y), width(w), height(h) {}
};

} // NS Resources
} // NS OpenEngine

#endif // _I_TEXTURE_RESOURCE_H_
