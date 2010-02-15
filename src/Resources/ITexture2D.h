// Texture 2D resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_TEXTURE_2D_RESOURCE_H_
#define _I_TEXTURE_2D_RESOURCE_H_

#include <Resources/IResource.h>
#include <Resources/ITexture.h>

namespace OpenEngine {
    namespace Resources {

        class Texture2DChangedEventArg;

        /**
         * Texture resource interface.
         *
         * @class ITexture2D ITexture2D.h Resources/ITexture2D.h
         */
        class ITexture2D : public IResource<Texture2DChangedEventArg> 
                               , public ITexture {
        protected:
            unsigned int width, height;

        public:
            ITexture2D()
                : ITexture() {
                width = height = 0;
            }
    
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

            virtual void Reverse() = 0;

            virtual void ReverseVertecally() = 0;

            virtual void ReverseHorizontally() = 0;

            //! Serialization support
            template<class Archive>
            void serialize(Archive& ar, const unsigned int version) {
                ;
            }
        };

        // Typedef for backwards compatibility
        //typedef Texture2DChangedEventArg TextureChangedEventArg;
        //typedef ITexture2D ITextureResource;
        //typedef boost::shared_ptr<ITexture2D> ITextureResourcePtr;

        /**
         * smart pointers
         */
        typedef boost::shared_ptr<void> VoidPtr;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;

        /**
         * Texture change event argument.
         * Contains a pointer to the texture that changed.
         *
         * @class TextureChangedEventArg ITextureResource.h Resource/ITextureResource.h
         */
        class Texture2DChangedEventArg {
        public:
            ITexture2DPtr resource;
            unsigned int xOffset, yOffset, width, height;
            VoidPtr dataRect;
            Texture2DChangedEventArg(ITexture2DPtr resource) : resource(resource) {
                xOffset = yOffset = 0;
                width = resource->GetWidth();
                height = resource->GetHeight();
                dataRect = VoidPtr();
            }
            Texture2DChangedEventArg(ITexture2DPtr resource, unsigned int x, unsigned int y, unsigned int w, unsigned int h, VoidPtr dr = VoidPtr()) 
                : resource(resource), xOffset(x), yOffset(y), width(w), height(h), dataRect(dr) {}
        };

    } // NS Resources
} // NS OpenEngine

#endif // _I_TEXTURE_RESOURCE_H_
