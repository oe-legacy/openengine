// An orthogonal viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/OrthogonalViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * OrthogonalViewingVolume constructor.
 */
OrthogonalViewingVolume::OrthogonalViewingVolume(const float distNear,
                                                 const float distFar,
                                                 const float left,
                                                 const float right,
                                                 const float top,
                                                 const float bottom)
    : distNear(distNear)
    , distFar(distFar)
    , left(left)
    , right(right)
    , top(top)
    , bottom(bottom)
{
    UpdateDimensions();
}

/**
 * OrthogonalViewingVolume destructor.
 */
OrthogonalViewingVolume::~OrthogonalViewingVolume() {

}
	
void OrthogonalViewingVolume::UpdateDimensions() {
    //@TODO: Fill with clever code
}

void OrthogonalViewingVolume::Update(const unsigned int width, const unsigned int height) {
    left = 0;
    right = width;
    top = 0;
    bottom = height;
}


	
float OrthogonalViewingVolume::GetLeft() {
    return left;
}
    	
float OrthogonalViewingVolume::GetRight() {
    return right;
}
	
float OrthogonalViewingVolume::GetBottom() {
    return bottom;
}
	
float OrthogonalViewingVolume::GetTop() {
    return top;
}
	
float OrthogonalViewingVolume::GetNear() {
    return distNear;
}
	
float OrthogonalViewingVolume::GetFar() {
    return distFar;
}
	
void OrthogonalViewingVolume::SetLeft(const float left) {
    this->left = left;
    UpdateDimensions();
}
    	
void OrthogonalViewingVolume::SetRight(const float right) {
    this->right = right;
    UpdateDimensions();
}
    	
void OrthogonalViewingVolume::SetBottom(const float bottom) {
    this->bottom = bottom;
    UpdateDimensions();
}

void OrthogonalViewingVolume::SetTop(const float top) {
    this->top = top;
    UpdateDimensions();
}
    	
void OrthogonalViewingVolume::SetNear(const float distNear) {
    this->distNear = distNear;
    UpdateDimensions();
}
    	
void OrthogonalViewingVolume::SetFar(const float distFar) {
    this->distFar = distFar;
    UpdateDimensions();
}
	
Matrix<4,4,float> OrthogonalViewingVolume::GetProjectionMatrix() {
    float a = 2/(right-left);
    float b = 2/(top-bottom);
    float c = -2/(distFar-distNear);
    float tx = -(right+left)/(right-left);
    float ty = -(top+bottom)/(top-bottom);
    float tz = -(distFar+distNear)/(distFar-distNear);
	
    Matrix<4,4,float> matrix( a, 0, 0, tx,
                              0, b, 0, ty,
                              0, 0, c, tz,
                              0, 0, 0, 1);
    matrix.Transpose();
    return matrix;
}

} // NS Display
} // NS OpenEngine
