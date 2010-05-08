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

namespace OpenEngine {
    namespace Resources {

        template <unsigned int N, class T>
        class DataBlock : public IDataBlock {
        protected:
            Math::VectorList<N, T> vectorlist;

        public:
            DataBlock(unsigned int s = 0, T* d = NULL,
                      BlockType b = ARRAY, UpdateMode u = STATIC)
                : IDataBlock(s, d, b, u) {
                if (d == NULL)
                    this->data = new T[N * s];
                vectorlist = Math::VectorList<N, T>((T*)this->data, s);
                this->dimension = N;
                this->type = Types::GetResourceType<T>();
            }

            DataBlock(Math::VectorList<N, T> list,
                      BlockType b = ARRAY, UpdateMode u = STATIC)
                : IDataBlock(list.GetSize(), list.GetData(), b, u) {
                vectorlist = list;
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

                vectorlist = Math::VectorList<N, T>((T*)this->data, this->size);
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
                    vectorlist = Math::VectorList<N, T>();
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

            void GetElement(unsigned int i, Math::Vector<2, float> &element){
                Math::Vector<N, T> vec = vectorlist.GetElement(i);
                element[0] = vec.Get(0);
                element[1] = (N >= 2) ? vec.Get(1) : 0;
            }
            void GetElement(unsigned int i, Math::Vector<3, float> &element){
                Math::Vector<N, T> vec = vectorlist.GetElement(i);
                element[0] = vec.Get(0);
                if (N >= 2) element[1] = vec.Get(1);
                if (N >= 3) element[2] = vec.Get(2);
            }
            void GetElement(unsigned int i, Math::Vector<4, float> &element){
                Math::Vector<N, T> vec = vectorlist.GetElement(i);
                element[0] = vec.Get(0);
                if (N >= 2) element[1] = vec.Get(1);
                if (N >= 3) element[2] = vec.Get(2);
                if (N >= 4) element[3] = vec.Get(3);
            }

            /**
             * Gets the i'th element in the data block.
             */
            inline Math::Vector<N, T> GetElement(unsigned int i) const {
                return vectorlist.GetElement(i);
            }
            inline Math::Vector<N, T> operator[](const unsigned int i){
                return GetElement(i);
            }

            void SetElement(unsigned int i, Math::Vector<2, float> value){
                Math::Vector<N, T> vec;
                vec[0] = value.Get(0);
                if (N >= 2) vec[1] = value.Get(1);
                vectorlist.SetElement(i, vec);
            }
            void SetElement(unsigned int i, Math::Vector<3, float> value){
                Math::Vector<N, T> vec;
                vec[0] = value.Get(0);
                if (N >= 2) vec[1] = value.Get(1);
                if (N >= 3) vec[2] = value.Get(2);
                vectorlist.SetElement(i, vec);
            }
            void SetElement(unsigned int i, Math::Vector<4, float> value){
                Math::Vector<N, T> vec;
                vec[0] = value.Get(0);
                if (N >= 2) vec[1] = value.Get(1);
                if (N >= 3) vec[2] = value.Get(2);
                if (N >= 4) vec[3] = value.Get(3);
                vectorlist.SetElement(i, vec);
            }

            /**
             * Returns an iterator referring to the first element in
             * the data block.
             */
            inline Math::VectorIterator<N, T> Begin() const {
                return vectorlist.Begin();
            }

            /**
             * Returns an iterator referring to the last element in
             * the data block.
             */
            inline Math::VectorIterator<N, T> End() const {
                return vectorlist.End();
            }

            std::string ToString(){
                return vectorlist.ToString();
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
