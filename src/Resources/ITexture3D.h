// Texture 3D resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_TEXTURE_3D_RESOURCE_H_
#define _I_TEXTURE_3D_RESOURCE_H_

#include <Resources/IResource.h>
#include <Resources/ITexture.h>

namespace OpenEngine {
    namespace Resources {

        class Texture3DChangedEventArg;

        /**
         * Texture resource interface.
         *
         * @class ITexture3D ITexture3D.h Resources/ITexture3D.h
         */
        class ITexture3D : public IResource<Texture3DChangedEventArg> 
                         , public ITexture {
        public:
            /**
             * Tells OpenEngine how the 3d texture will be used. Either as
             * a standard 3d texture or as an array of 2D textures.
             */
            enum TextureUseCase {TEXTURE3D = 0x806F, 
                                 TEXTURE2D_ARRAY = 0x8C1A};
            

        protected:
            unsigned int width, height, depth;
            TextureUseCase useCase;

        public:
            ITexture3D()
                : ITexture() {
                width = height = depth = 0;
                useCase = TEXTURE3D;
            }
    
            /**
             * Get width in pixels on loaded texture.
             *
             * @return width in pixels.
             */
            inline unsigned int GetWidth() const { return width; }

            /**
             * Get height in pixels on loaded texture.
             *
             * @return height in pixels.
             */
            inline unsigned int GetHeight() const { return height; }

            /**
             * Get depth in pixels on loaded texture.
             *
             * @return height in pixels.
             */
            inline unsigned int GetDepth() const { return depth; }

            /**
             * Get the specified use case.
             */
            inline TextureUseCase GetUseCase() const { return useCase; }

            /**
             * Sets a use case for the 3d texture. Will only have an
             * effect if the texture hasn't been bound.
             */
            inline void SetUseCase(TextureUseCase u) {
                if (id == 0)
                    useCase = u;
            }
        };

        /**
         * Void smart pointer
         */
        typedef boost::shared_ptr<void> VoidPtr;
        typedef boost::shared_ptr<ITexture3D> ITexture3DPtr;
        
        /**
         * Texture change event argument.
         * Contains a pointer to the texture that changed.
         *
         * @class TextureChangedEventArg ITexture3D.h Resource/ITexture3D.h
         */
        class Texture3DChangedEventArg {
        public:
            ITexture3DPtr resource;
            unsigned int xOffset, yOffset, zOffset, width, height, depth;
            VoidPtr dataRect;
            Texture3DChangedEventArg(ITexture3DPtr resource) : resource(resource) {
                xOffset = yOffset = zOffset = 0;
                width = resource->GetWidth();
                height = resource->GetHeight();
                depth = resource->GetDepth();
                dataRect = VoidPtr();
            }
            Texture3DChangedEventArg(ITexture3DPtr resource, unsigned int x, unsigned int y, unsigned int z, unsigned int w, unsigned int h, unsigned int d, VoidPtr dr = VoidPtr()) 
                : resource(resource), xOffset(x), yOffset(y), zOffset(z), width(w), height(h), depth(d), dataRect(dr) {}
        };

    } // NS Resources
} // NS OpenEngine

#endif // _I_TEXTURE_RESOURCE_H_
