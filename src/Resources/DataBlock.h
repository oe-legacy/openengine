// Data block.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DATA_BLOCK_H_
#define _DATA_BLOCK_H_

#include <Resources/IDataBlock.h>
#include <string.h>

namespace OpenEngine {
    namespace Resources {

        template <unsigned int N, class T>
        class DataBlock : public IDataBlock {
        public:
            DataBlock(unsigned int s = 0, T* d = NULL,
                      BlockType b = ARRAY, UpdateMode u = STATIC)
                : IDataBlock(s, d, b, u) {
                if (d == NULL)
                    this->data = new T[N * s];
                this->dimension = N;
                this->type = Types::GetResourceType<T>();
            }

            DataBlock(IDataBlock* block) 
                : IDataBlock(block->GetSize(), NULL, 
                             block->GetBlockType(), block->GetUpdateMode()){
                this->dimension = N;
                this->type = Types::GetResourceType<T>();
#ifdef OE_SAFE
                if (this->type != block->GetType())
                    throw Math::Exception("Types not equal");
#endif
                this->policy = block->GetUnloadPolicy();

                if (block->GetVoidDataPtr() != NULL){
                    this->data = new T[N * this->size];
                    memcpy(this->data, block->GetVoidDataPtr(), N * this->size * sizeof(T));
                }
            }

            ~DataBlock(){
                if (this->data)
                    delete [] (T*) this->data;
            }

            IDataBlockPtr Clone() {
                T* data = new T[N * this->size];
                memcpy(data, this->data, N * this->size * sizeof(T));
                DataBlock<N, T>* block = new DataBlock<N, T>(this->size, data, 
                                                             this->blockType,
                                                             this->updateMode);
                block->SetUnloadPolicy(this->policy);
                return IDataBlockPtr(block);
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
             * Gets the i'th element in the data block.
             */
            inline Math::Vector<N, T> GetElement(unsigned int i) const {
                T* data = (T*)this->data;
                return Math::Vector<N, T>(data + i * N);
            }
            inline Math::Vector<N, T> operator[](const unsigned int i){
                return GetElement(i);
            }

#undef VECTOR
#define VECTOR(dim, type)                                               \
            inline Math::Vector<N, T> ConvertVector(const Math::Vector<dim, type> value){ \
                Math::Vector<N, T> vec;                                 \
                for (unsigned int i = 0; i < N && i < dim; ++i)         \
                    vec[i] = (T)value.Get(i);                           \
                return vec;                                             \
            }                                                           \
                                                                        \
            inline void GetElement(unsigned int i, Math::Vector<dim, type> &element){ \
                Math::Vector<N, T> vec = GetElement(i);                 \
                for (unsigned int i = 0; i < dim; ++i)                  \
                    element[i] = i < N ? vec.Get(i) : 0;                \
            }                                                           \
            inline void SetElement(unsigned int i, const Math::Vector<dim, type> value){ \
                Math::Vector<N, T> vec = ConvertVector(value);          \
                T* data = ((T*)this->data) + i * N;                     \
                for (unsigned int i = 0; i < N; ++ i)                   \
                    data[i] = vec.Get(i);                               \
            }                                                           \
            inline void operator+=(const Math::Vector<dim, type> value) { \
                Math::Vector<N, T> vec = ConvertVector(value);          \
                for (unsigned int i = 0; i < this->size; ++i){          \
                    Math::Vector<N, T> element = GetElement(i);         \
                    SetElement(i, element + vec);                       \
                }                                                       \
            }                                                           \
            inline IDataBlockPtr operator+(const Math::Vector<dim, type> value) { \
                IDataBlockPtr clone = this->Clone();                    \
                *clone += value;                                        \
                return clone;                                           \
            }                                                           \
            inline void operator-=(const Math::Vector<dim, type> value) { \
                Math::Vector<N, T> vec = ConvertVector(value);          \
                for (unsigned int i = 0; i < this->size; ++i){          \
                    Math::Vector<N, T> element = GetElement(i);         \
                    SetElement(i, element - vec);                       \
                }                                                       \
            }                                                           \
            inline IDataBlockPtr operator-(const Math::Vector<dim, type> value) { \
                IDataBlockPtr clone = this->Clone();                    \
                *clone -= value;                                        \
                return clone;                                           \
            }                                                           \

#undef SCALAR
#define SCALAR(type)                                                    \
            inline void operator*=(const float s){                      \
                for (unsigned int i = 1; i < this->size; ++i){          \
                    Math::Vector<N, T> element = GetElement(i);         \
                    SetElement(i, element * (const T)s);                \
                }                                                       \
            }                                                           \
            inline IDataBlockPtr operator*(const float s){              \
                IDataBlockPtr clone = this->Clone();                    \
                *clone *= s;                                            \
                return clone;                                           \
            }                                                           \
            inline void operator/=(const float s){                      \
                for (unsigned int i = 1; i < this->size; ++i){          \
                    Math::Vector<N, T> element = GetElement(i);         \
                    SetElement(i, element / (const T)s);                \
                }                                                       \
            }                                                           \
            inline IDataBlockPtr operator/(const float s){              \
                IDataBlockPtr clone = this->Clone();                    \
                *clone /= s;                                            \
                return clone;                                           \
            }                                                           \
            
#include <Resources/DataBlockVectorList.h>
            
            inline void Normalize() {
                for (unsigned int i = 1; i < this->size; ++i){          
                    Math::Vector<N, T> element = GetElement(i); 
                    element.Normalize();
                    SetElement(i, element);            
                }                                                       
            }

            std::string ToString(){
                std::ostringstream out;
                out << "[";
                for (unsigned int i = 0; i+1 < size; ++i)
                    out << GetElement(i) << ", ";
                        
                out << GetElement(size-1) << "]";
                return out.str();
            }
        };

        /**
         * Data block smart pointer.
         */
        typedef boost::shared_ptr<DataBlock<2, float> > Float2DataBlockPtr;
        typedef boost::shared_ptr<DataBlock<3, float> > Float3DataBlockPtr;
        typedef boost::shared_ptr<DataBlock<4, float> > Float4DataBlockPtr;

        /**
         * Define special index block.
         */
        class Indices : public DataBlock<1, unsigned int> {
        public:
            Indices(unsigned int s = 0, unsigned int* d = NULL)
                : DataBlock<1, unsigned int>(s, d, INDEX_ARRAY) {
            }
        };
        typedef boost::shared_ptr<Indices> IndicesPtr;

    }
}

#endif
