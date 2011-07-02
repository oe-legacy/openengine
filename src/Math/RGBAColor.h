/*
 * RGBAColor.h
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#ifndef RGBACOLOR_H_
#define RGBACOLOR_H_

#include <Core/Exceptions.h>
#include <Math/Color.h>
#include <Math/Vector.h>
#include <Resources/ITexture.h>

namespace OpenEngine {
namespace Math {

class RGBAColor : public Vector<4,float>
				, public Color {
private:

public:
	RGBAColor();
    RGBAColor(RGBColor);
	RGBAColor(float,float,float,float);
    RGBAColor(unsigned char,unsigned char,unsigned char,unsigned char);
	virtual ~RGBAColor();

    static inline RGBAColor FromArray(const void* data, const int index, const Resources::ColorFormat f) {
        switch(f){
        case Resources::RGBA: {//RGBA32
            unsigned char* d = ((unsigned char*)data) + index * 4;
            return RGBAColor(d[0], d[1], d[2], d[3]);
            break;
        }
        default:
            throw Core::Exception("Colorformat not supported");
        }
    }
    inline void ToArray(void* data, const int index, const Resources::ColorFormat f) const {
        switch(f){
        case Resources::RGBA: {//RGBA32
            unsigned char* d = ((unsigned char*)data) + index * 4;
            d[0] = Get(0) * 255;
            d[1] = Get(1) * 255;
            d[2] = Get(2) * 255;
            d[3] = Get(3) * 255;
            break;
        }
        default:
            throw Core::Exception("Colorformat not supported");
        }
    }

    static inline RGBAColor Black()  { return RGBAColor(0.0f,0.0f,0.0f,1.0f); }
    static inline RGBAColor Blue()   { return RGBAColor(0.0f,0.0f,1.0f,1.0f); }
    static inline RGBAColor Green()  { return RGBAColor(0.0f,1.0f,0.0f,1.0f); }
    static inline RGBAColor Cyan()   { return RGBAColor(0.0f,1.0f,1.0f,1.0f); }
    static inline RGBAColor Red()    { return RGBAColor(1.0f,0.0f,0.0f,1.0f); }
    static inline RGBAColor Purple() { return RGBAColor(1.0f,0.0f,1.0f,1.0f); }
    static inline RGBAColor Orange() { return RGBAColor(1.0f,0.5f,0.0f,1.0f); }
    static inline RGBAColor Yellow() { return RGBAColor(1.0f,1.0f,0.0f,1.0f); }
    static inline RGBAColor White()  { return RGBAColor(1.0f,1.0f,1.0f,1.0f); }

	float GetRed();
	RGBColor GetRGB();
	RGBAColor GetRGBA();
};

}
}

#endif /* RGBACOLOR_H_ */
