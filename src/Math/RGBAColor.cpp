/*
 * RGBAColor.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#include <Math/RGBAColor.h>
#include <Math/RGBColor.h>

namespace OpenEngine {
namespace Math {

    RGBAColor::RGBAColor(RGBColor c) 
        : Vector<4,float>(c[0], c[1], c[2] ,1.0) {}

    RGBAColor::RGBAColor(float r, float g, float b, float a) 
        : Vector<4,float>(r,g,b,a) {}
    
    RGBAColor::RGBAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
        : Vector<4,float>(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, float(a) / 255.0f) {}

    RGBAColor::RGBAColor() 
        : Vector<4,float>() {}

    RGBColor RGBAColor::GetRGB() {
        return RGBColor((*this)[0],(*this)[1],(*this)[2]);
    }
    
    RGBAColor RGBAColor::GetRGBA() {
        return *this;
    }
    
    float RGBAColor::GetRed() {
        return (*this)[0];
    }
    
    RGBAColor::~RGBAColor() {
        // TODO Auto-generated destructor stub
    }

}
}
