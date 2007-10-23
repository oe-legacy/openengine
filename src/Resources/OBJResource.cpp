// OBJ Model resource.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/OBJResource.h>
#include <Resources/ResourceManager.h>
#include <Resources/File.h>
#include <Logging/Logger.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Resources {

using namespace OpenEngine::Logging;
using OpenEngine::Utils::Convert;

// PLUG-IN METHODS

/**
 * Get the file extension for OBJ files.
 */
string OBJPlugin::GetExtension() {
    return "obj";
}

/**
 * Create a OBJ resource.
 */
IModelResourcePtr OBJPlugin::CreateResource(string file) {
    return IModelResourcePtr(new OBJResource(file));
}


// RESOURCE METHODS

/**
 * Resource constructor.
 */
OBJResource::OBJResource(string file) : file(file), faces(NULL) {}

/**
 * Resource destructor.
 */
OBJResource::~OBJResource() {
    Unload();
}

/**
 * Helper function to print out errors in the OBJ files.
 */
void OBJResource::Error(int line, string msg) {
    logger.warning << file << " line[" << line << "] " << msg << "." << logger.end;
}

/**
 * Load a OBJ material file.
 * Parses the file and places the found textures and shaders in the
 * materials map.
 *
 * You may access the loaded materials from the private member as so:
 * @code
 * Material* m = materials["material_file_name.tga"]; 
 * m->texture; // contains the texture or NULL
 * m->shader;  // contains the shader or NULL
 * @endcode
 *
 * @param file Material file (just the file name, not the full path)
 */
void OBJResource::LoadMaterialFile(string file) {
    // open the material file
    ifstream* in = File::Open(file);

    // set up working variables
    Material* m = NULL;
    char buf[255], tmp[255];
    int line = 0;

    // save the obj file and set this file as the current file so
    // errors are printed correctly
    string objfile = this->file;
    string resource_dir = File::Parent(this->file);
    this->file = file;

    // for each line in the material file...
    while (!in->eof()) {
        line++;
        in->getline(buf,255);

        // new material section
        if (string(buf,6) == "newmtl")
            if (sscanf(buf, "newmtl %s", tmp) != 1)
                Error(line, "Invalid newmtr declaration");
            else {
                // make a new material and add it to the material map
                m = new Material();
                materials.insert(make_pair(string(tmp), m));
            }

        // texture material
        else if (string(buf,6) == "map_Kd")
            if (sscanf(buf, "map_Kd %s", tmp) != 1)
                Error(line, "Invalid map_Ka declaration");
            else if (m == NULL || m->texture != NULL)
                // texture != NULL means we already set it and no newmtl has appeared since
                Error(line, "Multiple map_Kd sections appear before a newmtr declaration");
            else {
                // we reset the resource path temporary to create the texture resource
                string path = ResourceManager::SetPath("");
                m->texture = ResourceManager::CreateTexture(resource_dir + string(tmp));
                ResourceManager::SetPath(path);
            }

        // shader material
        else if (string(buf,6) == "shader")
            if (sscanf(buf, "shader %s", tmp) != 1)
                Error(line, "Invalid shader declaration");
            else if (m == NULL || m->shader != NULL)
                // shader != NULL means we already set it and no newmtl has appeared since
                Error(line, "Multiple shader sections appear before a newmtr declaration");
            else {
                // reset resource path temporary and create the shader resource
                string path = ResourceManager::SetPath("");
                m->shader = ResourceManager::CreateShader(resource_dir + string(tmp));
                ResourceManager::SetPath(path);
            }
        
        // we ignore all other sections in the material file
    }
    // reset file name to obj file
    this->file = objfile;
}


/**
 * Load an OBJ 3d model file.
 *
 * This method parses the file given to the constructor and populates a
 * FaceSet with the data from the file that can be retrieved with
 * GetFaceSet().
 *
 * @see Geometry::FaceSet
 * @see Geometry::Face
 */
void OBJResource::Load() {

    // check if we have loaded the resource
    if (faces != NULL) return;

    ifstream* in = File::Open(file);

    // create a new face set
    faces = new FaceSet();

    // working variables
    char buffer[255];
    float f1, f2, f3;
    int line = 0;
    ITextureResourcePtr texr;
    IShaderResourcePtr  shad;
    vector< Vector<3,float> > vert, norm;
    vector< Vector<2,float> > texc;

    // for each line...
    while (!in->eof()) {
        in->getline(buffer, 255);
        line++;

        // ignored stuff
        if (in->gcount() <= 2 || // short line
            buffer[0] == ' ' || // empty lines
            buffer[0] == '#' || // comments
            buffer[0] == 'g' || // groups
            buffer[0] == 's' ) continue;

        // read vertex
        else if (string(buffer,2) == "v ") {
            if (sscanf(buffer, "v %f %f %f", &f1, &f2, &f3) == 3)
                vert.push_back(Vector<3,float>(f1,f2,f3));
            else
                Error(line, "Invalid vertex");
        }

        // read texture
        else if(string(buffer,2) == "vt") {
			if (sscanf(buffer, "vt %f %f ",&f1, &f2) == 2)
                texc.push_back(Vector<2,float>(f1,f2));
			else
                Error(line, "Invalid texture coordinate");
        }

        // read normals
        else if (string(buffer,2) == "vn") {
			if(sscanf(buffer, "vn %f %f %f", &f1, &f2, &f3) == 3)
				norm.push_back(Vector<3,float>(f1,f2,f3));
			else
				Error(line, "Invalid vertex normal");
        }

        // read faces
        else if (string(buffer,2) == "f ") {
            Vector<9,int> f(0);
            //            int d1, d2, d3;
            // test that the model is triangulated
            char s1[255],s2[255],s3[255],s4[255];
            if (sscanf(buffer, "f %s %s %s %s", s1,s2,s3,s4) != 3)
                Error(line, "Face has not been triangulated");
            else if ( !( sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f[0],&f[1],&f[2],&f[3],&f[4],&f[5],&f[6],&f[7],&f[8]) == 9
                 || sscanf(buffer, "f %d//%d %d//%d %d//%d", &f[0],&f[2],&f[3],&f[5],&f[6],&f[8]) == 6
                 || sscanf(buffer, "f %d %d %d", &f[0],&f[3],&f[6]) == 3 ) ) 
                Error(line, "Invalid face");
            else {
                // Create a new face with the loaded data
                // We subtract one from all indexes so it corresponds
                // to the correct index in the vectors.
                FacePtr face = FacePtr(new Face(vert[f[0] - 1],
                                                vert[f[3] - 1],
                                                vert[f[6] - 1],
                                                norm[f[2] - 1],
                                                norm[f[5] - 1],
                                                norm[f[8] - 1]));
                face->texc[0] = texc[f[1] - 1];
                face->texc[1] = texc[f[4] - 1];
                face->texc[2] = texc[f[7] - 1];

                // test for valid face
                if (face->vert[0] == face->vert[1] || 
                    face->vert[1] == face->vert[2] ||
                    face->vert[0] == face->vert[2]) {
                    Error(line, "Two or more vertices in face are equal");
                    continue;
                }

                // check against invalid normals
                for (int i=0; i<3; i++)
                    if (face->norm[i].IsZero())
                        Error(line, "norm["+Convert::int2string(i)+"] is the zero vector.");

                // add resource pointers
                face->texr = texr;
                face->shad = shad;

                // add the face to the FaceSet
                faces->Add(face);
            }
        }

        // material resources
        else if (string(buffer,6) == "mtllib") {
            string res;
            std::stringstream ss(buffer+7);
            while (ss >> res)
                LoadMaterialFile(File::Parent(file) + res);
        }

        // material elements
        else if (string(buffer,6) == "usemtl") {
            char name[255];
            sscanf(buffer, "usemtl %s", name);
            map<string, Material*>::iterator mat;
            mat = materials.find(name);
            if (mat == materials.end()) {
                texr.reset();
                shad.reset();
                Error(line, "Material "+string(name)+" is not defined in any material resources");
            } else {
                texr = mat->second->texture;
                shad = mat->second->shader;
            }
        }

        // unsupported or invalid lines
        else Error(line, "Unsupported OBJ declaration");
    }

    // close the file
    in->close();

}

/**
 * Unload the resource.
 * Resets the face collection. Does not delete the face set.
 */
void OBJResource::Unload() {
    faces = NULL;
}

/**
 * Get the face set for the loaded OBJ data.
 *
 * @return Face set
 */
FaceSet* OBJResource::GetFaceSet() {
    return faces;
}

} // NS Resources
} // NS OpenEngine
