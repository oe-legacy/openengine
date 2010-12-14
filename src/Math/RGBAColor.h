/*
 * RGBAColor.h
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#ifndef RGBACOLOR_H_
#define RGBACOLOR_H_

#include <Math/Color.h>
#include <Math/Vector.h>

namespace OpenEngine {
namespace Math {

class RGBAColor : public Vector<4,float>
				, public Color {
private:

public:
	RGBAColor();
    RGBAColor(RGBColor);
	RGBAColor(float,float,float,float);
	virtual ~RGBAColor();

	float GetRed();
	RGBColor GetRGB();
	RGBAColor GetRGBA();
};

}
}

#endif /* RGBACOLOR_H_ */
