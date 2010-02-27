// Test the math lib
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>

#include "testMath.h"

// include math lib
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>
#include <Math/VectorIterator.h>

#include <iostream>

using namespace OpenEngine::Math;

void OpenEngine::Tests::testVector() {
    // zero vector
    Vector<3,int> v0(0);
    BOOST_CHECK(v0[0]==0 && v0[1]==0 && v0[2]==0);
    // parameter creation
    Vector<3,int> v1(1,2,3);
    BOOST_CHECK(v1[0]==1 && v1[1]==2 && v1[2]==3);
    // copy creation
    Vector<3,int> v2(v1);
    BOOST_CHECK(v2[0]==1 && v2[1]==2 && v2[2]==3);
    // equality
    BOOST_CHECK(v1 == v2);
    // assignment on index and inequality
    v1[1] = 0;
    BOOST_CHECK(v1 != v2);
    // assignment on object
    v1 = v2;
    BOOST_CHECK(v1 == v2);
    // additive inverse
    BOOST_CHECK( -v1 == (Vector<3,int>(-1,-2,-3)));
    // scalar addition (commutative)
    BOOST_CHECK(v1 + 10 == (Vector<3,int>(11,12,13)));
    BOOST_CHECK(10 + v1 == (Vector<3,int>(11,12,13)));
    // scalar subtraction
    BOOST_CHECK( (Vector<3,int>(11,12,13)) - 10 == v1);
    // vector addition
    BOOST_CHECK(v1+v2 == (Vector<3,int>(2,4,6)));
    // vector subtraction
    BOOST_CHECK((Vector<3,int>(2,4,6))-v1 == v2);
    // scalar multiplication (commutative)
    BOOST_CHECK(v1*10 == (Vector<3,int>(10,20,30)));
    BOOST_CHECK(10*v1 == (Vector<3,int>(10,20,30)));
    // scalar division
    BOOST_CHECK(v1/2 == (Vector<3,float>(0.5,1.0,1.5)));
    // dot product
    BOOST_CHECK(v1*v2 == 14);
    // vector length
    BOOST_CHECK(v1.GetLength() <= 3.74167);
    BOOST_CHECK(v1.GetLength() >= 3.74165);
    // getNormalize vector
    BOOST_CHECK(fabs(v1.GetNormalize().GetLength() - 1.0) < 0.000001);
    // destructive Normalize vector
    Vector<3,float> vTmp = Vector<3,float>(v1[0],v1[1],v1[2]);
    vTmp.Normalize();
    BOOST_CHECK(fabs(vTmp.GetLength() - 1.0) < 0.000001);
    // Distance between two vectors
    BOOST_CHECK( v1.Distance(v1) == 0 );
    BOOST_CHECK( v1.Distance(v0) != 0 );
    BOOST_CHECK( (Vector<3,int>(3,4,0)).Distance(v0) == 5 );
    // cross product
    v2[0] = 3; v2[2] = 1;
    Vector<3,int> c(-4,8,-4);
    BOOST_CHECK(v1 % v2 == c);
    // array to vector
    float f1[] = {1,2,3};
    Vector<3,float> vf(f1);
    BOOST_CHECK( vf[0]==1 && vf[1]==2 && vf[2]==3 );
    // vector to array
    float f2[3];
    vf.ToArray(f2);
    BOOST_CHECK( f2[0]==1 && f2[1]==2 && f2[2]==3 );
    // max and min values and indexes
    BOOST_CHECK( v1.Max() == 3 );
    BOOST_CHECK( v1.Min() == 1 );
    BOOST_CHECK( v1.MaxIndex() == 2 );
    BOOST_CHECK( v1.MinIndex() == 0 );
    // destructive tests
    Vector<3,int> vd;
    // destructive scalar addition
    vd = Vector<3,int>(1,2,3);
    vd += 10;
    BOOST_CHECK( vd == (Vector<3,int>(11,12,13)));
    // destructive vector addition
    vd = Vector<3,int>(1,2,3);
    vd += vd;
    BOOST_CHECK( vd == (Vector<3,int>(2,4,6)));
    // destructive scalar subtraction
    vd = Vector<3,int>(11,12,13);
    vd -= 10;
    BOOST_CHECK( vd == (Vector<3,int>(1,2,3)));
    // destructive vector subtraction
    vd = Vector<3,int>(11,12,13);
    vd -= 10;
    BOOST_CHECK( vd == (Vector<3,int>(1,2,3)));
    // destructive scalar multiplication
    vd = Vector<3,int>(1,2,3);
    vd *=10;
    BOOST_CHECK( vd == (Vector<3,int>(10,20,30)));
    // destructive scalar division
    vd = Vector<3,int>(10,20,30);
    vd /= 10;
    BOOST_CHECK( vd == (Vector<3,int>(1,2,3)) );
    // out of bounds checking
    Vector<3,int> vb(1,2,3);
    try {
        vb[3];
        BOOST_CHECK(false);
    } catch (IndexOutOfBounds) {}
    try {
        vb[-1];
        BOOST_CHECK(false);
    } catch (IndexOutOfBounds) {}
    try {
        vb.Get(3);
        BOOST_CHECK(false);
    } catch (IndexOutOfBounds) {}
    try {
        vb.Get(-1);
        BOOST_CHECK(false);
    } catch (IndexOutOfBounds) {}
    // zero tests:
    Vector<3,int> zero;
    // zero vector errors
    try {
        zero.GetNormalize();
        BOOST_CHECK(false);
    } catch (ArithmeticException) {}
    // zero scalar division
    try {
        zero / 0;
        BOOST_CHECK(false);
    } catch (DivisionByZero) {}
    try {
        zero /= 0;
        BOOST_CHECK(false);
    } catch (DivisionByZero) {}
    
}

void OpenEngine::Tests::testMatrix() {
    // identity matrix creation
    Matrix<2,2,int> i;
    BOOST_CHECK( i(0,0)==1 && i(0,1)==0 &&
                 i(1,0)==0 && i(1,1)==1 );
    // matrix scalar creation
    Matrix<2,2,int> a(1);
    BOOST_CHECK( a(0,0)==1 && a(0,1)==1 &&
                 a(1,0)==1 && a(1,1)==1 );
    // parameter creation
    Matrix<2,2,int> b(1,2, 3,4);
    BOOST_CHECK( b(0,0)==1 && b(0,1)==2 &&
                 b(1,0)==3 && b(1,1)==4 );
    // copy creation
    Matrix<2,2,int> c(b);
    BOOST_CHECK( c(0,0)==1 && c(0,1)==2 &&
                 c(1,0)==3 && c(1,1)==4 );
    // equality
    BOOST_CHECK( b == c );
    // assignment on index and inequality
    b(1,1) = 0;
    BOOST_CHECK( b != c );
    // assignment on object
    b = c;
    BOOST_CHECK( b == c );
    // array to matrix
    float f1[] = {1,2,3, 4,5,6, 7,8,9};
    Matrix<3,3,float> mf(f1);
    BOOST_CHECK( mf(0,0)==1 && mf(0,1)==2 && mf(0,2)==3 &&
                 mf(1,0)==4 && mf(1,1)==5 && mf(1,2)==6 &&
                 mf(2,0)==7 && mf(2,1)==8 && mf(2,2)==9 );
    // matrix to array
    float f2[9];
    mf.ToArray(f2);
    BOOST_CHECK( (f2[0]==1) && (f2[1]==2) && (f2[2]==3) &&
                 (f2[3]==4) && (f2[4]==5) && (f2[5]==6) &&
                 (f2[6]==7) && (f2[7]==8) && (f2[8]==9) );
    // matrix multiplication
    Matrix<2,2,int> d = b * c;
    BOOST_CHECK( d(0,0)==7  && d(0,1)==10 &&
                 d(1,0)==15 && d(1,1)==22 );
    // transpose matrix
    d.Transpose();
    BOOST_CHECK( d(0,0)==7  && d(0,1)==15 &&
                 d(1,0)==10 && d(1,1)==22 );
    // matrix row
    Vector<2,int> vr = d.GetRow(1);
    BOOST_CHECK( vr[0] == 10 && vr[1] == 22 );
    BOOST_CHECK( vr == d[1] );
    // matrix column
    Vector<2,int> vc = d.GetColumn(1);
    BOOST_CHECK( vc[0] == 15 && vc[1] == 22 );
    // matrix trace
    BOOST_CHECK( d.Trace() == 29 );
}

void OpenEngine::Tests::testQuaternion() {
    // identity quaternion creation and []
    Quaternion<float> i;
    BOOST_CHECK( i[0]==1 && i[1]==0 &&
                 i[2]==0 && i[3]==0 );
    // 4-arg constructor
    Quaternion<float> q1(1,2,3,4);
    BOOST_CHECK( q1[0]==1 && q1[1]==2 &&
                 q1[2]==3 && q1[3]==4 );
    // copy constructor
    Quaternion<float> q2(q1);
    BOOST_CHECK( q2[0]==1 && q2[1]==2 &&
                 q2[2]==3 && q2[3]==4 );
    // quaternion scalar constructor
    Quaternion<float> q3(10);
    BOOST_CHECK( q3[0]==10 && q3[1]==0 &&
                 q3[2]==0  && q3[3]==0 );
    // vector constructor
    Quaternion<int> q4(Vector<3,int>(2,3,4));
    BOOST_CHECK( q4[0]==0 && q4[1]==2 &&
                 q4[2]==3 && q4[3]==4 );
    // angle/axis constructor

    // @todo: round function does not exist in windows
    /*
    Quaternion<float> q5(3.14f, Vector<3,float>(2,3,4));
    BOOST_CHECK( round(q5[0])==0 && round(q5[1])==2 &&
                 round(q5[2])==3 && round(q5[3])==4 );
    */

    // GetReal and GetImaginary
    BOOST_CHECK( q1.GetReal()==1 && 
                 q1.GetImaginary()==(Vector<3,float>(2,3,4)) );
    // equality operator
    BOOST_CHECK( q1 == q2 );
    // inequality operator
    BOOST_CHECK( i != q1 );
    // check norm
    BOOST_CHECK( i.GetNorm() == 1 );
    BOOST_CHECK( q1.GetNorm() == 30 );
    // @todo: test quaternion multiplication
    
    // normalize quaternion
    Quaternion<float> n1 = q1.GetNormalize();
    BOOST_CHECK(fabs(n1.GetNorm() - 1.0) < 0.000001);
    // normalization after multiplication
    BOOST_CHECK((i * n1).IsNormalized() == true);
    BOOST_CHECK((q1 * n1).IsNormalized() == false);
    BOOST_CHECK((q1 * q2).IsNormalized() == false);

    // @todo: test euler constructor

    // @todo: test GetMatrix
    //std::cout << q1.GetMatrix().ToString() << std::endl;
    //std::cout << n1.GetMatrix().ToString() << std::endl;

    // @todo: test * operator
    //Quaternion<float> qt = q1*q2;
    //std::cout << qt.ToString() << std::endl;
}


void OpenEngine::Tests::testVectorIterator() {
    float* array = new float[6];
    array[0] = 0;
    array[1] = 0;
    array[2] = 0;
    array[3] = 0;
    array[4] = 0;
    array[5] = 0;

    VectorIterator<3 ,float> itr(array, 6);
    BOOST_CHECK(itr == Vector<3, float>(0));
}
