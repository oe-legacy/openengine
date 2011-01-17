// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#include <Resources/SerializationResource.h>
#include <Resources/File.h>
#include <Resources/StreamArchive.h>



namespace OpenEngine {
namespace Resources {

using namespace std;
using namespace Resources;

SerializationPlugin::SerializationPlugin() {
    this->AddExtension("oes");
}

IModelResourcePtr SerializationPlugin::CreateResource(string file) {
    return IModelResourcePtr(new SerializationResource(file));
}


// Resource methods

SerializationResource::SerializationResource(string file)
    : file(file),node(NULL) {
    
}

void SerializationResource::Load() {
    ifstream* in = File::Open(file);

    StreamArchiveReader r(*in);
    node = r.ReadScene("scene");

    in->close();
    delete in;
}
    
void SerializationResource::Unload() {}

ISceneNode* SerializationResource::GetSceneNode() {
    return node;
}

} // NS Resources
} // NS OpenEngine

