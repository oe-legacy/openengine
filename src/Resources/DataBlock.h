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
        protected:
            VectorList<N, T> vectorlist;

        public:
            DataBlock(unsigned int s = 0, T* d = NULL,
                      BlockType b = ARRAY, UpdateMode u = STATIC)
                : IDataBlock(s, d, b, u) {
                if (d == NULL)
                    this->data = new T[N * s];
                vectorlist = VectorList<N, T>((T*)this->data, s);
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            DataBlock(VectorList<N, T> list,
                      BlockType b = ARRAY, UpdateMode u = STATIC)
                : IDataBlock(list.GetSize(), list.GetData(), b, u) {
                vectorlist = list;
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            ~DataBlock(){
                if (this->data)
                    delete [] (T*) this->data;
            }

            /**
             * Unloads the data array.
             */
            void Unload() {
                if (this->data){
                    delete [] (T*) this->data;
                    this->data = NULL;
                    vectorlist = VectorList<N, T>();
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

            void* GetVoidElement(unsigned int i) {
                return ((T*) this->data) + N * i;
            }

            /**
             * Gets the i'th element in the data block.
             */
            inline Vector<N, T> GetElement(unsigned int i) const {
                return vectorlist.GetElement(i);
            }
            inline Vector<N, T> operator[](const unsigned int i){
                return GetElement(i);
            }

            /**
             * Sets the i'th element in the data block to the vector.
             *
             * @param value The value to be set to.
             */
            inline void SetElement(unsigned int i, Vector<N, T> value){
                vectorlist.SetElement(i, value);
            }
           
            /**
             * Returns an iterator referring to the first element in
             * the data block.
             */
            inline VectorIterator<N, T> Begin() const {
                return vectorlist.Begin();
            }

            /**
             * Returns an iterator referring to the last element in
             * the data block.
             */
            inline VectorIterator<N, T> End() const {
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
