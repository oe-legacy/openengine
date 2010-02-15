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

#include <Resources/ResourceFormats.h>
#include <Renderers/IRenderer.h>

namespace OpenEngine {
    namespace Resources {

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

            /**
             * Sets up the textures type dependent on the template
             * parameter.
             */
            template <class T> void SetupType(){
                if (typeid(T) == typeid(unsigned char))
                    this->type = UBYTE;
                else if (typeid(T) == typeid(char))
                    this->type = BYTE;
                else if (typeid(T) == typeid(unsigned int))
                    this->type = UINT;
                else if (typeid(T) == typeid(int))
                    this->type = INT;
                else if (typeid(T) == typeid(float))
                    this->type = FLOAT;
                else 
                    this->type = NOTYPE;
            }

        public:
            ITexture() {
                id = channels = 0;
                data = NULL;
                mipmapping = true;
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
             */
            inline Wrapping GetWrapping() const { return wrap; }

        };

        /**
         * Texture resource smart pointer.
         */
        typedef boost::shared_ptr<ITexture> ITexturePtr;

    }
}

#endif
