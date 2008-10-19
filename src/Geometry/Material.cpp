// Face representation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Material.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Geometry {

using namespace std;
using namespace OpenEngine::Math;

// helper function initial material
void Material::Init() {
  	ambient = Vector<4,float>(0.2,0.2,0.2,1.0);
    diffuse = Vector<4,float>(0.8,0.8,0.8,1.0);
    specular = Vector<4,float>(0.0,0.0,0.0,1.0);
    emission = Vector<4,float>(0.0,0.0,0.0,1.0);
    shininess = 0.0;    
}

// initialize default material.
Material::Material() {
    Init();
}

// Shared copy initialization code
void Material::Copy(const Material& mat) {
  	ambient = mat.ambient;
    diffuse = mat.diffuse;
    specular = mat.specular;
    emission = mat.emission;
    shininess = mat.shininess;
}

/**
 * Construct a material by ambient diffuse and specular colors.
 *
 * @param amb ambient color.
 * @param diff diffuse color.
 * @param spec specular color.
 */
Material::Material(Vector<4,float> amb, Vector<4,float> diff, 
                       Vector<4,float> spec) {
    Init();
    
    ambient = amb;
    diffuse = diff;
    specular = spec;
}

/**
 * Copy constructor for a smart pointer.
 *
 * @param mat Material to copy
 */
Material::Material(const MaterialPtr& mat) {
    Copy(*mat);
}

/**
 * Copy constructor.
 *
 * @param mat Material to copy
 */
Material::Material(const Material& mat) {
    Copy(mat);
}

/**
 * Destructor.
 */
Material::~Material() {

}

bool Material::Equals(MaterialPtr mat) {
    if (this->diffuse != mat->diffuse) return false;
    else if (this->ambient != mat->ambient) return false;
    else if (this->specular != mat->specular) return false;
    else if (this->emission != mat->emission) return false;
    else if (this->shininess != mat->shininess) return false;
    else if (this->texr != mat->texr) return false;
    else if (this->shad != mat->shad) return false;
    return true;
}

} // NS Geometry
} // NS OpenEngine
