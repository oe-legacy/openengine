// Concrete viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/ViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * Construct viewing volume.
 * Default position is origin (0,0,0) and direction is the
 * identity which should amount to looking along the negative
 * z-axis with the y-axis as up.
 */
ViewingVolume::ViewingVolume() {

}

/**
 * Empty destructor.
 */
ViewingVolume::~ViewingVolume() {

}

void ViewingVolume::SetPosition(const Vector<3,float> position) {
    this->position = position;
}

void ViewingVolume::SetDirection(const Quaternion<float> direction) {
    this->direction = direction;
}

Vector<3,float> ViewingVolume::GetPosition() {
    return position;
}

Quaternion<float> ViewingVolume::GetDirection() {
    return direction;
}

Matrix<4,4,float> ViewingVolume::GetViewMatrix() {
    // get the rotation from the quaternion and expand it
    Matrix<4,4,float> m = direction.GetMatrix().GetExpanded();
    Matrix<4,4,float> t;
    // write the position information
    t(3,0) = -position.Get(0);
    t(3,1) = -position.Get(1);
    t(3,2) = -position.Get(2);
    return t * m;
}

Matrix<4,4,float> ViewingVolume::GetProjectionMatrix() {
	// Setup standard values (use Frustum or Orthotope to customize) 
	float fov = PI/4;
	float aspect = 4.0/3.0;
	float distNear = 0.01;
	float distFar = 5000;
	
	float f = 1 / tan( fov / 2 );
	float a = ( distFar + distNear ) / ( distNear - distFar );
	float b = (2 * distFar * distNear ) / ( distNear - distFar );
	Matrix<4,4,float> matrix(f/aspect,	0,	0,	0,
				 0, 			f, 	0, 	0,
				 0,			0, 	a,	b,
				 0,			0,	-1,	0);
	matrix.Transpose();
	return matrix;
}

/**
 * Empty signal handler.
 */
void ViewingVolume::SignalRendering(const float dt) {

}

bool ViewingVolume::IsVisible(const Square& square) {
    return true;
}

bool ViewingVolume::IsVisible(const Sphere& sphere) {
    return true;
}

bool ViewingVolume::IsVisible(const Box& box) {
    return true;
}

} // NS Display
} // NS OpenEngine
