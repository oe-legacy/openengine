/**
 * Second order tensor in three dimensions.
 *
 * @class Tensor Tensor.h th/Tensor.h
 */

#ifndef _TENSOR_H_
#define _TENSOR_H_

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include "eig3.h"

#include <stdio.h>

using namespace std;

namespace OpenEngine {
namespace Math {

/**
 * Second order Tensor.
 *
 * @class Tensor Tensor.h
 * @param N Number of rows
 * @param M Number of columns
 * @param T Type of element
 */
template<int N, int M, class T>
class Tensor {
private:
    T elm[N*M];
    
    // Array of eigenvalues - only 3x3 tensors are supported.
    double eigenValue[3];
    // Each row in the matrix corresponds to 
    Matrix<3,3,float> eigenVector;


public:
    /**
     * Default constructor.
     * Creates the identity tensor.
     */
    Tensor() {
        // Iterate over rows
        for( int i=0; i<N; i++)
            // Iterate over columns
            for( int j=0; j<M; j++ )
                if( i==j ) 
                    elm[j+(i*N)] = 1;
                else
                    elm[j+(i*N)] = 0;
    }
    
    Tensor(const Tensor<N, M, T>& t) {
        for (int i=0; i<N*M; i++)
            elm[i] = t.elm[i];  
    }


    Tensor(const Vector<M,T>& v0, const Vector<M,T>& v1, const Vector<M,T>& v2) {
    }

    /**
     * Returns true if the tensor is symmetric, false otherwise.
     *
     */
    bool isSymmetric() {
         // Iterate over rows
        for( int i=0; i<N; i++)
            // Iterate over columns
            for( int j=0; j<M; j++ )
                if( (*this)[i][j] != (*this)[j][i] )
                    return false;
        return true;
    }

    /**
     * Get tensor row vector
     * @see GetRow()
     * @param i Row index
     * @return Row vector
     */
    Vector<N,T> operator[](const int i) {
        return GetRow(i);
    }
 
    T& operator()(const int i, const int j) {
        return elm[j+(i*N)];
    }

    /**
     * Get tensor row vector.
     * @code
     * Tensor<3,3,int> t();   
     * t = [ 1, 0, 0
     *       0, 1, 0
     *       0, 0, 1 ]
     *
     * t[1] = [0, 1, 0]
     * @endcode
     */
    Vector<M,T> GetRow(const int i) const {
        Vector<M,T> row;
        for(int j=0; j<M; j++)
            row[j] = elm[j+(M*i)];
        return row;
    }


    /**
     * Set row vector into tensor
     *
     */
    void setRow(const int i, const Vector<M,T> v) {
        for(int j=0; j<M; j++)
            elm[j+(i*M)] = v.Get(j);
    }

    /**
     * Get tensor column vector 
     *
     */
    Vector<N,T> GetColumn(const int i) const {
       Vector<N,T> col;
        for(int j=0; j<N; j++)
            col[j] = elm[(j*M)+i];
        return col;    
    }

    /**
     * Set tensor column vector 
     *
     */
    void SetColumn(const int i, const Vector<N,T> v) {
        for(int j=0; j<N; j++)
            elm[j*M+i] = v.Get(j);
    }

    /**
     * Tensor addition.
     * Let S and T be two tensors. Then U = S + T is also a tensor.
     */
    Tensor<N,M,T> operator+(const Tensor<N,M,T> t) {
        Tensor<N,M,T> res;
        for(int i=0; i<(N*M); i++)
            res.elm[i] = elm[i] + t.elm[i];
        return res;
    }

    /**
     * Product of a tensor and a vector.
     * Let v be a vector and S a second order tensor. Then u = S * v
     * is a vector.  
     */
    const Vector<N,T> operator*(const Vector<N,T> v) {
        Tensor<N,M,T> S = (*this);
        return Vector<N,T>(S[0]*v, S[1]*v, S[2]*v);
    }

    /**
     * Product of two tensors.
     * Let T and S be two second order tensors. Then U = T * S is also
     * a tensor. Multiply rows with columns, T and S must have equal dim.
     */
    const Tensor<N,M,T> operator*(const Tensor<N,M,T> t) {
        Tensor<N,M,T> res;
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                res(i,j) = GetRow(i) * t.GetColumn(j);
        return res;
    }

    /**
     * Get transposed of tensor, none destructive.
     *
     */
    const Tensor<N,M,T> GetTransposed() {
    }

    /**
     * Destructive transpose of the tensor.
     *
     */
    void Transpose() {
    }

    /**
     * Trace is the sum of the diagonal elements.
     *
     */
    const T trace() {
        T sum = 0;
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                if( i==j) 
                    sum += elm[j+(i*M)];
        return sum;
    }


    /**
     * Computes the eigenvectors and eigenvalues of a symmetric 3x3
     * tensor. Get the results using eigenVectors() and eigenValues(). 
     * This needs to be re-calculated if the tensor changes.
     *
     * @see eigenValues()
     * @see eigenVectors()
     */
    void eigenVectorsAndValues() {
        double A[N][M];
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                A[i][j] = elm[j+i*N];
                printf("%f ", A[i][j]);
            }
            printf("\n");
        }

        double V[N][M];
        double d[3];
        eigen_decomposition(A,V,d);
      
    }
    
    /**
     * Calculates the eigen values of the tensor and
     * returns each eigen value as a component in the vector.
     */
    const Vector<N,double> eigenValues() {
        //return Vector<N,double>(d[0],d[1],d[2]);
        return Vector<N,double>();
    }


    /**
     * 
     *
     */
    

    

};

} // NS Math
} // NS OpenEngine

#endif
