/*
 * RGBColor.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#include <Math/RGBColor.h>
#include <Math/RGBAColor.h>

namespace OpenEngine {
namespace Math {

RGBColor::RGBColor(float r, float g, float b) : Vector<3,float>(r,g,b) {

}

RGBColor::RGBColor() : Vector<3,float>() {

}

RGBColor RGBColor::GetRGB() {
	return *this;
}

RGBAColor RGBColor::GetRGBA() {
	return RGBAColor(*this);
}


float RGBColor::GetRed() {
	return (*this)[0];
}

Vector<3,unsigned char> RGBColor::GetUChar() {
    return Vector<3,unsigned char>((*this)[0]*255.0, (*this)[1]*255.0, (*this)[2]*255.0);
}

RGBColor::~RGBColor() {
	// TODO Auto-generated destructor stub
}

}
}
