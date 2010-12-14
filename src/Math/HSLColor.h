/*
 * HSLColor.h
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#ifndef HSLCOLOR_H_
#define HSLCOLOR_H_

#include "Color.h"

namespace OpenEngine {
namespace Math {

class HSLColor 	: public Vector<3,float>
				, public Color {
public:
	HSLColor(float,float,float);
	HSLColor();
	RGBColor GetRGB();
	RGBAColor GetRGBA();
	virtual ~HSLColor();
};


}  // namespace Math
}  // namespace OpenEngine


#endif /* HSLCOLOR_H_ */
