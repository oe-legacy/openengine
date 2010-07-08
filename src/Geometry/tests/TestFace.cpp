#include <Testing/Testing.h>

#include <Geometry/Face.h>

using namespace OpenEngine::Geometry;

void test_contains() {


    // The face
    Vector<3,float> p1(0,0,0);
    Vector<3,float> p2(0,1,0);
    Vector<3,float> p3(1,0,0);


    // inside
    Vector<3,float> p4(0.1, 0, 0);

    // outside
    Vector<3,float> p5(2, 0, 0);


    // outside plane
    Vector<3,float> p6(0.1, 0, 1);


    Face f1(p1,p2,p3);

    // inside

    OE_CHECK(true == f1.Contains(p1));
    OE_CHECK(true == f1.Contains(p4));

    // outside

    OE_CHECK(false == f1.Contains(p5));
    OE_CHECK(false == f1.Contains(p6));
    

}

int test_main(int argc, char* argv[]) {
    
    test_contains();

    return 0;
}
