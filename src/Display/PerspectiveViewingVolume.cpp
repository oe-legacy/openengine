// A perspective viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/PerspectiveViewingVolume.h>
#include <Math/Math.h>

namespace OpenEngine {
namespace Display {

/**
 * Perspective viewing volume constructor.
 *
 * @param distNear Near plane [optional]
 * @param distFar Far plane [optional]
 * @param aspect Aspect ratio [optional]
 * @param fov Field of view [optional]
 */
PerspectiveViewingVolume::PerspectiveViewingVolume(const float distNear,
                                                   const float distFar,
                                                   const float aspect,
                                                   const float fov)
    : fov(fov)
    , aspect(aspect)
    , distNear(distNear)
    , distFar(distFar) 
{
    UpdateProjection();
}

PerspectiveViewingVolume::~PerspectiveViewingVolume() {

}

void PerspectiveViewingVolume::Update(const unsigned int width, const unsigned int height) {
    aspect = (float)width/(float)height;
}

Matrix<4,4,float> PerspectiveViewingVolume::GetProjectionMatrix() {
	float f = 1 / tan( fov / 2 );
	float a = ( distFar + distNear ) / ( distNear - distFar );
	float b = (2 * distFar * distNear ) / ( distNear - distFar );
	Matrix<4,4,float> matrix(f/aspect,  0,  0,  0,
                             0,         f,  0,  0,
                             0,         0,  a,  b,
                             0,         0, -1,  0);
	matrix.Transpose();
	return matrix;
}

/**
 * Get the field of view.
 *
 * @return fov Field of view.
 */
float PerspectiveViewingVolume::GetFOV() {
    return fov;
}

/**
 * Get the aspect ratio.
 *
 * @return aspect Aspect ratio.
 */
float PerspectiveViewingVolume::GetAspect() {
    return aspect;
}

/**
 * Get the distance to the near clipping plane.
 *
 * @return distNear Near clipping plane.
 */
float PerspectiveViewingVolume::GetNear() {
    return distNear;
}

/**
 * Get the distance to the far clipping plane.
 *
 * @return distFar Far clipping plane.
 */
float PerspectiveViewingVolume::GetFar() {
    return distFar;
}


/**
 * Set the field of view.
 *
 * @param fov Field of view.
 */
void PerspectiveViewingVolume::SetFOV(const float fov) {
    this->fov = fov;
    UpdateProjection();
}

/**
 * Set the aspect ratio.
 *
 * @param aspect Aspect ratio.
 */
void PerspectiveViewingVolume::SetAspect(const float aspect) {
    this->aspect = aspect;
    UpdateProjection();
}

/**
 * Set the distance to the near clipping plane.
 *
 * @param distNear Near clipping plane.
 */
void PerspectiveViewingVolume::SetNear(const float distNear) {
    this->distNear = distNear;
    UpdateProjection();
}

/**
 * Set the distance to the far clipping plane.
 *
 * @param distFar Far clipping plane.
 */
void PerspectiveViewingVolume::SetFar(float distFar) {
    this->distFar = distFar;
    UpdateProjection();
}

/**
 * Calculate the corners of the near clipping plane.
 *
 * @param[out] left Left corner.
 * @param[out] right Right corner.
 * @param[out] top Top corner.
 * @param[out] bottom Bottom corner.
 */
void PerspectiveViewingVolume::CalculateNearPlane(float& left, float& right, float& top, float& bottom) {
    float t, ty, tx;
    t  = fov * 0.5f;            // half of the angle
    ty = tan(t);                // unit distance on the y-axis
    tx = ty * aspect;           // unit distance on the x-axis
    // set the corners
    right  = tx * distNear;
    left   = -right;
    top    = ty * distNear;
    bottom = -top;
}

/**
 * Compute the frustum projection matrix.
 */
void PerspectiveViewingVolume::UpdateProjection() {
    float left, right, top, bottom;
    CalculateNearPlane(left, right, top, bottom);

    float inv_w, inv_h, inv_d;
    inv_w = 1 / (right - left);
    inv_h = 1 / (top - bottom);
    inv_d = 1 / (distFar - distNear);

    // calculate matrix elements
    projection(0,0) = 2 * distNear * inv_w;
    projection(0,2) = (right + left) * inv_w;
    projection(1,1) = 2 * distNear * inv_h;
    projection(1,2) = (top + bottom) * inv_h;
    projection(2,2) = - (distFar + distNear) * inv_d;
    projection(2,3) = -2 * (distFar * distNear) * inv_d;
    projection(3,2) = -1;
    projection(3,3) = 0;
}

} // NS Display
} // NS OpenEngine
