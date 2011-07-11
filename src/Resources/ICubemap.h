// Cubemap texture interface.
// -------------------------------------------------------------------
// Copyright (C) 2011 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_CUBEMAP_RESOURCE_H_
#define _I_CUBEMAP_RESOURCE_H_

#include <Resources/ITexture.h>
#include <Math/RGBAColor.h>

namespace OpenEngine {
namespace Resources {

    /**
     * Forward declarations.
     */
    class ICubemap;
    typedef boost::shared_ptr<ICubemap> ICubemapPtr;
    class ICubemapChanged;
    class ICubemapDestroyed;

    class ITexture2D;
    typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;

    /**
     * Cubemap texture interface.
     *
     * @todo The cubemap needs events that notifies on data changed, filtering
     * changed and destruction, in order for a given context to listen to these
     * and update accodingly.
     *
     * @class ICubemap ICubemap.h Resources/ICubemap.h
     */
    class ICubemap {
    public:

        /**
         * An enumeration of the cubemap faces.
         */
        enum Face {POSITIVE_X = 0x8515,
                   NEGATIVE_X = 0x8516,
                   POSITIVE_Y = 0x8517,
                   NEGATIVE_Y = 0x8518,
                   POSITIVE_Z = 0x8519,
                   NEGATIVE_Z = 0x851A};
                   
        /** SHOULD BE MOVED TO CONTEXT!! **/
        unsigned int id;
        /**
         * Get texture id.
         *
         * @return Texture id.
         */
        inline unsigned int GetID() const { return id; }

        /**
         * Set texture id.
         *
         * @param id Texture id.
         */
        virtual void SetID(int id) { this->id = id; }


        /**
         * Get width in pixels on loaded texture.
         *
         * @return width in pixels.
         */
        virtual const int Width(const int miplevel = 0) const = 0;

        /**
         * Get height in pixels on loaded texture.
         *
         * @return height in pixels.
         */
        virtual const int Height(const int miplevel = 0) const = 0;

        /**
         * Get color format of the texture.
         *
         * @return ColorFormat representing the way colors are stored
         */
        virtual const ColorFormat GetColorFormat() const = 0;

        /**
         * Sets the texture filtering used for this texture
         */
        virtual void SetFiltering(const Filtering f) = 0;
        
        /**
         * Returns the texture filtering used for this texture.
         *
         * @return Filtering The filtering used.
         */
        virtual const Filtering GetFiltering() const = 0;

        /**
         * Returns true if the cubemap is mipmapped.
         */
        virtual const bool IsMipmapped() const = 0;
        /**
         * Returns the number of mipmaps in this cubemap.
         */
        virtual const int MipmapCount() const = 0;

        /**
         * Returns true if the cubemap's color data is readable. This is not the
         * case if the cubemap is a render cubemap, where the data is stored in
         * a device's memory and requires a context to be accessed.
         *
         * @return True if the data in the texture can be read.
         */
        virtual const bool IsReadable() const = 0;

        /**
         * Returns the pixel color of the cubemaps face at (x,y). The cubemap
         * must be readable or an exception will be thrown.
         *
         * @return RGBAColor The pixel color.
         */
        virtual Math::RGBAColor GetPixel(const Face face, const int x, const int y, const int miplevel = 0) const = 0;
        
        /**
         * Sets the pixel color of the cubemaps face at (x,y).
         */
        virtual void SetPixel(const Math::RGBAColor& color, const Face face, const int x, const int y, const int miplevel = 0) = 0;

        /**
         * Set the pixels on the specified face to be the same colors as the 2D texture.
         */
        virtual void SetPixels(const ITexture2DPtr data, const Face face, const int miplevel = 0) = 0;

        /**
         * Returns a pointer to the color data in its raw form. The cubemap must
         * be readable or an exception will be thrown.
         */
        virtual void* GetRawData(const Face face, const int miplevel = 0) = 0;
        virtual const void* GetRawData(const Face face, const int miplevel = 0) const = 0;
    };
    

}
}

#endif
