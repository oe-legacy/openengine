// TGA image resource, TGA Loading inspired by Nate Miller.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _TGA_RESOURCE_H_
#define _TGA_RESOURCE_H_

#include <Resources/ITextureResource.h>
#include <Resources/ResourcePlugin.h>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>
#include <Logging/Logger.h>

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

    //    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        
        ar & boost::serialization::base_object<ITextureResource>(*this);
        ar & filename;
        
    }

    TGAResource() : loaded(false),data(NULL) {
        width = height = depth = id = 0;
    };

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
class TGAPlugin : public ResourcePlugin<ITextureResource> {
public:
	TGAPlugin();
    ITextureResourcePtr CreateResource(string file);
};

} //NS Resources
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Resources::TGAResource)

#endif // _TGA_RESOURCE_H_
