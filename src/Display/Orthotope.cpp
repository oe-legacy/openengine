// Interface for viewing volume decorators.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/Orthotope.h>

namespace OpenEngine {
namespace Display {

/**
 * Viewing volume decorator interface.
 *
 * @class IViewingVolumeDecorator IViewingVolumeDecorator.h Display/IViewingVolumeDecorator.h
 */
/**
 * Orthotope constructor.
 */
	Orthotope::Orthotope(IViewingVolume& volume,
                 const float distNear, const float distFar,
                 const float aspect, const float fov) : IViewingVolumeDecorator(volume) {
            this->fov = fov;
            this->aspect = aspect;
            this->distNear = distNear;
            this->distFar = distFar;
            this->projectionMode = OE_ORTHOGONAL;
	}

/**
 * Orthotope destructor.
 */
	Orthotope::~Orthotope() {}

} // NS Display
} // NS OpenEngine
