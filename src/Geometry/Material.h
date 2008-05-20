// Material class
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <Math/Vector.h>
#include <Resources/ITextureResource.h>
#include <Resources/IShaderResource.h>
#include <boost/serialization/shared_ptr.hpp> // include serialization
                                              // for shared_ptr
namespace OpenEngine {
namespace Geometry {

using namespace OpenEngine::Math;
using namespace OpenEngine::Resources;

class Material;
//! Smart pointer to a material object.
typedef boost::shared_ptr<Material> MaterialPtr;

/**
 * Material structure.
 * 
 *
  * @class Material Material.h Geometry/Material.h
 */
class Material {
private:
    void Copy(const Material& mat);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & diffuse;
        ar & ambient;
        ar & specular;
        ar & shininess;
        ar & emission;
        ar & texr;
        // members that are not serialized
        // ar & shad;
    }
    
    void Init();

public:
    Vector<4,float> diffuse;     //!< diffuse color
    Vector<4,float> ambient;     //!< ambient color
    Vector<4,float> specular;    //!< specular color
    Vector<4,float> emission;    //!< emission color   
    float shininess;             //!< shininess value

//     Vector<4,float> reflective;  //!< reflective color
//     float reflectivity;          //!< reflective color   

//     Vector<4,float> transparent; //!< reflective color
//     float transparency;          //!< reflective color

//     float indexOfRefraction;     //!< reflective color
    
    OpenEngine::Resources::ITextureResourcePtr texr; //!< texture resource
    OpenEngine::Resources::IShaderResourcePtr  shad; //!< shader resource

    Material(); 
    explicit Material(const Material& material);
    explicit Material(const MaterialPtr& material);
    explicit Material(Vector<4,float> amb, Vector<4,float> diff, 
             Vector<4,float> spec);

    virtual ~Material();
};

} // NS Geometry
} // NS OpenEngine

#endif
