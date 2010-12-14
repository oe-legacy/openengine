/*
 * RGBColor.h
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#ifndef RGBCOLOR_H_
#define RGBCOLOR_H_

#include <Math/Color.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Math {

class RGBColor 	: public Vector<3,float>
				, public Color {
private:
public:
	RGBColor();
	RGBColor(float,float,float);
	virtual ~RGBColor();

	float GetRed();
	RGBColor GetRGB();
	RGBAColor GetRGBA();
    Vector<3,unsigned char> GetUChar();
};

}
}

#endif /* RGBCOLOR_H_ */
