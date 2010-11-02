// A perspective viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_PERSPECTIVE_VIEWING_VOLUME_H_
#define _OE_PERSPECTIVE_VIEWING_VOLUME_H_

#include <Display/ViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * A perspective viewing volume implementation.
 *
 * @class PerspectiveViewingVolume PerspectiveViewingVolume.h Display/PerspectiveViewingVolume.h
 */
class PerspectiveViewingVolume : public ViewingVolume {
public:

    PerspectiveViewingVolume(const float distNear = 1,
                             const float distFar  = 30000,
                             const float aspect   = 4.0/3.0,
                             const float fov      = PI/4.0);

    virtual ~PerspectiveViewingVolume();

    // base implementation
    virtual Matrix<4,4,float> GetProjectionMatrix();
    virtual void Update(const unsigned int width, const unsigned int height);

    // get / set methods
    virtual float GetFOV();
    virtual float GetAspect();
    virtual float GetNear();
    virtual float GetFar();
    virtual void SetFOV(const float fov);
    virtual void SetAspect(const float aspect);
    virtual void SetNear(const float distNear);
    virtual void SetFar(const float distFar);

private:

    // private fields
    float fov, aspect, distNear, distFar;

    // internal routines
    void UpdateProjection();
    void CalculateNearPlane(float& right, float& left, float& top, float& bottom);

};

} // NS Display
} // NS OpenEngine

#endif // _OE_PERSPECTIVE_VIEWING_VOLUME_H_
