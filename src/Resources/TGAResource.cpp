// TGA image resource, TGA Loading inspired by Nate Miller.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/TGAResource.h>
#include <Resources/Exceptions.h>
#include <Resources/File.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Utils::Convert;

string TGAPlugin::GetExtension() {
    return "tga";
}

ITextureResourcePtr TGAPlugin::CreateResource(string file) {
    return ITextureResourcePtr(new TGAResource(file));
}

TGAResource::TGAResource(string filename)
    : loaded(false),
      filename(filename),
      data(NULL) {
    width = height = depth = id = 0;
}

TGAResource::~TGAResource() {
    Unload();
}

void TGAResource::Load() {
    if (loaded) return;
    ifstream* file = File::Open(filename,ios::binary);

    // read in colormap info and image type, unsigned char 0 ignored
    unsigned char* type = new unsigned char[3];
    file->read((char*)type, sizeof(unsigned char)*3); 
    // check for supported tga file type
    if (type[1] != 0 || (type[2] != 2 && type[2] != 3)) {
        file->close();
    	throw ResourceException("Unsupported tga file: " + filename);
    }
    char dataIndex = type[0];
    delete[] type;
    // seek past the header and useless info
    file->seekg(12);
    unsigned char* info = new unsigned char[7];
    file->read((char*)info, sizeof(unsigned char)*6);
    width = info[0] + info[1] * 256; 
    height = info[2] + info[3] * 256;
    depth =	info[4]; 
    delete[] info;

    // make sure we are loading a supported color depth 
    if (depth != 32 && depth != 24 && depth != 8) {
        file->close();
        delete file;
        string msg = "Unsupported color depth: ";
        msg += Convert::int2string(depth) + " in file: " + filename;
        throw ResourceException(msg);
    }

    // load data, taking color depth into acount
    int numberOfCharsPerColor = (depth/8);
    long size = width * height * numberOfCharsPerColor;
    data = new unsigned char[size]; 
    
    file->seekg(dataIndex, ios_base::cur); // skip past image identification
    file->read((char*)data, sizeof(unsigned char)*size); 
    if (file->fail()) {
        delete [] data;
        data = NULL;
        file->close();
        delete file;
        throw ResourceException("Error loading TGA data in: " + filename);
    }
    if (depth != 8) { // @todo: why should this be skipped for depth==8
        // convert the data from BGR to RGB
        for (int i=0; i < size; i+=numberOfCharsPerColor) {
            unsigned char temp = data[i];
            data[i] = data[i + 2];
            data[i + 2] = temp;
        }
    }
    file->close();
    delete file;

    // no image data 
    if (data == NULL)
    	throw ResourceException("Unsupported data in file: " + filename);
    loaded = true;
}

void TGAResource::Unload() {
    if (loaded) {
        delete[] data;
        loaded = false;
    }
}

int TGAResource::GetID(){
    return id;
}
void TGAResource::SetID(int id){
    this->id = id;
}	
int TGAResource::GetWidth(){
    return width;
}
int TGAResource::GetHeight(){
    return height;
}
int TGAResource::GetDepth(){
    return depth;
}
unsigned char* TGAResource::GetData(){
    return data;
}

} //NS Resources
} //NS OpenEngine
