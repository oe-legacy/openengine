/*
 * Color.h
 *
 *  Created on: Dec 2, 2010
 *      Author: ptx
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <Math/Vector.h>

namespace OpenEngine {
namespace Math {

class RGBColor;
class RGBAColor;

class Color {
public:
	virtual RGBColor GetRGB() =0;
	virtual RGBAColor GetRGBA() =0;
};


}  // namespace Math
}  // namespace OpenEngine

#endif /* COLOR_H_ */
