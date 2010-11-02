// Concrete viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _VIEWING_VOLUME_H_
#define _VIEWING_VOLUME_H_

#include <Display/IViewingVolume.h>

namespace OpenEngine {
namespace Display {

/**
 * Concrete viewing volume implementation.
 * This implementation uses quaternions internally to manage the
 * rotational information.
 *
 * @class ViewingVolume ViewingVolume.h Display/ViewingVolume.h
 */
class ViewingVolume : public IViewingVolume {

protected:

    Vector<3,float> position;    //!< position vector
    Quaternion<float> direction; //!< direction quaternion
    Matrix<4,4,float> projection; //!< projection matrix

public:

    ViewingVolume();
    virtual ~ViewingVolume();

    virtual void Update(const unsigned int width, const unsigned int height);

    virtual void SetPosition(const Vector<3,float> position);
    virtual void SetDirection(const Quaternion<float> direction);
    virtual Vector<3,float> GetPosition();
    virtual Quaternion<float> GetDirection();
    virtual Matrix<4,4,float> GetViewMatrix();
    virtual Matrix<4,4,float> GetProjectionMatrix();

    virtual void SignalRendering(const float dt);

    virtual bool IsVisible(const Square& square);
    virtual bool IsVisible(const Sphere& sphere);
    virtual bool IsVisible(const Box& box);

};

} // NS Display
} // NS OpenEngine

#endif // _VIEWING_VOLUME_H_
