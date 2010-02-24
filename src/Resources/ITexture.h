// Texture resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_TEXTURE_H_
#define _I_TEXTURE_H_

#include <Resources/Types/ResourceTypes.h>

using namespace OpenEngine::Resources::Types;

namespace OpenEngine {
    namespace Resources {
        
        /**
         * Color Format enumeration.
         */
        enum ColorFormat { ALPHA, ALPHA_COMPRESSED, 
                           LUMINANCE, LUMINANCE_COMPRESSED, DEPTH, 
                           LUMINANCE_ALPHA, LUMINANCE_ALPHA_COMPRESSED, 
                           RGB, BGR, RGB_COMPRESSED, RGB32F, 
                           RGBA, BGRA, RGBA_COMPRESSED, RGBA32F };

        /**
         * Texture Wrapping options
         */
        enum Wrapping {CLAMP, CLAMP_TO_EDGE, REPEAT};

        /**
         * Basic texture interface.
         *
         * @class ITexture ITexture.h Resources/ITexture.h
         */
        class ITexture {
        protected:
            unsigned int id;
            unsigned char channels;
            Type type;
            ColorFormat format;
            Wrapping wrap;
            void* data;
            bool mipmapping;
            bool compression;

            /**
             * Sets up the textures type dependent on the template
             * parameter.
             */
            template <class T> void SetupType(){
                this->type = GetResourceType<T>();
            }

            /**
             * Given a number of channels, the default colorformat is
             * returned.
             */
            ColorFormat ColorFormatFromChannels(unsigned char c){
                switch(c){
                case 1: return LUMINANCE;
                case 2: return LUMINANCE_ALPHA;
                case 3: return RGB;
                case 4: return RGBA;
                }
                return RGBA;
            }

        public:
            ITexture() {
                id = channels = 0;
                data = NULL;
                mipmapping = true;
                compression = true;
                type = NOTYPE;
                wrap = REPEAT;
            }

            virtual ~ITexture() {}

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
             * Get the size of each channel on the loaded texture.
             *
             * @return Channel size in bytes.
             */
            virtual unsigned int GetChannelSize() = 0;

            /**
             * Get number of channels in the texture.
             *
             * @return Channels the number of channels.
             */
            inline unsigned char GetChannels() const { return channels; }
            
            /**
             * Get pointer to loaded texture.
             *
             * @return Char pointer to loaded data.
             */
            inline void* GetVoidDataPtr() const { return data; }

            /**
             * Get the type of the texture.
             *
             * @return Type the type of the texture.
             */
            inline Type GetType() const { return type; }

            /**
             * Set the type of the texture.
             */
            virtual void SetType(Type t) { type = t; }

            /**
             * Get color format of the texture.
             *
             * @return ColorFormat representing the way colors are stored
             */
            inline ColorFormat GetColorFormat() const { return format; }

            /**
             * Set color format of the texture.
             */
            virtual void SetColorFormat(ColorFormat f) { format = f; }

            /**
             * Set wether mipmapping should be enabled or disabled.
             *
             * Defaults to ignoring the argument.
             */
            virtual void SetMipmapping(const bool m){ mipmapping = m; }

            /**
             * Tells wether mipmapping should be used or not.
             *
             * Defaults to true.
             *
             * @ return true if mipmapping is used otherwise false.
             */
            inline bool UseMipmapping() const { return mipmapping; }

            /**
             * Sets the texture wrapping used for this texture
             */
            virtual void SetWrapping(Wrapping w) { wrap = w; }

            /**
             * Returns the texture wrapping used for this texture.
             *
             * @return Wrapping The wrapping used.
             */
            inline Wrapping GetWrapping() const { return wrap; }

            /**
             * Returns wether or not to use compression.
             *
             * @return bool Compression.
             */
            inline bool UseCompression() const { return compression; }

            /**
             * Set wether compression should be used or not if
             * available.
             *
             * @param c Compression.
             */
            virtual void SetCompression(bool c) { compression = c; }

        };

        /**
         * Texture resource smart pointer.
         */
        typedef boost::shared_ptr<ITexture> ITexturePtr;

    }
}

#endif
