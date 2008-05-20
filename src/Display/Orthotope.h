// Interface for viewing volume decorators.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _ORTHOTOPE_H_
#define _ORTHOTOPE_H_


#include <Display/IViewingVolumeDecorator.h>

namespace OpenEngine {
namespace Display {

/**
 * Viewing volume decorator interface.
 *
 * @class IViewingVolumeDecorator IViewingVolumeDecorator.h Display/IViewingVolumeDecorator.h
 */
class Orthotope : public IViewingVolumeDecorator {
public:    
    /**
     * Orthotope constructor.
     */
    Orthotope(IViewingVolume& volume,
            const float distNear   = 10,  const float distFar = 300,
            const float aspect = 4.0/3.0, const float fov = PI/4.0);

    /**
     * Orthotope destructor.
     */
    virtual ~Orthotope();
};

} // NS Display
} // NS OpenEngine

#endif // _ORTHOTOPE_H_
