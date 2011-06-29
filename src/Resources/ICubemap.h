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
    class ICubemapChanged;
    class ICubemapDestroyed;

    /**
     * Cubemap smart pointer.
     */
    typedef boost::shared_ptr<ICubemap> ICubemapPtr;

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
        enum Face {NEGATIVE_X, POSITIVE_X, 
                   NEGATIVE_Y, POSITIVE_Y, 
                   NEGATIVE_Z, POSITIVE_Z};

        /**
         * Get width in pixels on loaded texture.
         *
         * @return width in pixels.
         */
        virtual const int Width() const = 0;

        /**
         * Get height in pixels on loaded texture.
         *
         * @return height in pixels.
         */
        virtual const int Height() const = 0;

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
         * Returns a pointer to the color data in its raw form. The cubemap must
         * be readable or an exception will be thrown.
         */
        virtual const void* GetRawData(const Face face) const = 0;
    };
    

}
}

#endif
