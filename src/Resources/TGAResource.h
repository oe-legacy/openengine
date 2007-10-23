// TGA image resource, TGA Loading inspired by Nate Miller.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TGA_RESOURCE_H_
#define _TGA_RESOURCE_H_

#include <Resources/ITextureResource.h>
#include <string>
#include <iostream>
#include <fstream>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * TGA image resource.
 *
 * @class TGAResource TGAResource.h Resources/TGAResource.h
 */
class TGAResource : public ITextureResource {
private:
    bool loaded;
    int id;                     //!< material identifier
    string filename;            //!< file name
    unsigned char* data;        //!< binary material data
    int width;                  //!< texture width
    int height;                 //!< texture height
    int depth;                  //!< texture depth/bits

public:

    /**
     * Constructor
     *
     * @param file tga file to load.
     */
    TGAResource(string file);
    ~TGAResource();

    // resource methods
    void Load();
    void Unload();

    // texture resource methods
	int GetID();
	void SetID(int id);   
    int GetWidth();
	int GetHeight();
	int GetDepth();
	unsigned char* GetData();

};

/**
 * TGA texture resource plug-in.
 *
 * @class TGAPlugin TGAResource.h Resources/TGAResource.h
 */
class TGAPlugin : public ITextureResourcePlugin {
public:
    ITextureResourcePtr CreateResource(string file);
    string GetExtension();
};

} //NS Resources
} //NS OpenEngine

#endif // _TGA_RESOURCE_H_
