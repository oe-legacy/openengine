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

#include <Meta/OEMeta.h>
//#include <Renderers/IRenderer.h>

namespace OpenEngine {
    namespace Resources {

        class ITexture {
        protected:
            unsigned int id;
            unsigned char channels;
            OEType type;
            ColorFormat format;
            unsigned char* data;
            bool mipmapping;
            unsigned int apiType;

        public:
            ITexture() {
                id = channels = apiType = 0;
                data = NULL;
                mipmapping = true;
                type = OE_UBYTE;
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
            virtual void SetID(int id) { this->id = id; }
            
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
            inline bool UseMipmapping() const {
                return mipmapping;
            }

            /**
             * Returns the textures type relative to the graphics api
             * after the texture has been applied.
             *
             * ex: In OpenGL ITexture<float>.GetType returns GL_FLOAT.
             *
             * return The api type.
             */
            inline int GetAPIType() const{
                return apiType;
            }

            /**
             * Set the api type. This should be done prior to applying
             * the texture to have any effect.
             */
            inline void SetAPIType(const int type){
                apiType = type;
            }

            /**
             * Returns the textures format relative to the graphics
             * api after the texture has been applied.
             *
             * ex: If the format of the texture is OE_LUMINANCE then
             * with an OpenGL renderer this will return GL_LUMINANCE.
             *
             * return The api type.
             */
            inline int GetAPIColorFormat() const{
                return apiColorFormat;
            }

            /**
             * Set the api format. This should be done prior to
             * applying the texture to have any effect.
             */
            inline void SetAPIColorFormat(const unsigned int format){
                apiColorFormat = format;
            }

            /**
             * Bind the texture to the renderer.
             *
             * If you want your texture to be of a type not supported
             * by the Renderer's GetAPIType method, then you should
             * override this method and implement your own.
            virtual void Bind(Renderers::IRenderer& render) = 0;
             */

            /**
             * Rebind the texture to the renderer, uploading any
             * changes made within the reactangle.
             *
             * If you want your texture to be of a type not supported
             * by the Renderer's GetAPIType method, then you should
             * override this method and implement your own.
            virtual void Update(Renderers::IRenderer& render, unsigned int x, unsigned int y, unsigned int w, unsigned int h) = 0;
             */

        };

        /**
         * Texture resource smart pointer.
         */
        typedef boost::shared_ptr<ITexture> ITexturePtr;

    }
}

#endif
