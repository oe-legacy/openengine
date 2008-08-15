// Interpolated viewing volume implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <math.h>

#include <Display/InterpolatedViewingVolume.h>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Display {

using std::min;

/**
 * Construct viewing volume.
 * Default position is origin (0,0,0) and direction is the
 * identity which should amount to looking along the negative
 * z-axis with the y-axis as up.
 */
InterpolatedViewingVolume::InterpolatedViewingVolume(IViewingVolume& volume, float factor)
    : IViewingVolumeDecorator(volume), factor(factor) {
    timer.Start();
}

/**
 * Empty destructor.
 */
InterpolatedViewingVolume::~InterpolatedViewingVolume() {

}

/**
 * Signal handler.
 */
void InterpolatedViewingVolume::SignalRendering(const float dt) {
    // let the underlying volume perform signal tasks
    volume.SignalRendering(dt);

    // compute the new interpolated direction and position
    float t = min(1.0f, timer.GetElapsedTimeAndReset().AsInt() * factor / 1000000);
    oldDirection = Quaternion<float>(oldDirection, volume.GetDirection(), t);
    oldPosition = oldPosition + ((volume.GetPosition() - oldPosition) * t);

    // set in on the volume
    volume.SetDirection(oldDirection);
    volume.SetPosition(oldPosition);
}

} // NS Display
} // NS OpenEngine
