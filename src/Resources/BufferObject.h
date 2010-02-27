// Buffer object.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BUFFER_OBJECT_H_
#define _BUFFER_OBJECT_H_

#include <Resources/IBufferObject.h>
#include <Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Resources {

        template <unsigned int N, class T>
        class BufferObject : public IBufferObject {
        public:
            BufferObject()
                : IBufferObject() {
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            BufferObject(unsigned int s)
                : IBufferObject() {
                this->dimension = N;
                this->type = GetResourceType<T>();
                this->size = s;
            }            

            BufferObject(T* d, unsigned int s)
                : IBufferObject() {
                this->dimension = N;
                this->type = GetResourceType<T>();
                this->data = d;
                this->size = s;
            }

            ~BufferObject(){
                if (this->data)
                    delete [] (T*) this->data;
            }

            /**
             * Loads an array.
             */
            void Load() {
                if (!this->data)
                    this->data = new T[this->size * N];
            }

            /**
             * Unloads the data array.
             */
            void Unload() {
                if (this->data){
                    delete [] (T*) this->data;
                    this->data = NULL;
                }
            }

            /**
             * Get pointer to loaded data.
             *
             * @return T* pointer to loaded data.
             */
            inline T* GetData() const{
                return (T*) this->data;
            }

            /**
             * Gets the i'th element in a buffer object.
             */
            inline VectorIterator<N, T> GetElement(unsigned int i) const {
                unsigned int index = i * dimension;
                T* data = this->data;
                return VectorIterator<N, T>(data + index, N);
            }
           
            inline VectorIterator<N, T> Begin() const {
                return VectorIterator<N, T>((T*)this->data, this->size);
            }

            inline VectorIterator<N, T> End() const {
                T* data = this->data;
                return VectorIterator<N, T>(this->size, data + this->size * N);
            }
        };

        /**
         * Buffer Object smart pointer.
         */
        //typedef boost::shared_ptr<BufferObject> BufferObjectPtr;

    }
}

#endif
