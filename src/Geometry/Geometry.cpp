// Geometry subsystem.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Geometry.h>
#include <Geometry/Square.h>
#include <Geometry/Box.h>
#include <Geometry/Sphere.h>

namespace OpenEngine {
namespace Geometry {

Geometry::Geometry() {}

Geometry::~Geometry() {}

bool Geometry::Intersects(const Box& box, const Square& square) {
    return Geometry::Intersects(square, box);
}
/**
 *
 */
bool Geometry::Intersects(const Square& square, const Box& box) {
    return (square.Intersects(box.center + box.corner) ||
            square.Intersects(box.center + box.corner * Vector<3,float>( 1, 1,-1)) ||
            square.Intersects(box.center + box.corner * Vector<3,float>( 1,-1, 1)) ||
            square.Intersects(box.center + box.corner * Vector<3,float>( 1,-1,-1)) ||
            square.Intersects(box.center + box.corner * Vector<3,float>(-1, 1, 1)) ||
            square.Intersects(box.center + box.corner * Vector<3,float>(-1, 1,-1)) ||
            square.Intersects(box.center + box.corner * Vector<3,float>(-1,-1, 1)) ||
            square.Intersects(box.center + box.corner * Vector<3,float>(-1,-1,-1)) );
}

bool Geometry::Intersects(const Sphere& sphere, const Square& square) {
    return Geometry::Intersects(square, sphere);
}

bool Geometry::Intersects(const Square& square, const Sphere& sphere) {
    Vector<3,float> scenter( square.GetCenter().Get(0), 0, square.GetCenter().Get(1) );
    float ssize = square.GetHalfSize();
    Vector<3,float> max = (scenter + ssize) + sphere.GetRadius();
    Vector<3,float> min = (scenter - square.GetHalfSize()) - sphere.GetRadius();
    Vector<3,float> center = sphere.GetCenter();
    if( center[0] <= max[0] && center[1] <= max[1] && center[2] <= max[2] )
        if( center[0] >= min[0] && center[1] >= min[1] && center[2] >= min[2] )
            return true;
    return false;
}


} // NS Geometry
} // NS OpenEngine
