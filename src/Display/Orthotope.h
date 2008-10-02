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
private:
	float distNear, distFar;
	float left, right;
	float top, bottom;
	
	void UpdateDimensions();
public:    
    /**
     * Orthotope constructor.
     */
    Orthotope(IViewingVolume& volume,
            const float distNear   = 1,    const float distFar = 3000,
            const float left       = -100, const float right   = 100,
            const float bottom     = -100, const float top     = 100);

    /**
     * Orthotope destructor.
     */
    virtual ~Orthotope();
    
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
    virtual Matrix<4,4,float> GetProjectionMatrix();
};

} // NS Display
} // NS OpenEngine

#endif // _ORTHOTOPE_H_
