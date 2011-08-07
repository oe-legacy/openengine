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
#include <Resources/ITexture2D.h>
#include <Utils/Convert.h>
#include <Logging/Logger.h>
#include <cstring>

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
        int mipcount;
        void *negXData, *posXData,
            *negYData, *posYData,
            *negZData, *posZData;
        
        Cubemap(const int s, const ColorFormat f, bool mipmapping = true)
            : size(s), format(f), filtering(TRILINEAR) {
            int arraySize;
            mipcount = 1;
            if (mipmapping){
                int size = s;
                arraySize = size*size;
                while (size > 1){
                    ++mipcount;
                    size /= 2;
                    arraySize += size*size;
                }
            } else
                arraySize = s*s;

            negXData = ITexture::CreateDataArray(arraySize,f);
            posXData = ITexture::CreateDataArray(arraySize,f);
            negYData = ITexture::CreateDataArray(arraySize,f);
            posYData = ITexture::CreateDataArray(arraySize,f);
            negZData = ITexture::CreateDataArray(arraySize,f);
            posZData = ITexture::CreateDataArray(arraySize,f);

            this->id = 0;
        }
        
    public:
        static inline CubemapPtr Create(const int size, const ColorFormat format, bool mipmapping = true) { 
            return CubemapPtr(new Cubemap(size, format, mipmapping));
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
        virtual int Width(const int miplevel = 0) const { 
            const int w = size >> miplevel;
            return w ? w : 1;
        }

        /**
         * Get height in pixels on loaded texture.
         *
         * @return height in pixels.
         */
        virtual int Height(const int miplevel = 0) const { 
            const int h = size >> miplevel;
            return h ? h : 1;
        }

        /**
         * Get color format of the texture.
         *
         * @return ColorFormat representing the way colors are stored
         */
        virtual ColorFormat GetColorFormat() const { return format; }

        /**
         * Sets the texture filtering used for this texture
         */
        virtual void SetFiltering(const Filtering f) { filtering = f; }
        
        /**
         * Returns the texture filtering used for this texture.
         *
         * @return Filtering The filtering used.
         */
        virtual Filtering GetFiltering() const { return filtering; }

        /**
         * Returns true if the cubemap is mipmapped.
         */
        virtual bool IsMipmapped() const { return mipcount > 1;}
        /**
         * Returns the number of mipmaps in this cubemap.
         */
        virtual int MipmapCount() const { return mipcount; }

        /**
         * Returns true if the cubemap's color data is readable. This is always
         * true as long as the data is stored in a colorformat that can be
         * converted to RGBAColor.
         *
         * @return True if the data in the texture can be read.
         */
        virtual bool IsReadable() const { return true; } // @TODO might not always be the case longterm.

        /**
         * Returns the pixel color of the cubemaps face at (x,y). The cubemap
         * must be readable or an exception will be thrown.
         *
         * @return RGBAColor The pixel color.
         */
        virtual Math::RGBAColor GetPixel(const ICubemap::Face face, const int x, const int y, const int miplevel = 0) const {
            const void* data = this->GetRawData(face, miplevel);
            const int index = x + y * Width(miplevel);
            return Math::RGBAColor::FromArray(data, index, format);
        }
        
        /**
         * Sets the pixel color of the cubemaps face at (x,y).
         */
        virtual void SetPixel(const Math::RGBAColor& color, const ICubemap::Face face, const int x, const int y, const int miplevel = 0) {
            void* data = this->GetRawData(face, miplevel);
            const int index = x + y * Width(miplevel);
            color.ToArray(data, index, format);
        }

        /**
         * Set the pixels on the specified face to be the same colors as the 2D texture.
         */
        virtual void SetPixels(const ITexture2DPtr source, const Face face, const int miplevel = 0) {
            if ((int)source->GetWidth() != size || (int)source->GetHeight() != size)
                throw Core::Exception("2D texture, " + Utils::Convert::ToString(source->GetWidth()) + "x" + Utils::Convert::ToString(source->GetHeight()) + 
                                      ", and cubemap dimensions, " + Utils::Convert::ToString(size) + "x" + Utils::Convert::ToString(size) + ", must match.");

            void* faceData = GetRawData(face);
            switch(source->GetColorFormat()) {
            case RGBA:
                if (format == RGBA){
                    memcpy(faceData, source->GetVoidDataPtr(), size * size * 4 * sizeof(unsigned char));
                    break;
                } else
                    throw Core::Exception("Unsupported color format.");
            case RGB:
                if (format == RGBA){
                    unsigned char* data = (unsigned char*)source->GetVoidDataPtr();
                    unsigned char* rawdata = (unsigned char*)faceData;
                    for (int x = 0; x < Width(); ++x)
                        for (int y = 0; y < Height(); ++y){
                            int index = x + y * Width();
                            rawdata[index * 4]   = data[index * 3];
                            rawdata[index * 4+1] = data[index * 3+1];
                            rawdata[index * 4+2] = data[index * 3+2];
                            rawdata[index * 4+3] = 255;
                        }
                    break;
                } else
                    throw Core::Exception("Unsupported color format.");
            case BGR:
                if (format == RGBA){
                    unsigned char* data = (unsigned char*)source->GetVoidDataPtr();
                    unsigned char* rawdata = (unsigned char*)faceData;
                    for (int x = 0; x < Width(); ++x)
                        for (int y = 0; y < Height(); ++y){
                            int index = x + y * Width();
                            rawdata[index * 4]   = data[index * 3+2];
                            rawdata[index * 4+1] = data[index * 3+1];
                            rawdata[index * 4+2] = data[index * 3];
                            rawdata[index * 4+3] = 255;
                        }
                    break;
                } else
                    throw Core::Exception("Unsupported color format.");
            default:
                throw Core::Exception("Unsupported color format.");
            }
        }
        
        /**
         * Returns a pointer to the color data in its raw form.
         */
        virtual void* GetRawData(const Face face, const int miplevel = 0) {
            if (miplevel >= mipcount) return NULL;

            unsigned char *data;
            switch(face){
            case ICubemap::NEGATIVE_X: data = (unsigned char*)negXData; break;
            case ICubemap::POSITIVE_X: data = (unsigned char*)posXData; break;
            case ICubemap::NEGATIVE_Y: data = (unsigned char*)negYData; break;
            case ICubemap::POSITIVE_Y: data = (unsigned char*)posYData; break;
            case ICubemap::NEGATIVE_Z: data = (unsigned char*)negZData; break;
            case ICubemap::POSITIVE_Z: data = (unsigned char*)posZData; break;
            }

            int offset;
            switch(format){
            case RGBA: offset = 4; break;
            default:
                throw Core::Exception("Unsupported color format.");
            }

            for (int mip = 0, s = size; mip < miplevel; ++mip, s /= 2) {
                data += s * s * offset;
            }

            return (void*)data;
        }

        /**
         * Returns a pointer to the color data in its raw form.
         */
        virtual const void* GetRawData(const Face face, const int miplevel = 0) const {
            if (miplevel >= mipcount) return NULL;

            unsigned char *data;
            switch(face){
            case ICubemap::NEGATIVE_X: data = (unsigned char*)negXData; break;
            case ICubemap::POSITIVE_X: data = (unsigned char*)posXData; break;
            case ICubemap::NEGATIVE_Y: data = (unsigned char*)negYData; break;
            case ICubemap::POSITIVE_Y: data = (unsigned char*)posYData; break;
            case ICubemap::NEGATIVE_Z: data = (unsigned char*)negZData; break;
            case ICubemap::POSITIVE_Z: data = (unsigned char*)posZData; break;
            }

            int offset;
            switch(format){
            case RGBA: offset = 4; break;
            default:
                throw Core::Exception("Unsupported color format.");
            }

            for (int mip = 0, s = size; mip < miplevel; ++mip, s /= 2) {
                data += s * s * offset;
            }

            return (void*)data;
        }
    };
    
}
}

#endif
