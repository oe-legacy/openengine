// Test the geometry lib
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>

#include "testGeometry.h"

// include geometry lib
#include <Geometry/FaceSet.h>

#include <iostream>

using namespace OpenEngine::Geometry;

void OpenEngine::Tests::testFaceSet() {
    // test ComparePosition function
	Vector<3,float> p1(156.74893,-19.059851,52.948181);
	Vector<3,float> p2(164.09485,-19.059851,73.145622);
	Vector<3,float> p3(156.74893,2.4319899,52.948181);
	FacePtr face(new Face(p1,p2,p3));
	face->norm[0] = ((p1-p2) % (p3-p2)).GetNormalize();
	face->CalcHardNorm();
	Vector<3,int> result = face->ComparePosition(face);
    BOOST_CHECK( (result == Vector<3,int>(0,0,0)) );
}

void OpenEngine::Tests::testLine() {
    /*
    // from: http://mathforum.org/library/drmath/view/51996.html
    Vector<3,float> lb(1,1,-6);
    Vector<3,float> la(1,-2,0);
    Vector<3,float> rb(1,2,-3);
    Vector<3,float> ra(1,0,-4);

    float dist = 5/sqrt(21);
    Vector<3,float> p1 = (31/42,32/21,-6);
    Vector<3,float> p2 = p1 + Vector<3,float>(4,2,1) * dist;

    Vector<3,float> line = Line::ShortestLineBetweenLines( l1, l2 );

    BOOST_CHECK( (p1 == ) );
    BOOST_CHECK( (p2 == ) );
*/
}
