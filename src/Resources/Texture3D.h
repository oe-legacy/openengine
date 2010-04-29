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
#include <Resources/Texture2D.h>
#include <Math/Exceptions.h>
#include <Resources/Exceptions.h>

#include <vector>
using std::vector;

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
                data = new T[w*h*d*c];
                std::memset(data,height*width*depth*channels,0);
            }


            Texture3D(unsigned int w, unsigned int h, unsigned int d, 
                      unsigned int c, T* data)
                : ITexture3D() {
                SetupType<T>();
                this->width = w;
                this->height = h;
                this->depth = d;
                this->channels = c;
                this->format = ColorFormatFromChannels(c);
                this->data = data;
            }

            Texture3D(vector<Texture2DPtr(T)> l)
                : ITexture3D() {
                SetupType<T>();
                this->width = 0;
                this->height = 0;
                this->depth = l.size();
                this->channels = 1;
                typename vector<Texture2DPtr(T) >::iterator itr = l.begin();
                while (itr != l.end()) {
                    Texture2DPtr(T) tex = *itr;
                    tex->Load();
                    if (this->width < tex->GetWidth()) this->width = tex->GetWidth();
                    if (this->height < tex->GetHeight()) this->height = tex->GetHeight();
                    if (this->channels < tex->GetChannels()) this->channels = tex->GetChannels();

                    ++itr;
                }
                this->format = ColorFormatFromChannels(this->channels);
                this->data = new T[this->width * this->height * this->depth * this->channels];
                
                for (unsigned int w = 0; w < this->width; ++w){
                    for (unsigned int h = 0; h < this->height; ++h){
                        float x = float(w) / float(this->width);
                        float y = float(h) / float(this->height);
                        for (unsigned int d = 0; d < this->depth; ++d){
                            T* voxel = GetVoxel(w,h,d);
                            Vector<4, T> color = l[d]->InterpolatedPixel(x, y);
                            
                            for (unsigned int c = 0; c < this->channels; ++c)
                                voxel[c] = color.Get(c);
                        }
                    }
                }

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
             * Get a pointer to the specific voxel at (x, y, z).
             *
             * return T The pointer to the voxel.
             */
            inline T* GetVoxel(const int x, const int y, const int z) const {
#ifdef OE_SAFE
                if (this->data == NULL){
                    throw ResourceException("Cannot get pixel data from null texture.");
                }
#endif
                unsigned int X, Y, Z;
                switch(this->wrap){
                case REPEAT:
                    X = x % width;
                    Y = y % height;
                    Z = z % height;
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
                    if (z < 0)
                        Z = 0;
                    else if (depth <= (unsigned int)z)
                        Z = depth - 1;
                    else
                        Z = z;
                }

                unsigned int entry = X + Y * width + Z * width * height;
                T* data = (T*) this->data;
                return data + entry * this->channels;
            }

        Vector<4,T> GetVoxelValues(const int x, const int y, const int z) {
            T* p = GetVoxel(x, y, z);
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
            
        inline Vector<4, T> InterpolatedVoxel(const float x,
                                              const float y,
                                              const float z){
                unsigned int X = x * width;
                unsigned int Y = y * height;
                unsigned int Z = z * depth;

                float dX = X / (float)width  - x;
                float dY = Y / (float)height - y;
                float dZ = Z / (float)depth  - z;

                Vector<4, T> llb = GetVoxelValues(X, Y, Z);
                Vector<4, T> lrb = GetVoxelValues(X+1, Y, Z);
                Vector<4, T> ulb = GetVoxelValues(X, Y+1, Z);
                Vector<4, T> urb = GetVoxelValues(X+1, Y+1, Z);

                Vector<4, T> llf = GetVoxelValues(X, Y, Z+1);
                Vector<4, T> lrf = GetVoxelValues(X+1, Y, Z+1);
                Vector<4, T> ulf = GetVoxelValues(X, Y+1, Z+1);
                Vector<4, T> urf = GetVoxelValues(X+1, Y+1, Z+1);

                Vector<4, T> back = llb * (1-dX) * (1-dY) +
                    lrb * dX * (1-dY) +
                    ulb * (1-dX) * dY +
                    urb * dX * dY;

                Vector<4, T> front = llf * (1-dX) * (1-dY) +
                    lrf * dX * (1-dY) +
                    ulf * (1-dX) * dY +
                    urf * dX * dY;

                Vector<4, T> result = front * (1-dZ) +
                    back * dZ;

                // @todo: missing third dimension
                return result;
            }
        };

        /**
         * Texture 3D smart pointer.
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
