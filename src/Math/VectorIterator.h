// Vector Iterator.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _OE_VECTOR_ITERATOR_H_
#define _OE_VECTOR_ITERATOR_H_

#include <Math/Vector.h>

namespace OpenEngine {
    namespace Math {
        
        template <unsigned int N, class T>
        class VectorIterator : public Vector<N, T> {
        protected:
            unsigned int size;
            T* begin;
            T* end;
            
            VectorIterator(unsigned int size, T* end){
                this->size = size;
                this->elm = begin;
                this->begin = end - size * N;
                this->end = end;
            }

        public:
            VectorIterator(T* begin, unsigned int size){
                this->size = size;
                this->elm = begin;
                this->begin = begin;
                this->end = begin + size * N;
            }

            inline VectorIterator<N, T> Begin() const {
                return VectorIterator<N, T>(begin, size);
            }

            inline VectorIterator<N, T> End() const {
                return VectorIterator<N, T>(size, end);
            }

            inline bool HasPrevious() const {
                return this->elm != begin;
            }

            inline bool HasNext() const {
                return this->elm != end;
            }
            
            inline VectorIterator<N, T> operator++() {
#ifdef OE_SAFE
                if (!HasNext())
                    throw IndexOutOfBounds(size, 0, size);
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
                    throw IndexOutOfBounds(size, 0, size);
#endif
                this->elm -= N;
                return *this;
            }

            inline VectorIterator<N, T> Previous() {
                return --(*this);
            }

            inline VectorIterator<N, T> operator=(Vector<N,T> other) {
                for (unsigned int i = 0; i < N; ++i)
                    this->elm[i] = other[i];
                return *this;
            }
            
            inline bool operator==(VectorIterator<N, T> other) const {
                return this->elm == other.elm;
                /*
                  begin == other.begin && 
                  end == other.end;
                */
            }
            
            // operators that needs implementing != ==
  
        };

    }
}

#endif
