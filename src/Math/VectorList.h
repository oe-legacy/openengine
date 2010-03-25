// Vector container.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_VECTOR_LIST_H_
#define _OE_VECTOR_LIST_H_

#include <Math/Vector.h>
#include <Utils/Convert.h>

namespace OpenEngine {
    namespace Math {

        template <unsigned int N, class T>
        class VectorIterator : public Vector<N, T> {
        protected:
            T* begin;
            T* end;

        public:
            VectorIterator(T* begin, unsigned int size){
                this->elm = begin;
                this->begin = begin;
                this->end = begin + size * N;
            }

            /**
             * Copy constructor.
             */
            VectorIterator(const VectorIterator<N, T>& itr){
                this->elm = itr.elm;
                this->begin = itr.begin;
                this->end = itr.end;
            }

            inline bool HasPrevious() const {
                return this->elm != begin;
            }

            inline bool HasNext() const {
                return this->elm != end;
            }
            
            inline VectorIterator<N, T> JumpToElement(const unsigned int i){
                this->elm = begin + i * N;
#ifdef OE_SAFE
                if (this->elm >= end)
                    throw Exception("Exceeding the last element in the iterator.");
#endif
                return *this;
            }

            inline VectorIterator<N, T> operator++() {
#ifdef OE_SAFE
                if (!HasNext())
                    throw Exception("Exceeding the last element in the iterator.");
#endif
                this->elm += N;
                return *this;
            }
          
            inline VectorIterator<N, T> Next() {
                return ++(*this);
            }

            inline VectorIterator<N, T> operator--() {
#ifdef OE_SAFE
                if (!HasPrevious())
                    throw Exception("Subceeding the first element in the iterator.");
#endif
                this->elm -= N;
                return *this;
            }

            inline VectorIterator<N, T> Previous() {
                return --(*this);
            }

            inline VectorIterator<N, T> operator=(const Vector<N,T>& other) {
                for (unsigned int i = 0; i < N; ++i)
                    this->elm[i] = other.Get(i);
                return *this;
            }

            inline VectorIterator<N, T> operator=(const VectorIterator<N,T>& other) {
                this->elm = other.elm;
                this->begin = other.begin;
                this->end = other.end;
                return *this;
            }
            
            inline bool operator==(const VectorIterator<N, T>& other) const {
                return this->elm == other.elm;
            }

            inline bool operator==(const Vector<N, T>& other) const {
                for (unsigned int i=0; i<N; i++)
                    if (this->elm[i] != other.Get(i))
                        return false;
                return true;
            }
            
            inline bool operator!=(const VectorIterator<N, T>& other) const {
                return this->elm != other.elm;
            }

            inline bool operator!=(const Vector<N, T>& other) const {
                return !(*this == other);
            }

        };


        template <int N, class T>
        class VectorList {
        protected:
            T* data;
            unsigned int size;
        public:
            VectorList()
                : data(NULL), size(0) { }

            VectorList(T* data, unsigned int size)
                : data(data), size(size) { }

            /**
             * Get pointer to the data array.
             */
            inline T* GetData() const {
                return data;
            }

            /**
             * Gets the i'th vector element in the list.
             */
            inline Vector<N, T> GetElement(unsigned int i) const {
                unsigned int index = i * N;
                return Vector<N, T>(data + index);
            }
            inline Vector<N, T> operator[](const unsigned int i){
                return GetElement(i);
            }

            /**
             * Sets the i'th element in the list to the values in vector.
             *
             * @param value The value to be set to.
             */
            inline void SetElement(unsigned int i, Vector<N, T> vector){
#ifdef OE_SAFE
                if (i > size)
                    throw Exception("Element index " + 
                                    OpenEngine::Utils::Convert::ToString<unsigned int>(i) + 
                                    " too high.");
#endif
                T* offset = data + i * N;
                for (unsigned int j = 0; j < N; ++j)
                    offset[j] = vector[j];
            }
           
            /**
             * Returns an iterator referring to the first element in
             * the buffer object.
             */
            inline VectorIterator<N, T> Begin() const {
                return VectorIterator<N, T>(data, size);
            }

            /**
             * Returns an iterator referring to the last element in
             * the buffer object.
             */
            inline VectorIterator<N, T> End() const {
                return VectorIterator<N, T>(data, size).JumpToElement(size-1);
            }
        };
            
    }
}

#endif
