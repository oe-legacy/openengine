// Texture 3D resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TEXTURE_3D_RESOURCE_H_
#define _TEXTURE_3D_RESOURCE_H_

#include <Resources/ITexture3D.h>
#include <Math/Exceptions.h>
#include <Resources/Exceptions.h>

namespace OpenEngine {
    namespace Resources {

        /**
         * Templated 3D texture implementation with basic Load and
         * Unload functions.
         *
         * @class TTexture3D Texture3D.h Resources/Texture3D.h
         */
        template <class T> class Texture3D : public ITexture3D {
        public:
            Texture3D()
                : ITexture3D() {
                SetupType<T>();
            }

            Texture3D(unsigned int w, unsigned int h, unsigned int d, unsigned int c)
                : ITexture3D() {
                SetupType<T>();
                this->width = w;
                this->height = h;
                this->depth = d;
                this->channels = c;
                this->format = ColorFormatFromChannels(c);
            }

            Texture2D(unsigned int w, unsigned int h, unsigned int c, T* data)
                : ITexture2D() {
                SetupType<T>();
                this->width = w;
                this->height = h;
                this->depth = d;
                this->channels = c;
                this->format = ColorFormatFromChannels(c);
                this->data = data;
            }
            
            virtual ~Texture3D() {
                if (this->data){
                    delete [] (T*) this->data;
                }
            }

            /**
             * Loads an empty data array.
             */
            virtual void Load() {
                if (this->data == NULL)
                    data = new T[this->width * this->height * this->depth * this->channels];
            }

            /**
             * Unloads the data array but leaves the property values.
             */
            virtual void Unload(){
                if (this->data) {
                    delete [] (T*) this->data;
                    this->data = NULL;
                }
            }

            /**
             * Get the size of each channel on the loaded texture.
             *
             * @return Channel size in bytes.
             */
            unsigned int GetChannelSize(){
                return sizeof(T);
            }

            /**
             * Get pointer to loaded texture data.
             *
             * @return T* pointer to loaded data.
             */
            inline T* GetData() const{
                return (T*) this->data;
            }

            /**
             * Get a pointer to the specific pixel at (x, y).
             *
             * return T The pointer to the pixel.
             */
            inline T* GetVoxel(const unsigned int x, const unsigned int y, const unsigned int z) const{
#ifdef OE_SAFE
                if (this->data == NULL){
                    throw ResourceException("Cannot get pixel data from null texture.");
                }
                // Check bounds
                if (x > width) throw Math::IndexOutOfBounds(x, 0, width);
                if (y > height) throw Math::IndexOutOfBounds(y, 0, height);
                if (z > depth) throw Math::IndexOutOfBounds(z, 0, depth);
#endif
                unsigned int entry = x + y * width + z * width * height;
                T* data = (T*) this->data;
                return data + entry * this->channels;
            }

        };

        /**
         * Texture resource smart pointer.
         */
        typedef Texture3D<unsigned char>  UCharTexture3D;
        typedef Texture3D<char>  CharTexture3D;
        typedef Texture3D<unsigned int>  UIntTexture3D;
        typedef Texture3D<int>  IntTexture3D;
        typedef Texture3D<float>  FloatTexture3D;

        typedef boost::shared_ptr<Texture3D<unsigned char> > UCharTexture3DPtr;
        typedef boost::shared_ptr<Texture3D<char> > CharTexture3DPtr;
        typedef boost::shared_ptr<Texture3D<unsigned int> > UIntTexture3DPtr;
        typedef boost::shared_ptr<Texture3D<int> > IntTexture3DPtr;
        typedef boost::shared_ptr<Texture3D<float> > FloatTexture3DPtr;

#define Texture3DPtr(T) boost::shared_ptr<Texture3D<T> >
    }
}

#endif
