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
// #include <list>
#include <utility>
#include <string>
#include <map>

// using std::list;
using std::map;
using std::pair;
using std::string;

// forward declerations
namespace OpenEngine {
    namespace Resources{
        class IShaderResource;
        typedef boost::shared_ptr<IShaderResource> IShaderResourcePtr;
        class ITexture2D;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;
        class ITexture3D;
        typedef boost::shared_ptr<ITexture3D> ITexture3DPtr;
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
    OE_SERIALIZABLE_OBJECT(Material)

private:
    map<string, ITexture2DPtr> texs2D;
    map<ITexture2DPtr, unsigned int> uvIndices;
    map<string, ITexture3DPtr> texs3D;

    void Copy(const Material& mat);
    void Init();

public:
    enum ShadingModel {
        NONE,
        PHONG,
        BLINN
        // more to come ...
    } shading;
    Vector<4,float> diffuse;     //!< diffuse color
    Vector<4,float> ambient;     //!< ambient color
    Vector<4,float> specular;    //!< specular color
    Vector<4,float> emission;    //!< emission color
    float shininess;             //!< shininess value

    IShaderResourcePtr  shad; //!< shader resource
    
    Material();
    explicit Material(const Material& material);
    explicit Material(const MaterialPtr& material);
    explicit Material(Vector<4,float> amb, Vector<4,float> diff,
             Vector<4,float> spec);

    virtual ~Material();

    bool Equals(MaterialPtr mat);

    void AddTexture(ITexture2DPtr tex);
    void AddTexture(ITexture2DPtr tex, std::string name);
    void AddUVIndex(ITexture2DPtr tex, unsigned int index);
    unsigned int GetUVIndex(ITexture2DPtr tex);
    void AddTexture(ITexture3DPtr tex);
    void AddTexture(ITexture3DPtr tex, std::string name);
    inline map<string, ITexture2DPtr> Get2DTextures() const { return texs2D; }
    inline map<string, ITexture3DPtr> Get3DTextures() const { return texs3D; }

    void Serialize(IArchiveWriter& w);
    void Deserialize(IArchiveReader& r);
};

} // NS Geometry
} // NS OpenEngine

#endif
