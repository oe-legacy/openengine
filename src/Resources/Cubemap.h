// Cubemap texture.
// -------------------------------------------------------------------
// Copyright (C) 2011 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CUBEMAP_RESOURCE_H_
#define _CUBEMAP_RESOURCE_H_

#include <Resources/ICubemap.h>

namespace OpenEngine {
namespace Resources {

    /**
     * Forward declarations.
     */
    class Cubemap;

    /**
     * Cubemap smart pointer.
     */
    typedef boost::shared_ptr<Cubemap> CubemapPtr;

    /**
     * Basic cubemap implementation.
     *
     * @class Cubemap Cubemap.h Resources/Cubemap.h
     */
    class Cubemap : public virtual ICubemap {
    protected:
        int size;
        ColorFormat format;
        Filtering filtering;
        void *negXData, *posXData,
            *negYData, *posYData,
            *negZData, *posZData;
        
        Cubemap(const int s, const ColorFormat f)
            : size(s), format(f), filtering(TRILINEAR) {
            negXData = ITexture::CreateDataArray(s*s,f);
            posXData = ITexture::CreateDataArray(s*s,f);
            negYData = ITexture::CreateDataArray(s*s,f);
            posYData = ITexture::CreateDataArray(s*s,f);
            negZData = ITexture::CreateDataArray(s*s,f);
            posZData = ITexture::CreateDataArray(s*s,f);

            this->id = 0;
        }
        
    public:
        static inline CubemapPtr Create(const int size, const ColorFormat format) { 
            return CubemapPtr(new Cubemap(size, format));
        }

        ~Cubemap() {
            ITexture::DeleteDataArray(negXData, format); ITexture::DeleteDataArray(posXData, format);
            ITexture::DeleteDataArray(negYData, format); ITexture::DeleteDataArray(posYData, format);
            ITexture::DeleteDataArray(negZData, format); ITexture::DeleteDataArray(posZData, format);
        }

        /**
         * Get width in pixels on loaded texture.
         *
         * @return width in pixels.
         */
        virtual const int Width() const { return size; }

        /**
         * Get height in pixels on loaded texture.
         *
         * @return height in pixels.
         */
        virtual const int Height() const { return size; }

        /**
         * Get color format of the texture.
         *
         * @return ColorFormat representing the way colors are stored
         */
        virtual const ColorFormat GetColorFormat() const { return format; }

        /**
         * Sets the texture filtering used for this texture
         */
        virtual void SetFiltering(const Filtering f) { filtering = f; }
        
        /**
         * Returns the texture filtering used for this texture.
         *
         * @return Filtering The filtering used.
         */
        virtual const Filtering GetFiltering() const { return filtering; }

        /**
         * Returns true if the cubemap's color data is readable. This is always
         * true as long as the data is stored in a colorformat that can be
         * converted to RGBAColor.
         *
         * @return True if the data in the texture can be read.
         */
        virtual const bool IsReadable() const { return true; } // @TODO might not always be the case longterm.

        /**
         * Returns the pixel color of the cubemaps face at (x,y). The cubemap
         * must be readable or an exception will be thrown.
         *
         * @return RGBAColor The pixel color.
         */
        virtual Math::RGBAColor GetPixel(const ICubemap::Face face, const int x, const int y, const int miplevel = 0) const {
            const int index = x + y * size;
            switch(face){
            case ICubemap::NEGATIVE_X: 
                return Math::RGBAColor::FromArray(negXData, index, format);
            case ICubemap::POSITIVE_X: 
                return Math::RGBAColor::FromArray(posXData, index, format);
            case ICubemap::NEGATIVE_Y: 
                return Math::RGBAColor::FromArray(negYData, index, format);
            case ICubemap::POSITIVE_Y: 
                return Math::RGBAColor::FromArray(posYData, index, format);
            case ICubemap::NEGATIVE_Z: 
                return Math::RGBAColor::FromArray(negZData, index, format);
            case ICubemap::POSITIVE_Z: 
                return Math::RGBAColor::FromArray(posZData, index, format);
            }
            return Math::RGBAColor();
        }
        
        /**
         * Sets the pixel color of the cubemaps face at (x,y).
         */
        virtual void SetPixel(const Math::RGBAColor& color, const ICubemap::Face face, const int x, const int y, const int miplevel = 0) {
            const int index = x + y * size;
            switch(face){
            case ICubemap::NEGATIVE_X: 
                color.ToArray(negXData, index, format);
                break;
            case ICubemap::POSITIVE_X: 
                color.ToArray(posXData, index, format);
                break;
            case ICubemap::NEGATIVE_Y: 
                color.ToArray(negYData, index, format);
                break;
            case ICubemap::POSITIVE_Y: 
                color.ToArray(posYData, index, format);
                break;
            case ICubemap::NEGATIVE_Z: 
                color.ToArray(negZData, index, format);
                break;
            case ICubemap::POSITIVE_Z: 
                color.ToArray(posZData, index, format);
                break;
            }
        }
        
        /**
         * Returns a pointer to the color data in its raw form.
         */
        virtual const void* GetRawData(const Face face) const {
            switch(face){
            case ICubemap::NEGATIVE_X:
                return negXData;
            case ICubemap::POSITIVE_X:
                return posXData;
            case ICubemap::NEGATIVE_Y:
                return negYData;
            case ICubemap::POSITIVE_Y:
                return posYData;
            case ICubemap::NEGATIVE_Z:
                return negZData;
            case ICubemap::POSITIVE_Z:
                return posZData;
            }
            return NULL;
        }
    };
    
}
}

#endif
