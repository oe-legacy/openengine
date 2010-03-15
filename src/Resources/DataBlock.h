// Data block.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DATA_BLOCK_H_
#define _DATA_BLOCK_H_

#include <Resources/IDataBlock.h>
#include <Math/VectorList.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Resources {

        template <unsigned int N, class T>
        class DataBlock : public IDataBlock {
        public:
            DataBlock()
                : IDataBlock() {
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            DataBlock(T* d, unsigned int s)
                : IDataBlock(d, s) {
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            ~DataBlock(){
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
             * Gets the i'th element in the buffer object.
             */
            inline Vector<N, T> GetElement(unsigned int i) const {
                unsigned int index = i * N;
                T* data = (T*) this->data;
                return Vector<N, T>(data + index);
            }

            /**
             * Sets the i'th element in the buffer object to the vector.
             *
             * @param value The value to be set to.
             */
            inline void SetElement(unsigned int i, Vector<N, T> value){
                T* data = (T*) this->data;
                data += i * N;
                for (unsigned int j = 0; j < N; ++j)
                    data[j] = value[j];
            }
           
            /**
             * Returns an iterator referring to the first element in
             * the buffer object.
             */
            inline VectorIterator<N, T> Begin() const {
                return VectorIterator<N, T>((T*)this->data, this->size);
            }

            /**
             * Returns an iterator referring to the last element in
             * the buffer object.
             */
            inline VectorIterator<N, T> End() const {
                T* data = (T*) this->data;
                return VectorIterator<N, T>(this->size, data + this->size * N);
            }
        };

        /**
         * Buffer Object smart pointer.
         */
        typedef boost::shared_ptr<DataBlock<2, float> > Float2DataBlockPtr;
        typedef boost::shared_ptr<DataBlock<3, float> > Float3DataBlockPtr;
        typedef boost::shared_ptr<DataBlock<4, float> > Float4DataBlockPtr;

    }
}

#endif
