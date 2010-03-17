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
            DataBlock()
                : IDataBlock() {
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            DataBlock(T* d, unsigned int s)
                : IDataBlock(d, s) {
                vectorlist = VectorList<N, T>(d, s);
                this->dimension = N;
                this->type = GetResourceType<T>();
            }

            DataBlock(VectorList<N, T> list)
                : IDataBlock(list.GetData(), list.GetSize()) {
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

            /**
             * Gets the i'th element in the data block.
             */
            inline Vector<N, T> GetElement(unsigned int i) const {
                return vectorlist.GetElement(i);
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
             * the buffer object.
             */
            inline VectorIterator<N, T> Begin() const {
                return vectorlist.Begin();
            }

            /**
             * Returns an iterator referring to the last element in
             * the buffer object.
             */
            inline VectorIterator<N, T> End() const {
                return vectorlist.End();
            }
        };

        /**
         * Buffer Object smart pointer.
         */
        typedef boost::shared_ptr<DataBlock<2, float> > Float2DataBlockPtr;
        typedef boost::shared_ptr<DataBlock<3, float> > Float3DataBlockPtr;
        typedef boost::shared_ptr<DataBlock<4, float> > Float4DataBlockPtr;

        /**
         * Define special index block.
         */
        class DataIndices : public DataBlock<1, unsigned int> {
        public:
            DataIndices()
                : DataBlock<1, unsigned int>() {
                this->bufferType = INDEX_ARRAY;
            }

            DataIndices(unsigned int* d, unsigned int s)
                : DataBlock<1, unsigned int>(d, s) {
                this->bufferType = INDEX_ARRAY;
            }
        };
        typedef boost::shared_ptr<DataIndices > DataIndicesPtr;

    }
}

#endif
