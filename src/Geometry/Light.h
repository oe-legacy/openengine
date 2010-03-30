// Base class for Light nodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_LIGHT_H_
#define _OE_LIGHT_H_

#include <Math/Vector.h>


namespace OpenEngine {
namespace Geometry {

using Math::Vector;

/**
 * Base class for light nodes.
 * 
 * @class Light Light.h Geometry/Light.h
 */
class Light {
public:
    Vector<4,float> ambient, diffuse, specular;

    Light()
        : ambient(Vector<4,float>(0.0,0.0,0.0,1.0))
        , diffuse(Vector<4,float>(1.0,1.0,1.0,1.0))
        , specular(Vector<4,float>(1.0,1.0,1.0,1.0)) {}

    virtual ~Light() {}


};

} // NS Scene
} // NS OpenEngine


#endif // _OE_LIGHT_H_
