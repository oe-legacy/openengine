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

#include <Core/Exceptions.h>
#include <Resources/Types/ResourceTypes.h>
#include <Resources/ISerializable.h>

namespace OpenEngine {
    namespace Resources {
        
        /**
         * Forward declaration.
         */
        class ITexture;
        class ICubemap;
        
        /**
         * Texture resource smart pointer.
         */
        typedef boost::shared_ptr<ITexture> ITexturePtr;
        typedef boost::shared_ptr<ICubemap> ICubemapPtr;

        /**
         * Color Format enumeration.
         */
        enum ColorFormat {UNKNOWN, ALPHA, ALPHA_COMPRESSED, 
                          LUMINANCE, LUMINANCE_COMPRESSED, DEPTH, LUMINANCE32F,
                          LUMINANCE_ALPHA, LUMINANCE_ALPHA_COMPRESSED, 
                          RGB, BGR, RGB_COMPRESSED, RGB32F, 
                          RGBA, BGRA, RGBA_COMPRESSED, RGBA32F };

        /**
         * Texture Wrapping options
         */
        enum Wrapping {CLAMP = 0x2900, 
                       CLAMP_TO_EDGE = 0x812F, 
                       REPEAT = 0x2901};
        
        /**
         * Texture filtering options
         */
        enum Filtering {NONE = 0x2700, // GL_NEAREST_MIPMAP_NEAREST
                        BILINEAR = 0x2701, // GL_LINEAR_MIPMAP_NEAREST
                        TRILINEAR = 0x2703}; // GL_LINEAR_MIPMAP_LINEAR

        /**
         * Basic texture interface.
         *
         * @class ITexture ITexture.h Resources/ITexture.h
         */
        class ITexture : public ISerializable {
        protected:
            unsigned int id;
            unsigned char channels;
            Types::Type type;
            ColorFormat format;
            Filtering filtering;
            Wrapping wrap;
            void* data;
            bool mipmapping;
            bool compression;

            /**
             * Sets up the textures type dependent on the template
             * parameter.
             */
            template <class T> void SetupType(){
                this->type = Types::GetResourceType<T>();
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
                return Resources::UNKNOWN;
            }

            /**
             * Given a number of channels, the default colorformat is
             * returned.
             */
            ColorFormat ColorFormatFromChannelsBGR(unsigned char c){
                switch(c){
                case 1: return LUMINANCE;
                case 2: return LUMINANCE_ALPHA;
                case 3: return BGR;
                case 4: return BGRA;
                }
                return Resources::UNKNOWN;
            }

            unsigned char ChannelsFromColorFormat(ColorFormat c){
                switch (c) {
                case Resources::UNKNOWN: return 0;
                case ALPHA:
                case ALPHA_COMPRESSED:
                case LUMINANCE:
                case LUMINANCE_COMPRESSED:
                case DEPTH:
                case LUMINANCE32F:
                    return 1;
                case LUMINANCE_ALPHA:
                case LUMINANCE_ALPHA_COMPRESSED:
                    return 2;
                case RGB:
                case BGR:
                case RGB_COMPRESSED:
                case RGB32F:
                    return 3;
                case RGBA:
                case BGRA:
                case RGBA_COMPRESSED:
                case RGBA32F:
                    return 4;
                }
                return 0;
            }

        public:
            ITexture() {
                id = channels = 0;
                data = NULL;
                mipmapping = true;
                compression = false;
                type = Types::NOTYPE;
                format = Resources::UNKNOWN;
                wrap = REPEAT;
                filtering = TRILINEAR;
            }

            virtual ~ITexture() {}

            virtual ITexture* Clone() = 0;

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
            inline Types::Type GetType() const { return type; }

            /**
             * Set the type of the texture.
             */
            virtual void SetType(Types::Type t) { type = t; }

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
             * Sets the texture filtering used for this texture
             */
            virtual void SetFiltering(Filtering f) { filtering = f; }

            /**
             * Returns the texture filtering used for this texture.
             *
             * @return Filtering The filtering used.
             */
            inline Filtering GetFiltering() const { return filtering; }

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

            inline static void* CreateDataArray(const int size, const ColorFormat f){
                switch(f){
                case RGBA: //RGBA32
                    return new unsigned char[size*4];
                    break;
                default:
                    throw Core::Exception("Colorformat not supported");
                }
            }

            inline static void DeleteDataArray(void* data, const ColorFormat f){
                switch(f){
                case RGBA: //RGBA32
                    delete (unsigned char*) data;
                    return;
                default:
                    throw Core::Exception("Colorformat not supported");
                }
            }

            // Serialization
            virtual void Serialize(IArchiveWriter&) {}; //! @Todo make pure virtual.
            virtual void Deserialize(IArchiveReader&) {};
            virtual unsigned int GetSerialzationTag() {return (unsigned int)-1;}
            
            static std::string colorFormatToString(ColorFormat cf) {
                switch(cf) {
                case Resources::UNKNOWN : return "UNKNOWN";
                case Resources::ALPHA : return "ALPHA";
                case Resources::ALPHA_COMPRESSED : return "ALPHA_COMPRESSED";
                case Resources::LUMINANCE : return "LUMINANCE";
                case Resources::LUMINANCE_COMPRESSED : 
                    return "LUMINANCE_COMPRESSED";
                case Resources::DEPTH : return "DEPTH";
                case Resources::LUMINANCE32F : return "LUMINANCE32F";
                case Resources::LUMINANCE_ALPHA : return "LUMINANCE_ALPHA";
                case Resources::LUMINANCE_ALPHA_COMPRESSED : 
                    return "LUMINANCE_ALPHA_COMPRESSED";
                case Resources::RGB : return "RGB";
                case Resources::BGR : return "BGR";
                case Resources::RGB_COMPRESSED : return "RGB_COMPRESSED";
                case Resources::RGB32F : return "RGB32F";
                case Resources::RGBA : return "RGBA";
                case Resources::BGRA : return "BGRA";
                case Resources::RGBA_COMPRESSED : return "RGBA_COMPRESSED";
                case Resources::RGBA32F : return "RGBA32F";
                default:
                    return "unknown type";
                }
            }
        };

    } // NS Resources
} // OpenEngine

#endif
