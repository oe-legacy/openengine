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
                 const float distNear,  const float distFar,
                 const float left, const float right,
                 const float bottom, const float top) : IViewingVolumeDecorator(volume),
                 distNear(distNear), distFar(distFar), left(left), right(right), top(top), bottom(bottom) {                 
	}

/**
 * Orthotope destructor.
 */
	Orthotope::~Orthotope() {}
	
	void Orthotope::UpdateDimensions() {
		//@TODO: Fill with clever code
	}
	
	float Orthotope::GetLeft() {
		return left;
	}
    	
    	float Orthotope::GetRight() {
    		return right;
	}
	
    	float Orthotope::GetBottom() {
    		return bottom;
	}
	
    	float Orthotope::GetTop() {
    		return top;
	}
	
    	float Orthotope::GetNear() {
    		return distNear;
	}
	
    	float Orthotope::GetFar() {
    		return distFar;
	}
	
    	void Orthotope::SetLeft(const float left) {
    		this->left = left;
    		UpdateDimensions();
    	}
    	
    	void Orthotope::SetRight(const float right) {
    		this->right = right;
    		UpdateDimensions();
    	}
    	
    	void Orthotope::SetBottom(const float bottom) {
    		this->bottom = bottom;
    		UpdateDimensions();
    	}
    	
    	void Orthotope::SetTop(const float top) {
    		this->top = top;
    		UpdateDimensions();
    	}
    	
    	void Orthotope::SetNear(const float distNear) {
    		this->distNear = distNear;
    		UpdateDimensions();
    	}
    	
    	void Orthotope::SetFar(const float distFar) {
    		this->distFar = distFar;
    		UpdateDimensions();
    	}
	
	Matrix<4,4,float> Orthotope::GetProjectionMatrix() {
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
