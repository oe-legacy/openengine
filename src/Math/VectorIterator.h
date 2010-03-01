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
#include <Logging/Logger.h>

namespace OpenEngine {
    namespace Math {
        
        template <unsigned int N, class T>
        class VectorIterator : public Vector<N, T> {
        protected:
            T* begin;
            T* end;
            
        public:
            /**
             * Create the iterator as a subclass for direct access?
             * Or make it stand alone and overload it's = operator?
             */

            VectorIterator(T* begin, unsigned int size){
                this->elm = begin;
                this->begin = begin;
                this->end = begin + size * N;
            }

            VectorIterator(unsigned int size, T* end){
                this->elm = begin;
                this->begin = end - size * N;
                this->end = end;
            }

            inline bool HasPrevious() const {
                return this->elm != begin;
            }

            inline bool HasNext() const {
                return this->elm != end;
            }
            
            inline VectorIterator<N, T> JumpTo(const unsigned int i){
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

            inline VectorIterator<N, T> operator=(VectorIterator<N,T> other) {
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

    }
}

#endif
