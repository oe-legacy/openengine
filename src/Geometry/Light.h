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

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/export.hpp>
#include <Meta/BoostSerialization.h>

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

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<Light>(*this);
        ar & ambient;
        ar & diffuse;
        ar & specular;
    }
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Geometry::Light)

#endif // _OE_LIGHT_H_
