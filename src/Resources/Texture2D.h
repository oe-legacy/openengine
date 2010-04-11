// Texture 2D resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TEXTURE_2D_RESOURCE_H_
#define _TEXTURE_2D_RESOURCE_H_

#include <Resources/ITexture2D.h>
#include <Math/Exceptions.h>
#include <Resources/Exceptions.h>
#include <Math/Vector.h>
#include <cstring>

using OpenEngine::Math::Vector;

namespace OpenEngine {
    namespace Resources {

        /**
         * Templated 2D texture implementation with basic Load and
         * Unload functions.
         *
         * @class TTexture2D Texture2D.h Resources/Texture2D.h
         */
        template <class T> class Texture2D : public ITexture2D {
        public:
            Texture2D()
                : ITexture2D() {
                SetupType<T>();
            }

            Texture2D(unsigned int w, unsigned int h, unsigned int c)
                : ITexture2D() {
                SetupType<T>();
                this->width = w;
                this->height = h;
                this->channels = c;
                this->format = ColorFormatFromChannels(c);
                data = new T[w*h*c];
                std::memset(data,height*width*channels,0);
            }
            
            Texture2D(unsigned int w, unsigned int h, unsigned int c, T* d)
                : ITexture2D() {
                SetupType<T>();
                this->width = w;
                this->height = h;
                this->channels = c;
                this->format = ColorFormatFromChannels(c);
                this->data = d;
            }

            virtual ~Texture2D() {
                if (this->data){
                    delete [] (T*) this->data;
                }
            }

            /**
             * Loads an empty data array.
             */
            virtual void Load() {
                if (this->data == NULL)
                    data = new T[this->width * this->height * this->channels];
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
             * Get a pointer to the specific pixel at (x, y). Uses the
             * wrapping mode specified to handle out of bounds values.
             *
             * return T The pointer to the pixel.
             */
            inline T* GetPixel(const int x, const int y) const{
#ifdef OE_SAFE
                if (this->data == NULL){
                    throw ResourceException("Cannot get pixel data from null texture.");
                }
#endif
                unsigned int X, Y;
                switch(this->wrap){
                case REPEAT:
                    X = x % width;
                    Y = y % height;
                    break;
                default:
                    if (x < 0)
                        X = 0;
                    else if (width <= (unsigned int)x)
                        X = width - 1;
                    else
                        X = x;
                    if (y < 0)
                        Y = 0;
                    else if (height <= (unsigned int)y)
                        Y = height - 1;
                    else
                        Y = y;
                }

                unsigned int entry = X + Y * width;
                T* data = (T*) this->data;
                return data + entry * this->channels;
            }

            Vector<4,T> GetPixelValues(const int x, const int y) {
                T* p = GetPixel(x, y);
                Vector<4, T> vec(0.0f);
                vec[0] = *p;
                if (channels == 2)
                    vec[1] = *(p+1);
                if (channels == 3)
                    vec[2] = *(p+2);
                if (channels == 4)
                    vec[3] = *(p+3);
                return vec;
            }
            
            /**
             * Get a Vector of the bilinearly interpolated values.
             *
             * return The color values as a Vector<4, T>
             */
            inline Vector<4, T> InterpolatedPixel(const float x, const float y){
                unsigned int X = x * width;
                unsigned int Y = y * height;

                float dX = X / (float)width - x;
                float dY = Y / (float)height - y;

                Vector<4, T> lowerleft = GetPixelValues(X, Y);
                Vector<4, T> lowerright = GetPixelValues(X+1, Y);
                Vector<4, T> upperleft = GetPixelValues(X, Y+1);
                Vector<4, T> upperright = GetPixelValues(X+1, Y+1);

                return lowerleft * (1-dX) * (1-dY) +
                       lowerright * dX * (1-dY) +
                       upperleft * (1-dX) * dY +
                       upperright * dX * dY;
            }

            virtual void Reverse() {
                unsigned int height = this->height;
                unsigned int width = this->width;
                T* data = (T*) this->data;
                T temp;
                long size = width * height * channels;
                for (int i = 0, j = size-channels; i < j;
                     i += channels, j -= channels) {
                    for (int index = 0; index < channels; index++) {
                        temp = data[i+index];
                        data[i+index] = data[j+index];
                        data[j+index] = temp;
                    }
                }
            }

            virtual void ReverseVertecally() {
                //@todo make an optimized version that does this in one loop
                Reverse();
                ReverseHorizontally();
            }

            virtual void ReverseHorizontally() {
                unsigned int height = this->height;
                unsigned int width = this->width;
                T* data = (T*) this->data;
                T temp;
                long size = width * height * channels;
                for (int lineNumber=0; lineNumber<size;
                     lineNumber+=width*channels) {
                    for (int i=0, j=(width-1)*channels; i < j;
                         i+=channels, j-=channels) {
                        for(int index=0; index<channels;index++) {
                            temp = data[lineNumber+i+index];
                            data[lineNumber+i+index] = data[lineNumber+j+index];
                            data[lineNumber+j+index] = temp;
                        }
                    }
                }
            }

        };

        /**
         * Texture resource smart pointer.
         */
        typedef Texture2D<unsigned char>  UCharTexture2D;
        typedef Texture2D<char>  CharTexture2D;
        typedef Texture2D<unsigned int>  UIntTexture2D;
        typedef Texture2D<int>  IntTexture2D;
        typedef Texture2D<float>  FloatTexture2D;

        typedef boost::shared_ptr<Texture2D<unsigned char> > UCharTexture2DPtr;
        typedef boost::shared_ptr<Texture2D<char> > CharTexture2DPtr;
        typedef boost::shared_ptr<Texture2D<unsigned int> > UIntTexture2DPtr;
        typedef boost::shared_ptr<Texture2D<int> > IntTexture2DPtr;
        typedef boost::shared_ptr<Texture2D<float> > FloatTexture2DPtr;

#define Texture2DPtr(T) boost::shared_ptr<Texture2D<T> >
    }
}

#endif
