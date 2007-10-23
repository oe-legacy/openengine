// OBJ Model resource.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OBJ_MODEL_RESOURCE_H_
#define _OBJ_MODEL_RESOURCE_H_

#include <Resources/IModelResource.h>
#include <Resources/ITextureResource.h>
#include <Resources/IShaderResource.h>
#include <Geometry/FaceSet.h>

#include <string>
#include <vector>

namespace OpenEngine {
namespace Resources {

using namespace OpenEngine::Geometry;
using namespace std;

/**
 * OBJ-model resource.
 *
 * @class OBJResource OBJResource.h "OBJResource.h"
 */
class OBJResource : public IModelResource {
private:

    // inner material structure
    class Material {
    public:
        ITextureResourcePtr texture; //!< texture resource 
        IShaderResourcePtr shader;   //!< shader resource 
        Material() {}
        ~Material() {}
    };

    string file;                      //!< obj file path
    FaceSet* faces;                   //!< the face set
    map<string, Material*> materials; //!< resources material map

    // helper methods
    void Error(int line, string msg);
    void LoadMaterialFile(string file);

public:
    OBJResource(string file);
    ~OBJResource();
    void Load();
    void Unload();
    FaceSet* GetFaceSet();
};

/**
 * OBJ-model resource plug-in.
 *
 * @class OBJPlugin OBJResource.h "OBJResource.h"
 */
class OBJPlugin : public IModelResourcePlugin {
public:
    IModelResourcePtr CreateResource(string file);
    string GetExtension();
};

} // NS Resources
} // NS OpenEngine

#endif // _OBJ_MODEL_RESOURCE_H_
