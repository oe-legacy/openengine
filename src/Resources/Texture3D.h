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
#include <Utils/Convert.h>

#include <vector>
using std::vector;

namespace OpenEngine {
    using Utils::Convert;
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
                std::memset(data,0,h*w*d*c);
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
                this->depth = l.size();

                this->width = 0;
                this->height = 0;
                this->channels = 0;
                typename vector<Texture2DPtr(T) >::iterator itr = l.begin();
                this->format = Resources::UNKNOWN;
                unsigned int count = 1;
                bool allSliceSameSize = true;
                while (itr != l.end()) {
                    Texture2DPtr(T) tex = *itr;
                    tex->Load();
                    unsigned int w = tex->GetWidth();
                    unsigned int h = tex->GetHeight();
                    if (w == 0 || h == 0)
                        throw Core::Exception("texture with zero dimension");

                    if (allSliceSameSize) {
                        if (this->width != 0 && w != this->width)
                            allSliceSameSize = false;
                        else if (this->height != 0 && h != this->height)
                            allSliceSameSize = false;
                    }

                    if (this->width < w)
                        this->width = w;
                    if (this->height < h)
                        this->height = h;
                    if (this->channels < tex->GetChannels())
                        this->channels = tex->GetChannels();

                    if (itr == l.begin())
                        this->format = tex->GetColorFormat();
                    else if (this->format != tex->GetColorFormat())
                        throw Core::Exception("format mismatch on count: " +
                                              Convert::ToString(count) + " " +
                                              colorFomatToString(this->format)
                                              + "!=" +
                                              colorFomatToString(tex->GetColorFormat()));

                    ++itr;
                    count++;
                }

                unsigned int lineWidth = this->width * this->channels;
                unsigned long sliceSize = lineWidth * this->height;
                unsigned long size = sliceSize * this->depth;
                T* data = new T[size];
                this->data = data;

                if (allSliceSameSize) {
                    for (unsigned int d = 0; d < this->depth; ++d) {
                        T* from = l[d]->GetData();
                        T* to = data + d * sliceSize;
                        std::memcpy(to, from, sliceSize*sizeof(T));
                    }
                } else {
                    // @todo: move resampling to a function for reuse
                    for (unsigned int w = 0; w < this->width; ++w){
                        for (unsigned int h = 0; h < this->height; ++h){
                            float x = float(w) / float(this->width);
                            float y = float(h) / float(this->height);
                            for (unsigned int d = 0; d < this->depth; ++d){
                                T* voxel = GetVoxel(w,h,d);
                                Vector<4, T> color =
                                    l[d]->InterpolatedPixel(x, y);
                                
                                for (unsigned int c = 0; c<this->channels; ++c)
                                    voxel[c] = color.Get(c);
                            }
                        }
                    }
                }
            }
            
            virtual ~Texture3D() {
                if (this->data){
                    delete [] (T*) this->data;
                }
            }

            Texture3D<T>* Clone(){
                T* data = new T[this->width * this->height * this->depth * this->channels];
                memcpy(data, this->data, this->width * this->height * this->depth * this->channels * sizeof(T));
                Texture3D<T>* clone = new Texture3D<T>(this->width, this->height, this->depth, 
                                                       this->channels, data);
                clone->format = this->format;
                clone->wrap = this->wrap;
                clone->mipmapping = this->mipmapping;
                clone->compression = this->compression;
                clone->useCase = this->useCase;
                return clone;
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
                    Z = z % depth;
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
#if OE_SAFE
            if ( 0 > x || x > 1)
                throw Core::Exception("x out of range");
            if ( 0 > y || y > 1)
                throw Core::Exception("y out of range");
            if ( 0 > z || z > 1)
                throw Core::Exception("z out of range");
#endif

	    unsigned int X = (unsigned int)(x * width);
	    unsigned int Y = (unsigned int)(y * height);
	    unsigned int Z = (unsigned int)(z * depth);

	    float dX = X / (float)width  - x;
	    float dY = Y / (float)height - y;
	    float dZ = Z / (float)depth  - z;

	    // trilinear interpolation from:
	    // http://local.wasp.uwa.edu.au/~pbourke
	    // /miscellaneous/interpolation/
	    Vector<4, T> v000 = GetVoxelValues(X, Y, Z);
	    Vector<4, T> v100 = GetVoxelValues(X+1, Y, Z);
	    Vector<4, T> v001 = GetVoxelValues(X, Y+1, Z);
	    Vector<4, T> v101 = GetVoxelValues(X+1, Y+1, Z);
	    Vector<4, T> v010 = GetVoxelValues(X, Y, Z+1);
	    Vector<4, T> v110 = GetVoxelValues(X+1, Y, Z+1);
	    Vector<4, T> v011 = GetVoxelValues(X, Y+1, Z+1);
	    Vector<4, T> v111 = GetVoxelValues(X+1, Y+1, Z+1);

	    Vector<4, T> vxyz = 
	      v000 * (1-dX) * (1-dY) * (1-dZ) +
	      v100 * dX     * (1-dY) * (1-dZ) +
	      v010 * (1-dX) * dY     * (1-dZ) +
	      v001 * (1-dX) * (1-dY) * dZ     +
	      v101 * dX     * (1-dY) * dZ     +
	      v011 * (1-dX) * dY     * dZ     +
	      v000 * dX     * dY     * (1-dZ) +
	      v111 * dX     * dY     * dZ;
	    return vxyz;
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
