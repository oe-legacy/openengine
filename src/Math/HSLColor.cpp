/*
 * HSLColor.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#include <Math/HSLColor.h>
#include <Math/RGBColor.h>
#include <Math/RGBAColor.h>

namespace OpenEngine {
namespace Math {
HSLColor::HSLColor(float h, float s, float l) : Vector<3,float>(h,s,l) {

}

HSLColor::HSLColor() : Vector<3,float>() {

}

HSLColor::~HSLColor() {

}

RGBColor HSLColor::GetRGB() {
	float hue = (*this)[0];
	float sat = (*this)[1];
	float light = (*this)[2];
	float chroma = (1 - abs(2*light - 1)) * sat;

	int hh = hue/60.0;
	float x = chroma * (1 - abs(hh % 2 - 1));

	Vector<3,float> rgb1;
	if      (0 <= hh && hh <= 1) rgb1 = Vector<3,float>(chroma,x,0);
	else if (1 <= hh && hh <= 2) rgb1 = Vector<3,float>(x,chroma,0);
	else if (2 <= hh && hh <= 3) rgb1 = Vector<3,float>(0,chroma,x);
	else if (3 <= hh && hh <= 4) rgb1 = Vector<3,float>(0,x,chroma);
	else if (4 <= hh && hh <= 5) rgb1 = Vector<3,float>(x,0,chroma);
	else if (5 <= hh && hh <= 6) rgb1 = Vector<3,float>(chroma,0,x);

	float m = light - 0.5*chroma;


	return RGBColor(rgb1[0] + m,
					rgb1[1] + m,
					rgb1[2] + m);
}

RGBAColor HSLColor::GetRGBA() {
    return GetRGB().GetRGBA();
}

}  // namespace Math
}  // namespace OpenEngine
