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

namespace OpenEngine {
    namespace Resources {

        enum ColorFormat { RGBA, BGRA, RGB, BGR, LUMINANCE };

        class ITexture {
        protected:
            unsigned int id;
            unsigned char channels;
            ColorFormat format;
            unsigned char* data;
            bool mipmapping;
            unsigned int apiType;

        public:
            ITexture() {
                id = channels = apiType = 0;
                data = NULL;
                mipmapping = true;
            }

            virtual ~ITexture() {
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
            inline void* GetVoidDataPtr() { return (void*) data; }

            /**
             * Get pointer to loaded texture.
             *
             * @return Char pointer to loaded data.
             */
            inline unsigned char* GetData() { return data; }
            
            /**
             * Get color format of the texture.
             *
             * @return ColorFormat representing the way colors are stored
             */
            inline ColorFormat GetColorFormat() { return format; }

            /**
             * Set wether mipmapping should be enabled or disabled.
             *
             * Defaults to ignoring the argument.
             */
            virtual void SetMipmapping(const bool m){
                mipmapping = m;
            }

            /**
             * Tells wether mipmapping should be used or not.
             *
             * Defaults to true.
             *
             * @ return true if mipmapping is used otherwise false.
             */
            bool UseMipmapping() const {
                return mipmapping;
            }

        };

        /**
         * Texture resource smart pointer.
         */
        typedef boost::shared_ptr<ITexture> ITexturePtr;

    }
}

#endif
