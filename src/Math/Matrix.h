// Math matrix
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _OE_MATRIX_H_
#define _OE_MATRIX_H_

#include <string>
#include <sstream>
#include <boost/static_assert.hpp>

#include <Math/Vector.h>

namespace OpenEngine {
namespace Math {

/**
 * Matrix.
 *
 * @class Matrix Matrix.h Math/Matrix.h
 * @param M Number of rows
 * @param N Number of columns
 * @param T Type of elements
 */
template <unsigned int M, unsigned int N, class T>
class Matrix {
private:
    // matrix elements
    T elm[M][N];

public:
    /**
     * Create identity matrix.
     * If the dimension is not NxN zero-rows will appear.
     *
     * @code
     * Matrix<3,3,int> m;   // [(1, 0, 0), (0, 1, 0), (0, 0, 1)]
     * @endcode
     */
    Matrix() {
        for (unsigned int i=0; i<M; i++)
            for (unsigned int j=0; j<N; j++)
                elm[i][j] = (i==j)?(T)1:(T)0;
    }
    /**
     * Create matrix from scalar.
     * @code
     * Matrix<2,3,int> m(7);   // [(7, 7, 7), (7, 7, 7)]
     * @endcode
     *
     * @param s Scalar value in all indexes
     */
    explicit Matrix(const T s) {
        for (unsigned int i=0; i<M; i++)
            for (unsigned int j=0; j<N; j++)
                elm[i][j] = s;
    }
    /**
     * Copy constructor.
     *
     * @param m Matrix to copy
     */
    Matrix(const Matrix<M,N,T>& m) {
        for (unsigned int i=0; i<M; i++)
            for (unsigned int j=0; j<N; j++)
                elm[i][j] = m.elm[i][j];
    }
    /**
     * Create matrix form array.
     *
     * @param a Array to create from
     */
    explicit Matrix(const T a[M*N]) {
        for (unsigned int i=0; i<M; i++)
            for (unsigned int j=0; j<N; j++)
                elm[i][j] = a[i*N + j];
    }
    /**
     * Create a Mx3 matrix from 3 M-length vectors.
     */
    Matrix(const Vector<M,T> x, const Vector<M,T> y, const Vector<M,T> z) {
        BOOST_STATIC_ASSERT(N==3);
        x.ToArray(elm[0]);
        y.ToArray(elm[1]);
        z.ToArray(elm[2]);
    }
    /**
     * Constructor for a 2x2 matrix.
     */
    Matrix(const T a, const T b, const T c, const T d) {
        BOOST_STATIC_ASSERT(M==2 && N==2);
        elm[0][0]=a; elm[0][1]=b;
        elm[1][0]=c; elm[1][1]=d;
    }
    /**
     * Matrix-Vector multiplication. 2*2 matrices only.
     */
    const Vector<2,T> operator*(const Vector<2,T> v) {
        BOOST_STATIC_ASSERT(M==2 && N==M);
        Vector<2,T> r;
        r[0] = elm[0][0] * v.Get(0) + elm[0][1] * v.Get(1);
        r[1] = elm[1][0] * v.Get(0) + elm[1][1] * v.Get(1);
        return r;
    }
    /**
     * Matrix-Vector multiplication. 3*3 matrices only.
     */
    /**
     * Constructor for a 3x3 matrix.
     */
    Matrix(const T a, const T b, const T c, 
           const T d, const T e, const T f, 
           const T g, const T h, const T i) {
        BOOST_STATIC_ASSERT(M==3 && N==3);
        elm[0][0]=a; elm[0][1]=b; elm[0][2]=c;
        elm[1][0]=d; elm[1][1]=e; elm[1][2]=f;
        elm[2][0]=g; elm[2][1]=h; elm[2][2]=i;
    }
    /**
     * Constructor for a 4x4 matrix.
     */
    Matrix(const T a, const T b, const T c, const T d, 
           const T e, const T f, const T g, const T h,
           const T i, const T j, const T k, const T l, 
           const T o, const T p, const T q, const T r) {
        BOOST_STATIC_ASSERT(M==4 && N==4);
        elm[0][0]=a; elm[0][1]=b; elm[0][2]=c; elm[0][3]=d;
        elm[1][0]=e; elm[1][1]=f; elm[1][2]=g; elm[1][3]=h;
        elm[2][0]=i; elm[2][1]=j; elm[2][2]=k; elm[2][3]=l;
        elm[3][0]=o; elm[3][1]=p; elm[3][2]=q; elm[3][3]=r;
    }
    /**
     * Index access to matrix elements.
     * @code
     * Matrix<2,2,int> m(1,2, 3,4);   // [(1, 2), (3, 4)]
     * m(1,0)                         // 3
     * @endcode
     *
     * @param i Row index
     * @param j Column index
     * @return Element at index \a (i,j)
     */
    T& operator()(const unsigned int i, const unsigned int j) {
#if OE_SAFE
        if (i >= M)
            throw IndexOutOfBounds(i,0,M);
        if (j >= N)
            throw IndexOutOfBounds(j,0,N);
#endif
        return elm[i][j];
    }
    /**
     * Matrix equality.
     * True if all index element are identical.
     */
    bool operator==(const Matrix<M,N,T>& m) const {
        for (unsigned int i=0; i<M; i++)
            for (unsigned int j=0; j<N; j++)
                if (elm[i][j] != m.elm[i][j])
                    return false;
        return true;
    }
    /**
     * Matrix inequality.
     * True if one or more index elements differ.
     */
    bool operator!=(const Matrix<M,N,T>& m) const {
        return !(*this == m);
    }
    /**
     * Matrix multiplication.
     * @code
     * Matrix<2,2,int> a(1,2,3,4);     // [(1,  2), ( 3,  4)]
     * a * a;                          // [(7, 10), (15, 22)]
     * @endcode
     */
    Matrix<M,M,T> operator*(const Matrix<N,M,T> m) {
        Matrix<M,M,T> r;
        for (unsigned int i=0; i<M; i++) 
            for (unsigned int j=0; j<M; j++) {
                T s = 0;
                for (unsigned int t=0; t<N; t++)
                    s += elm[i][t] * m.elm[t][j];
                r.elm[i][j] = s;
            }
        return r;
    }
    /**
     * Matrix-Vector multiplication. 3*3 matrices only.
     */
    const Vector<3,T> operator*(const Vector<3,T> v) {
        BOOST_STATIC_ASSERT(M==3 && N==M);
        Vector<3,T> r;
        r[0] = elm[0][0] * v.Get(0) + elm[0][1] * v.Get(1) + elm[0][2] * v.Get(2);
        r[1] = elm[1][0] * v.Get(0) + elm[1][1] * v.Get(1) + elm[1][2] * v.Get(2);
        r[2] = elm[2][0] * v.Get(0) + elm[2][1] * v.Get(1) + elm[2][2] * v.Get(2);
        return r;
    }
    /**
     * Matrix-Vector multiplication of 4*4 matrices.
     */
    const Vector<4,T> operator*(const Vector<4,T> v) {
        BOOST_STATIC_ASSERT(M==4 && N==M);
        Vector<4,T> r;
        r[0] = elm[0][0] * v.Get(0) + elm[0][1] * v.Get(1) + elm[0][2] * v.Get(2) + elm[0][3] * v.Get(3);
        r[1] = elm[1][0] * v.Get(0) + elm[1][1] * v.Get(1) + elm[1][2] * v.Get(2) + elm[1][3] * v.Get(3);
        r[2] = elm[2][0] * v.Get(0) + elm[2][1] * v.Get(1) + elm[2][2] * v.Get(2) + elm[2][3] * v.Get(3);
        r[3] = elm[3][0] * v.Get(0) + elm[3][1] * v.Get(1) + elm[3][2] * v.Get(2) + elm[3][3] * v.Get(3);
        return r;
    }
    /**
     * Scalar mult
     */
    const Matrix<M,N,T> operator*(const T s) {
        Matrix<M,M,T> r;
        for (unsigned int i=0; i<M; i++) 
            for (unsigned int j=0; j<M; j++) {
                r.elm[i][j] = s*elm[i][j];
            }
        return r;
    }
    /**
     * Matrix addition.
     */
    const Matrix<M,N,T> operator+(Matrix<M,N,T> m) {
        Matrix<M,M,T> r;
        for (unsigned int i=0; i<M; i++) 
            for (unsigned int j=0; j<M; j++) {
                r.elm[i][j] = elm[i][j] + m[i][j];
            }
        return r;
    }
    /**
     * Get matrix row vector.
     * @code
     * Matrix<2,2,int> m(1,2, 3,4);   // [(1, 2), (3, 4)]
     * m[1]                           // [3, 4]
     * @endcode
     *
     * @see GetRow()
     * @param i Row index
     * @return Row vector
     */
    Vector<N,T> operator[](const unsigned int i) {
        return this->GetRow(i);
    }
    /**
     * Set matrix row vector.
     *
     * @param i Row index
     * @param r Row vector
     */
    void SetRow(const unsigned int i, const Vector<N,T> r) {
        r.ToArray(elm[i]);
    }
    /**
     * Get matrix row vector.
     *
     * @param i Row index
     * @return Row vector
     */
    Vector<N,T> GetRow(const unsigned int i) {
        return Vector<N,T>(elm[i]);
    }
    /**
     * Get matrix column vector.
     *
     * @param j Column index
     * @return Column vector
     */
    Vector<M,T> GetColumn(const unsigned int j) {
        Vector<M,T> v;
        for (int i=0; i<M; i++)
            v[i] = elm[i][j];
        return v;
    }
    /**
     * Matrix trace.
     * Only defined for NxN matrices.
     *
     * @return Sum of elements in the main diagonal
     */
    T Trace() {
        BOOST_STATIC_ASSERT(N==M);
        T t = 0;
        for (unsigned int i=0; i<M; i++)
            t += elm[i][i];
        return t;
    }
    /**
     * Transpose matrix.
     * Note that this is a destructive operation and only works on
     * square matrices.
     */
    void Transpose() {
        BOOST_STATIC_ASSERT(M==N);
        T tmp;
        for (unsigned int i=1; i<M; i++)
            for (unsigned int j=0; j<i; j++) {
                tmp = elm[i][j];
                elm[i][j] = elm[j][i];
                elm[j][i] = tmp;
            }
    }
    /**
     * Returns the transposed matrix.
     * NOTE: Only works on 3*3 matrices.
     */
    Matrix <M,N,T> GetTranspose() {
        BOOST_STATIC_ASSERT(M==N&&M==3);
        return Matrix<M,N,T>(elm[0][0],elm[1][0],elm[2][0],
                             elm[0][1],elm[1][1],elm[2][1],
                             elm[0][2],elm[1][2],elm[2][2]);
    }

    /**
     * Returns the determinant of a matrix.
     * Copied from:
     *     http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm     
     * look at ?    
     *     http://www.google.com/codesearch/p?hl=en&sa=N&cd=3&ct=rc#xrFFuTdR3w0/tulip-2.0.2/library/tulip/include/tulip/cxx/Matrix.cxx&q=matrix%20inverse%20lang:c%2B%2B&l=13
     */
    T GetDeterminant() const {

        switch (N) {
        case 2:
            return elm[0][0] * elm[1][1] - elm[1][0] * elm[0][1];
            break;
        case 3:
            return elm[0][0] * (elm[1][1]*elm[2][2] - elm[1][2] * elm[2][1])
                - elm[0][1] * (elm[1][0]*elm[2][2] - elm[1][2] * elm[2][0])
                + elm[0][2] * (elm[1][0]*elm[2][1] - elm[1][1] * elm[2][0]) ;
            break;
        case 4:

            T value;
            value =
                elm[0][3] * elm[1][2] * elm[2][1] * elm[3][0]-elm[0][2] * elm[1][3] * elm[2][1] * elm[3][0]-elm[0][3] * elm[1][1] * elm[2][2] * elm[3][0]+elm[0][1] * elm[1][3]    * elm[2][2] * elm[3][0]+
                elm[0][2] * elm[1][1] * elm[2][3] * elm[3][0]-elm[0][1] * elm[1][2] * elm[2][3] * elm[3][0]-elm[0][3] * elm[1][2] * elm[2][0] * elm[3][1]+elm[0][2] * elm[1][3]    * elm[2][0] * elm[3][1]+
                elm[0][3] * elm[1][0] * elm[2][2] * elm[3][1]-elm[0][0] * elm[1][3] * elm[2][2] * elm[3][1]-elm[0][2] * elm[1][0] * elm[2][3] * elm[3][1]+elm[0][0] * elm[1][2]    * elm[2][3] * elm[3][1]+
                elm[0][3] * elm[1][1] * elm[2][0] * elm[3][2]-elm[0][1] * elm[1][3] * elm[2][0] * elm[3][2]-elm[0][3] * elm[1][0] * elm[2][1] * elm[3][2]+elm[0][0] * elm[1][3]    * elm[2][1] * elm[3][2]+
                elm[0][1] * elm[1][0] * elm[2][3] * elm[3][2]-elm[0][0] * elm[1][1] * elm[2][3] * elm[3][2]-elm[0][2] * elm[1][1] * elm[2][0] * elm[3][3]+elm[0][1] * elm[1][2]    * elm[2][0] * elm[3][3]+
                elm[0][2] * elm[1][0] * elm[2][1] * elm[3][3]-elm[0][0] * elm[1][2] * elm[2][1] * elm[3][3]-elm[0][1] * elm[1][0] * elm[2][2] * elm[3][3]+elm[0][0] * elm[1][1]    * elm[2][2] * elm[3][3];
            return value;
   

        default:
            throw 42;
        }
    }


    Matrix<N,M,T> GetInverse() {
        //BOOST_STATIC_ASSERT(M==3&&N==3);
        
        T d = GetDeterminant();
        
        
        Matrix<M,N,T> b;

        switch (N) {
        case 3:

            b(0,0) = elm[1][1]*elm[2][2] - elm[1][2]*elm[2][1];
            b(0,1) = elm[0][2]*elm[2][1] - elm[0][1]*elm[2][2];
            b(0,2) = elm[0][1]*elm[1][2] - elm[0][2]*elm[1][1];

            b(1,0) = elm[1][2]*elm[2][0] - elm[1][0]*elm[2][2];
            b(1,1) = elm[0][0]*elm[2][2] - elm[0][2]*elm[2][0];
            b(1,2) = elm[0][2]*elm[1][0] - elm[0][0]*elm[1][2];

            b(2,0) = elm[1][0]*elm[2][1] - elm[1][1]*elm[2][0];
            b(2,1) = elm[0][1]*elm[2][0] - elm[0][0]*elm[2][1];
            b(2,2) = elm[0][0]*elm[1][1] - elm[0][1]*elm[1][0];
            break;
        case 4:
            b(0,0) = elm[1][2]*elm[2][3]*elm[3][1] - elm[1][3]*elm[2][2]*elm[3][1] + elm[1][3]*elm[2][1]*elm[3][2] - elm[1][1]*elm[2][3]*elm[3][2] - elm[1][2]*elm[2][1]*elm[3][3] + elm[1][1]*elm[2][2]*elm[3][3];
            b(0,1) = elm[0][3]*elm[2][2]*elm[3][1] - elm[0][2]*elm[2][3]*elm[3][1] - elm[0][3]*elm[2][1]*elm[3][2] + elm[0][1]*elm[2][3]*elm[3][2] + elm[0][2]*elm[2][1]*elm[3][3] - elm[0][1]*elm[2][2]*elm[3][3];
            b(0,2) = elm[0][2]*elm[1][3]*elm[3][1] - elm[0][3]*elm[1][2]*elm[3][1] + elm[0][3]*elm[1][1]*elm[3][2] - elm[0][1]*elm[1][3]*elm[3][2] - elm[0][2]*elm[1][1]*elm[3][3] + elm[0][1]*elm[1][2]*elm[3][3];
            b(0,3) = elm[0][3]*elm[1][2]*elm[2][1] - elm[0][2]*elm[1][3]*elm[2][1] - elm[0][3]*elm[1][1]*elm[2][2] + elm[0][1]*elm[1][3]*elm[2][2] + elm[0][2]*elm[1][1]*elm[2][3] - elm[0][1]*elm[1][2]*elm[2][3];
            b(1,0) = elm[1][3]*elm[2][2]*elm[3][0] - elm[1][2]*elm[2][3]*elm[3][0] - elm[1][3]*elm[2][0]*elm[3][2] + elm[1][0]*elm[2][3]*elm[3][2] + elm[1][2]*elm[2][0]*elm[3][3] - elm[1][0]*elm[2][2]*elm[3][3];
            b(1,1) = elm[0][2]*elm[2][3]*elm[3][0] - elm[0][3]*elm[2][2]*elm[3][0] + elm[0][3]*elm[2][0]*elm[3][2] - elm[0][0]*elm[2][3]*elm[3][2] - elm[0][2]*elm[2][0]*elm[3][3] + elm[0][0]*elm[2][2]*elm[3][3];
            b(1,2) = elm[0][3]*elm[1][2]*elm[3][0] - elm[0][2]*elm[1][3]*elm[3][0] - elm[0][3]*elm[1][0]*elm[3][2] + elm[0][0]*elm[1][3]*elm[3][2] + elm[0][2]*elm[1][0]*elm[3][3] - elm[0][0]*elm[1][2]*elm[3][3];
            b(1,3) = elm[0][2]*elm[1][3]*elm[2][0] - elm[0][3]*elm[1][2]*elm[2][0] + elm[0][3]*elm[1][0]*elm[2][2] - elm[0][0]*elm[1][3]*elm[2][2] - elm[0][2]*elm[1][0]*elm[2][3] + elm[0][0]*elm[1][2]*elm[2][3];
            b(2,0) = elm[1][1]*elm[2][3]*elm[3][0] - elm[1][3]*elm[2][1]*elm[3][0] + elm[1][3]*elm[2][0]*elm[3][1] - elm[1][0]*elm[2][3]*elm[3][1] - elm[1][1]*elm[2][0]*elm[3][3] + elm[1][0]*elm[2][1]*elm[3][3];
            b(2,1) = elm[0][3]*elm[2][1]*elm[3][0] - elm[0][1]*elm[2][3]*elm[3][0] - elm[0][3]*elm[2][0]*elm[3][1] + elm[0][0]*elm[2][3]*elm[3][1] + elm[0][1]*elm[2][0]*elm[3][3] - elm[0][0]*elm[2][1]*elm[3][3];
            b(2,2) = elm[0][1]*elm[1][3]*elm[3][0] - elm[0][3]*elm[1][1]*elm[3][0] + elm[0][3]*elm[1][0]*elm[3][1] - elm[0][0]*elm[1][3]*elm[3][1] - elm[0][1]*elm[1][0]*elm[3][3] + elm[0][0]*elm[1][1]*elm[3][3];
            b(2,3) = elm[0][3]*elm[1][1]*elm[2][0] - elm[0][1]*elm[1][3]*elm[2][0] - elm[0][3]*elm[1][0]*elm[2][1] + elm[0][0]*elm[1][3]*elm[2][1] + elm[0][1]*elm[1][0]*elm[2][3] - elm[0][0]*elm[1][1]*elm[2][3];
            b(3,0) = elm[1][2]*elm[2][1]*elm[3][0] - elm[1][1]*elm[2][2]*elm[3][0] - elm[1][2]*elm[2][0]*elm[3][1] + elm[1][0]*elm[2][2]*elm[3][1] + elm[1][1]*elm[2][0]*elm[3][2] - elm[1][0]*elm[2][1]*elm[3][2];
            b(3,1) = elm[0][1]*elm[2][2]*elm[3][0] - elm[0][2]*elm[2][1]*elm[3][0] + elm[0][2]*elm[2][0]*elm[3][1] - elm[0][0]*elm[2][2]*elm[3][1] - elm[0][1]*elm[2][0]*elm[3][2] + elm[0][0]*elm[2][1]*elm[3][2];
            b(3,2) = elm[0][2]*elm[1][1]*elm[3][0] - elm[0][1]*elm[1][2]*elm[3][0] - elm[0][2]*elm[1][0]*elm[3][1] + elm[0][0]*elm[1][2]*elm[3][1] + elm[0][1]*elm[1][0]*elm[3][2] - elm[0][0]*elm[1][1]*elm[3][2];
            b(3,3) = elm[0][1]*elm[1][2]*elm[2][0] - elm[0][2]*elm[1][1]*elm[2][0] + elm[0][2]*elm[1][0]*elm[2][1] - elm[0][0]*elm[1][2]*elm[2][1] - elm[0][1]*elm[1][0]*elm[2][2] + elm[0][0]*elm[1][1]*elm[2][2];
            
        }
        return b * (1.0/d);
    }
    

    /**
     * Get a matrix expanded by one column and one row.
     * The column and row will consist of zero elements and a one in
     * the diagonal entry.
     *
     * @code
     * Matrix<2,2,int> m(1,2, 3,4);  // [(1,2), (3,4)]
     * m.GetExpanded()               // [(1,2,0), (3,4,0), (0,0,1)]
     * @endcode
     *
     * @return Reduced matrix.
     */
    Matrix<M+1,N+1,T> GetExpanded() {
        Matrix<M+1,N+1,T> m;
        for (unsigned int i=0; i < M; i++)
            for (unsigned int j=0; j < N; j++)
                m(i,j) = elm[i][j];
        return m;
    }
    /**
     * Get a matrix reduced by one column and one row.
     *
     * @code
     * Matrix<3,3,int> m(1,2,3, 4,5,6, 7,8,9);  // [(1,2,3), (4,5,6), (7,8,9)]
     * m.GetReduced()                           // [(1,2), (4,5)]
     * @endcode
     *
     * @return Reduced matrix.
     */
    Matrix<M-1,N-1,T> GetReduced() {
        Matrix<M-1,N-1,T> m;
        for (unsigned int i=0; i < M-1; i++)
            for (unsigned int j=0; j < N-1; j++)
                m(i,j) = elm[i][j];
        return m;
    }
    /**
     * Create array of matrix.
     *
     * @param a Array to populate
     */
    void ToArray(T a[M*N]) const {
        for (unsigned int i=0; i<M; i++)
            for (unsigned int j=0; j<N; j++)
                a[i*N + j] = elm[i][j];
    }
    /**
     * String representation.
     * Ex. [(1, 2), (3, 4)]
     *
     * @return Matrix as string
     */
    std::string ToString() const {
        std::ostringstream out;
        out << "[";
        for (unsigned int i=0; i<M-1; i++) {
            out << "(";
            for (unsigned int j=0; j<N-1; j++)
                out << elm[i][j] << ", ";
            out << elm[i][N-1] << "), ";
        }
        out << "(";
        for (unsigned int j=0; j<N-1; j++)
            out << elm[M-1][j] << ", ";
        out << elm[M-1][N-1] << ")]";
        return out.str();
    }


    /**
     *
     *
     *
     */
    Matrix<M, N, T> Star(Vector <M, T> vec) {
      BOOST_STATIC_ASSERT(M==3 && N==3);
      return Matrix(0, -vec[2], vec[1],
		    vec[2], 0, -vec[0],
		    -vec[1], vec[0], 0);
    }

}; // Matrix

/**
 * Stream operator to ease the use of ToString method.
 */
template <unsigned int M, unsigned int N, class T>
std::ostream& operator<<(std::ostream& os, const Matrix<M,N,T> e) {
    os<<e.ToString();
    return os;
}

}  // NS OpenEngine
}  // NS Math

#endif // _OE_MATRIX_H_
