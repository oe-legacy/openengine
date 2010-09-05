// Math vector.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
// --------------------------------------------------------------------

#ifndef _OE_VECTOR_H_
#define _OE_VECTOR_H_

#include <Math/Exceptions.h>

#include <string>
#include <sstream>
#include <ostream>
#include <math.h>
#include <boost/static_assert.hpp>

namespace OpenEngine {
namespace Math {

/**
 * Vector.
 *
 * @class Vector Vector.h Math/Vector.h
 * @param N Number of elements
 * @param T Type of elements
 */
template <unsigned int N, class T>
class Vector {
protected:
    // vector elements
    T elm[N];

public:
    /**
     * Create zero vector.
     * @code
     * Vector<3,int> v;   // [0, 0, 0]
     * @endcode
     */
    Vector() {
        for (unsigned int i=0; i<N; i++)
            elm[i] = 0;
    }
    /**
     * Create vector from scalar.
     * @code
     * Vector<3,int> v(7);   // [7, 7, 7]
     * @endcode
     *
     * @param s Scalar value in all indexes
     */
    explicit Vector(const T s) {
        for (unsigned int i=0; i<N; i++)
            elm[i] = s;
    }
    /**
     * Copy constructor.
     *
     * @param v Vector to copy
     */
    Vector(const Vector<N,T>& v) {
        for (unsigned int i=0;i<N;i++)
            elm[i] = v.elm[i];
    }
    Vector<N,T>& operator=(const Vector<N,T>& other) {
        if (this != &other) {
            for (unsigned int i=0; i<N; i++)
                elm[i] = other.elm[i];
        }

        return *this;
    }
    /**
     * Create vector from array.
     *
     * @param a Array to copy
     */
    explicit Vector(const T a[N]) {
        for (unsigned int i=0; i<N; i++)
            elm[i] = a[i];
    }
    /**
     * Constructor for a 2 element vector.
     */
    Vector(const T x, const T y) {
        BOOST_STATIC_ASSERT(N==2);
        elm[0]=x; elm[1]=y;
    }
    /**
     * Constructor for a 3 element vector.
     */
    Vector(const T x, const T y, const T z) {
        BOOST_STATIC_ASSERT(N==3);
        elm[0]=x; elm[1]=y; elm[2]=z;
    }
    /**
     * Constructor for a 4 element vector.
     */
    Vector(const T x, const T y, const T z, const T w) {
        BOOST_STATIC_ASSERT(N==4);
        elm[0]=x; elm[1]=y; elm[2]=z; elm[3]=w;
        
    }
    /**
     * Index access to vector elements.
     * @code
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * v[1]                      // 2
     * @endcode
     *
     * @param i Index of element to return
     * @exception IndexOutOfBounds Index is out of bounds.
     * @return Element at index \a i
     */
    inline T& operator[](const unsigned int i) {
#if OE_SAFE
        if (i >= N)
            throw IndexOutOfBounds(i,0,N);
#endif
        return elm[i];
    }
    /**
     * Vector equality.
     */
    bool operator==(const Vector<N,T>& v) const {
        for (unsigned int i=0; i<N; i++)
            if (elm[i] != v.elm[i])
                return false;
        return true;
    }
    /**
     * Vector inequality.
     */
    bool operator!=(const Vector<N,T>& v) const {
        return !(*this == v);
    }
    /**
     * Scalar addition. 
     * This is a commutative operation.
     *
     * @code
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * v + 10                    // [11, 12, 13]
     * 10 + v                    // [11, 12, 13]
     * @endcode
     */
    const Vector<N,T> operator+(const T s) const {
        Vector<N,T> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = elm[i] + s;
        return v;
    }
    /**
     * Vector addition.
     * @code
     * Vector<3,int> u(1,2,3);   // [1, 2, 3]
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * u + v                     // [2, 4, 6]
     * @endcode
     */
    const Vector<N,T> operator+(const Vector<N,T>& v) const {
        Vector<N,T> t;
        for (unsigned int i=0; i<N; i++)
            t[i] = elm[i] + v.elm[i];
        return t;
    }
    /**
     * Scalar subtraction.
     *
     * @code
     * Vector<3,int> v(1,2,3);   // [11, 12, 13]
     * v - 10                    // [1, 2, 3]
     * @endcode
     */
    const Vector<N,T> operator-(const T s) const {
        Vector<N,T> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = elm[i] - s;
        return v;
    }
    /**
     * Vector subtraction.
     * @code
     * Vector<3,int> u(1,2,3);   // [2, 4, 6]
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * u - v                     // [1, 2, 3]
     * @endcode
     */
    const Vector<N,T> operator-(const Vector<N,T>& v) const {
        Vector<N,T> t;
        for (unsigned int i=0; i<N; i++)
            t[i] = elm[i] - v.elm[i];
        return t;
    }
    /**
     * Scalar multiplication.
     * @code
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * v * 10                    // [10, 20, 30]
     * @endcode
     */
    const Vector<N,T> operator*(const T s) const {
        Vector<N,T> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = elm[i] * s;
        return v;
    }
    /**
     * Scalar division.
     * @code
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * v / 10                    // [0.5, 1.0, 1.5]
     * @endcode
     *
     * @todo What should the type of the returning vector be?
     *
     * @param s Scalar to divide by.
     * @exception DivisionByZero Cannot divide by a zero scalar.
     * @return Vector where all elements are divided by \a s
     */
    const Vector<N,T> operator/(const T s) const {
#if OE_SAFE
        if (s == 0)
            throw DivisionByZero();
#endif
        Vector<N,T> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = (T)elm[i] / s;
        return v;
    }
    /**
     * Additive inverse.
     * @code
     * Vector<3,int> u(1,2,3);   // [ 1,  2,  3]
     * -u                        // [-1, -2, -3]
     * @endcode
     */
    const Vector<N,T> operator-() const {
        return *this * -1;
    }
    /**
     * Dot/scalar product
     * @code
     * Vector<3,int> u(1,2,3);   // [1, 2, 3]
     * Vector<3,int> v(1,2,3);   // [1, 2, 3]
     * u * v                     // 14
     * @endcode
     */
    const T operator*(const Vector<N,T>& v) const {
        T s = 0;
        for (unsigned int i=0; i<N; i++)
            s += elm[i] * v.elm[i];
        return s;
    }
    /**
     * Cross/vector/outer product.
     *
     * @note Must be two vectors in R3.
     *
     * @code
     * Vector<3,int> u(1,2,3);   // [1, 2, 3]
     * Vector<3,int> v(1,2,3);   // [3, 2, 1]
     * u % v                     // [-4, 8, -4]
     * @endcode
     *
     * @return The perpendicular vector
     */
    const Vector<N,T> operator%(const Vector<N,T>& v) const {
        BOOST_STATIC_ASSERT(N==3);
        Vector<N,T> a;
        a[0] = elm[1]*v.elm[2] - elm[2]*v.elm[1];
        a[1] = elm[2]*v.elm[0] - elm[0]*v.elm[2];
        a[2] = elm[0]*v.elm[1] - elm[1]*v.elm[0];
        return a;
    }
    /**
     * Destructive scalar addition.
     */
    void operator+=(const T s) {
        for (unsigned int i=0; i<N; i++)
            elm[i] += s;
    }
    /**
     * Destructive vector addition.
     */
    void operator+=(const Vector<N,T>& v) {
        for (unsigned int i=0; i<N; i++)
            elm[i] += v.Get(i);
    }
    /**
     * Destructive scalar multiplication.
     */
    void operator*=(const T s) {
        for (unsigned int i=0; i<N; i++)
            elm[i] *= s;
    }
    /**
     * Destructive scalar subtraction.
     */
    void operator-=(const T s) {
        for (unsigned int i=0; i<N; i++)
            elm[i] -= s;
    }
    /**
     * Destructive scalar division.
     *
     * @param s Scalar to divide by.
     * @exception DivisionByZero Cannot divide by a zero scalar.
     * @return Vector where all elements are divided by \a s
     */
    void operator/=(const T s) {
#if OE_SAFE
        if (s == 0)
            throw DivisionByZero();
#endif
        for (unsigned int i=0; i<N; i++)
            elm[i] /= s;
    }
    /**
     * Is this the zero vector.
     *
     * @return True if all elements are zero, false otherwise.
     */
    bool IsZero() const {
        for (unsigned int i=0; i<N; i++)
            if (elm[i] != 0) return false;
        return true;
    }
    /**
     * Length/modulo of vector.
     *
     * @return Vector length
     */
    float GetLength() const {
        return sqrt((float) ((*this) * (*this)));
    }
    /**
     * Length/modulo squared of vector.
     *
     * @return Vector length squared
     */
    float GetLengthSquared() const {
        return (float) ((*this) * (*this));
    }
    /**
     * Normalized vector.
     *
     * @return Normalized vector
     */
    Vector<N,T> GetNormalize() const {
        Vector<N,T> v (*this);
        v.Normalize();
        return v;
    }
    /**
     * Destructively Normalize vector.
     *
     * @exception ArithmeticException Normalizing zero vector
     */
    void Normalize() {
        float norm = GetLength();
#if OE_SAFE
        if (norm == 0)
            throw ArithmeticException("Can not normalize the zero vector.");
#endif
        for (unsigned int i=0; i<N; i++)
            if( elm[i] != 0 )
	        elm[i] = (T)( ((float)elm[i])/norm );
    }
    /**
     * Distance between two vectors.
     * @note Must be two vectors in R3.
     *
     * @return The length between the two vectors
     */
    float Distance( Vector<3,T> v ) {
        return (*this-v).GetLength();
    }
    /**
     * Maximum element value.
     */
    T Max() const {
        T m = elm[0];
        for (unsigned int i=1; i<N; i++)
            if (elm[i] > m) m = elm[i];
        return m;
    }
    /**
     * Minimum element value.
     */
    T Min() const {
        T m = elm[0];
        for (unsigned int i=1; i<N; i++)
            if (elm[i] < m) m = elm[i];
        return m;
    }
    /**
     * Index of maximum element value.
     */
    unsigned int MaxIndex() const {
      unsigned int m = 0;
        for (unsigned int i=1; i<N; i++)
            if (elm[i] > elm[m]) m = i;
        return m;
    }
    /**
     * Index of minimum element value.
     */
    unsigned int MinIndex() const {
        int m = 0;
        for (unsigned int i=1; i<N; i++)
            if (elm[i] < elm[m]) m = i;
        return m;
    }
    /**
     * Sum of elements.
     *
     * @return Sum of elements
     */
    T Sum() const {
        T s = 0;
        for (unsigned int i=0; i<N; i++)
            s += elm[i];
        return s;
    }
    /**
     * Get vector with integer entries.
     *
     * @return Vector of integers.
     */
    Vector<N,int> ToInt() const {
        Vector<N,int> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = (int)elm[i];
        return v;
    }
    /**
     * Get vector with floating point entries.
     *
     * @return Vector of floats.
     */
    Vector<N,float> ToFloat() const {
        Vector<N,float> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = (float)elm[i];
        return v;
    }
    /**
     * Get vector with double precision entries.
     *
     * @return Vector of doubles.
     */
    Vector<N,double> ToDouble() const {
        Vector<N,double> v;
        for (unsigned int i=0; i<N; i++)
            v[i] = (double)elm[i];
        return v;
    }
    /**
     * Create array from vector.
     *
     * @param a Array to populate
     */
    void ToArray(T a[N]) const {
        for (unsigned int i=0; i<N; i++)
            a[i] = elm[i];
    }
    /**
     * Returns a pointer directly into the vectors data core.
     *
     * @return The data pointer.
     */
    inline T* ToArray() const {
        return (T*)elm;
    }
    /**
     * String representation.
     * Ex. [1, 2, 3]
     *
     * @return Vector as string
     */
    std::string ToString() const {
        std::ostringstream out;
        //out.width(6);
        out << "[";
        for (unsigned int i=0;i+1<N;i++)
            out << elm[i] << ", ";
        out << elm[N-1] << "]";
        return out.str();
    }
    /**
     * Get value of index (non modifiable).
     * 
     * @param i Index of element to return
     * @exception IndexOutOfBounds Index is out of bounds.
     * @return Element at index \a i
     */
    T Get(const unsigned int i) const { 
#if OE_SAFE
        if (i >= N)
            throw IndexOutOfBounds(i,0,N);
#endif
        return elm[i]; 
    }
    

};

/**
 * Commutative vector/scalar addition.
 *
 * @see Vector::operator+
 */
template <unsigned int N, class T>
const Vector<N,T> operator+(const T s, const Vector<N,T>& e) {
    return e + s;
}

/**
 * Commutative vector/scalar multiplication.
 *
 * @see Vector::operator*
 */
template <unsigned int N, class T>
const Vector<N,T> operator*(const T s, const Vector<N,T>& e) {
    return e * s;
}

/**
 * Scalar/vector division.
 *
 * @see Vector::operator/
 */
template <unsigned int N, class T>
const Vector<N,T> operator/(const T s, const Vector<N,T>& e) {
    Vector<N, T> ret;
    for (unsigned int i=0; i<N; i++)
        ret[i] = s / e.Get(i);
    return ret;
}

/**
 * Stream operator to ease the use of ToString method.
 */
template <unsigned int N, class T>
std::ostream& operator<<(std::ostream& os, const Vector<N,T> e) {
    os<<e.ToString();
    return os;
}

}  // NS OpenEngine
}  // NS Math

#endif // _OE_VECTOR_H_
