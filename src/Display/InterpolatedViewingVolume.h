// Interpolated viewing volume.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERPOLATED_VIEWING_VOLUME_H_
#define _INTERPOLATED_VIEWING_VOLUME_H_

#include <Display/IViewingVolumeDecorator.h>

namespace OpenEngine {
namespace Display {

/**
 * Interpolated viewing volume.
 *
 * @class InterpolatedViewingVolume InterpolatedViewingVolume.h Display/InterpolatedViewingVolume.h
 */
class InterpolatedViewingVolume : public IViewingVolumeDecorator {

private:

    // end points to interpolate by
    Vector<3,float> oldPosition;
    Quaternion<float> oldDirection;

    //! per second interpolation factor
    float factor;

public:

    // Mandatory constructors and destructor.
    InterpolatedViewingVolume(IViewingVolume& volume, float factor = 5.0f);
    virtual ~InterpolatedViewingVolume();

    // Overwritten viewing volume methods
    virtual void SignalRendering(const float dt);

};

} // NS Display
} // NS OpenEngine

#endif // _INTERPOLATED_VIEWING_VOLUME_H_
