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
#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>
#include <Resources/ITexture2D.h>
#include <Resources/ITexture3D.h>
#include <Utils/Convert.h>

#include <boost/shared_ptr.hpp>


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
    texs2D = map<string, ITexture2DPtr>();
    texs3D = map<string, ITexture3DPtr>();
    shading = NONE;
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

    // TODO: deep copy texs2D and texs3D.
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
Material::Material(const Material& mat) 
    : ISerializable() {
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
    else if (this->texs2D != mat->texs2D) return false;
    else if (this->texs3D != mat->texs3D) return false;
    else if (this->shad != mat->shad) return false;
    return true;
}

void Material::AddTexture(Resources::ITexture2DPtr tex){
    string name = "color" + Utils::Convert::ToString<unsigned int>(texs2D.size() + texs3D.size());
    AddTexture(tex, name);
}

void Material::AddTexture(Resources::ITexture2DPtr tex, std::string name){
    texs2D[name] = tex;
}

void Material::AddTexture(Resources::ITexture3DPtr tex){
    string name = "color" + Utils::Convert::ToString<unsigned int>(texs2D.size() + texs3D.size());
    AddTexture(tex, name);
}

void Material::AddTexture(Resources::ITexture3DPtr tex, std::string name){
    texs3D[name] = tex;
}

void Material::Serialize(Resources::IArchiveWriter& w) {
    w.WriteVector<4,float>("diffuse",diffuse);
    w.WriteVector<4,float>("ambient",ambient);
    w.WriteVector<4,float>("specular",specular);
    w.WriteVector<4,float>("emission",emission);
    w.WriteFloat("shininess",shininess);
    
    w.WriteInt("texs2Dsize", texs2D.size());
    unsigned int i = 0;
    map<string, ITexture2DPtr>::iterator itr = texs2D.begin();
    while (itr != texs2D.end()){
        string key = "tex2d" + Utils::Convert::ToString<unsigned int>(i);
        w.WriteString(key, itr->first);
        w.WriteObjectPtr(key, itr->second);
        ++itr; ++i;
    }
        
    w.WriteInt("texs3Dsize", texs3D.size());
    i = 0;
    map<string, ITexture3DPtr>::iterator itr3D = texs3D.begin();
    while (itr3D != texs3D.end()){
        string key = "tex3d" + Utils::Convert::ToString<unsigned int>(i);
        w.WriteString(key, itr3D->first);
        w.WriteObjectPtr(key, itr3D->second);
        ++itr3D; ++i;
    }
}

void Material::Deserialize(Resources::IArchiveReader& r) {
    diffuse = r.ReadVector<4,float>("diffuse");
    ambient = r.ReadVector<4,float>("ambient");
    specular = r.ReadVector<4,float>("specular");
    emission = r.ReadVector<4,float>("emission");
    shininess = r.ReadFloat("shininess");

    texs2D.clear();
    unsigned int texs2Dsize = r.ReadInt("texs2Dsize");
    for (unsigned int i = 0; i < texs2Dsize; ++i){
        string key = "tex2d" + Utils::Convert::ToString<unsigned int>(i);
        string name = r.ReadString(key);
        ITexture2DPtr tex = r.ReadObjectPtr<ITexture2D>(key);
        texs2D[name] = tex;
    }

    texs3D.clear();
    unsigned int texs3Dsize = r.ReadInt("texs3Dsize");
    for (unsigned int i = 0; i < texs3Dsize; ++i){
        string key = "tex3d" + Utils::Convert::ToString<unsigned int>(i);
        string name = r.ReadString(key);
        ITexture3DPtr tex = r.ReadObjectPtr<ITexture3D>(key);
        texs3D[name] = tex;
    }
}

} // NS Geometry
} // NS OpenEngine
