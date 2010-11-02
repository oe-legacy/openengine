// An orthogonal viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_ORTHOGONAL_VIEWING_VOLUME_H_
#define _OE_ORTHOGONAL_VIEWING_VOLUME_H_

#include <Display/ViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * An orthogonal viewing volume implementation.
 *
 * @class OrthogonalViewingVolume OrthogonalViewingVolume.h Display/OrthogonalViewingVolume.h
 */
class OrthogonalViewingVolume : public ViewingVolume {
public:

    OrthogonalViewingVolume(const float distNear = 1,
                            const float distFar  = 3000,
                            const float left     = -100,
                            const float right    = 100,
                            const float top      = 100,
                            const float bottom   = -100);

    virtual ~OrthogonalViewingVolume();

    // base implementation
    virtual Matrix<4,4,float> GetProjectionMatrix();
    virtual void Update(const unsigned int width, const unsigned int height);

    // get / set methods
    virtual float GetLeft();
    virtual float GetRight();
    virtual float GetBottom();
    virtual float GetTop();
    virtual float GetNear();
    virtual float GetFar();
    virtual void SetLeft(const float left);
    virtual void SetRight(const float right);
    virtual void SetBottom(const float bottom);
    virtual void SetTop(const float top);
    virtual void SetNear(const float distNear);
    virtual void SetFar(const float distFar);

private:

    // private fields
    float distNear, distFar, left, right, top, bottom;

    // internal routines
    void UpdateDimensions();

};

} // NS Display
} // NS OpenEngine

#endif // _OE_ORTHOGONAL_VIEWING_VOLUME_H_
