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
#include <boost/shared_ptr.hpp>
#include <Resources/ISerializable.h>

// forward declerations
namespace OpenEngine {
    namespace Resources{
        class IShaderResource;
        typedef boost::shared_ptr<IShaderResource> IShaderResourcePtr;
        class ITexture2D;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;
    }
}

namespace OpenEngine {
    namespace Resources {
        class IArchiveWriter;
        class IArchiveReader;
    }
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
class Material : public Resources::ISerializable {
private:
    void Copy(const Material& mat);


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

    OpenEngine::Resources::ITexture2DPtr texr; //!< texture resource
    OpenEngine::Resources::IShaderResourcePtr  shad; //!< shader resource

    Material();
    explicit Material(const Material& material);
    explicit Material(const MaterialPtr& material);
    explicit Material(Vector<4,float> amb, Vector<4,float> diff,
             Vector<4,float> spec);

    virtual ~Material();

    bool Equals(MaterialPtr mat);

    unsigned int GetSerialzationTag();

    void Serialize(Resources::IArchiveWriter& w);
    void Deserialize(Resources::IArchiveReader& r);
};

} // NS Geometry
} // NS OpenEngine

#endif
