#include <Testing/Testing.h>
#include <Math/Tensor.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Core/Exceptions.h>

using namespace std;
using namespace OpenEngine::Math;

int test_main(int argc, char* argv[])
{
    // ---------- Constructor test ----------------
    Tensor<3,3,float> t0;
 
    Vector<3,float> row0(1,0,0);
    Vector<3,float> row1(0,1,0);
    Vector<3,float> row2(0,0,1);

    // Test that we get the identity tensor
    OE_CHECK( t0[0] == row0 &&
              t0[1] == row1 &&
              t0[2] == row2 );
    
    // ---------- Test the identity tensor is symmetric --------
    OE_CHECK( t0.isSymmetric() );

    // ----------- Test tensor addition ----------------
    Tensor<3,3,float> t1;
    t1.setRow(0, Vector<3,float>(1,2,3));
    t1.setRow(1, Vector<3,float>(4,5,6));
    t1.setRow(2, Vector<3,float>(7,8,9));
    
    Tensor<3,3,float> t2;
    t2.setRow(0, Vector<3,float>(1,2,3));
    t2.setRow(1, Vector<3,float>(4,5,6));
    t2.setRow(2, Vector<3,float>(7,8,9));
 
    // Add t1 and t2 together
    Tensor<3,3,float> r;
    r = t1 + t2;

    OE_CHECK( r[0][0] == 2 && r[0][1] == 4  && r[0][2] == 6 &&
              r[1][0] == 8 && r[1][1] == 10 && r[1][2] == 12 &&
              r[2][0] == 14 && r[2][1] == 16 && r[2][2] == 18);
              

     // ---------- Test that the trace is correct --------------- //
    OE_CHECK( r.trace() == 30 );

    // ----------- Test product of a tensor and a vector ---------- //
    // Let v0 be a vector and t3 a second order tensor. Then u = t3 * v0
    // is a vector.  
    Tensor<3,3,float> t3;
    t3.setRow(0, Vector<3,float>(1,2,3));
    t3.setRow(1, Vector<3,float>(4,5,6));
    t3.setRow(2, Vector<3,float>(7,8,9));

    Vector<3,float> v0(1,2,3);
    Vector<3,float> u = t3 * v0;

    OE_CHECK( u[0] == 14 && u[1] == 32 && u[2] == 50 );
  

    // --------------- Test get column vector ------------------- //
    Tensor<3,3,float> t4;
    t4.setRow(0, Vector<3,float>(1,2,3));
    t4.setRow(1, Vector<3,float>(4,5,6));
    t4.setRow(2, Vector<3,float>(7,8,9));
    Vector<3,float> c0(1,4,7);
    Vector<3,float> c1(2,5,8);
    Vector<3,float> c2(3,6,9);

    OE_CHECK( t4.GetColumn(0) == c0 && 
              t4.GetColumn(1) == c1 &&
              t4.GetColumn(2) == c2);
    
    // ------------------ Test set column vector ------------------- //
    t4.SetColumn(0, Vector<3,float>(1,2,3));
    t4.SetColumn(1, Vector<3,float>(4,5,6));
    t4.SetColumn(2, Vector<3,float>(7,8,9));
    // The result should be
    // [ 1, 4, 7
    //   2, 5, 6
    //   7, 8, 9 ]
    OE_CHECK( t4[0][0] == 1 && t4[0][1] == 4 && t4[0][2] == 7 &&
              t4[1][0] == 2 && t4[1][1] == 5 && t4[1][2] == 8 &&
              t4[2][0] == 3 && t4[2][1] == 6 && t4[2][2] == 9);
  

    // ---------------------- Test tensor product ------------------ //
    Tensor<3,3,float> t5;
    t5.setRow(0, Vector<3,float>(1,2,3));
    t5.setRow(1, Vector<3,float>(4,5,6));
    t5.setRow(2, Vector<3,float>(7,8,9));
    row0 = t5.GetRow(0);

    Tensor<3,3,float> t6;
    t6.setRow(0, Vector<3,float>(1,2,3));
    t6.setRow(1, Vector<3,float>(4,5,6));
    t6.setRow(2, Vector<3,float>(7,8,9));
    // The result is expected to be
    // [ 1*1+2*4+3*7=30, 1*2+2*5+3*8=36, 1*3+2*6+3*9=42
    //   4*1+5*4+6*7=66, 4*2+5*5+6*8=81, 4*3+5*6+6*9=96
    //   7*1+8*4+9*7=102, 7*2+8*5+9*8=126, 7*3+8*6+9*9=150 ]
    
    Tensor<3,3,float> r1 = t5 * t6;

    OE_CHECK( r1[0][0] == 30 && r1[0][1] == 36 && r1[0][2] == 42 &&
              r1[1][0] == 66 && r1[1][1] == 81 && r1[1][2] == 96 &&
              r1[2][0] == 102 && r1[2][1] == 126 && r1[2][2] == 150
    );


    
    // ------------- Test Eigenvector and Eigenvalues --------- //
    Tensor<3,3,float> t7;
    t7.setRow(0, Vector<3,float>(3, -1,-1));
    t7.setRow(1, Vector<3,float>(-1, 3,-1));
    t7.setRow(2, Vector<3,float>(-1,-1, 3));

    Vector<3,double> eigenValue = t7.eigenValues();

    printf("EigenValue[0] = %f\n", eigenValue[0]);
    printf("EigenValue[1] = %f\n", eigenValue[1]);
    printf("EigenValue[2] = %f\n", eigenValue[2]);
    return 0;
}
