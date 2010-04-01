//
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#include <Resources/BinaryStreamArchive.h>

#include <Core/Exceptions.h>
#include <Scene/SceneNode.h>
#include <Scene/ISceneNodeVisitor.h>

#include <Scene/SceneNodes.h>

#include <string>

using namespace std;

namespace OpenEngine {
namespace Resources {


    enum SceneNodeTags {
#define SCENE_NODE(node) \
        NODE_##node,
#include <Scene/SceneNodes.def>
#undef SCENE_NODE
        NODE_NULL,
        NODE_END
    };

    using namespace Scene;

BinaryStreamArchiveReader::BinaryStreamArchiveReader(istream& input) : input(input) {

}

size_t BinaryStreamArchiveReader::Begin(string key) {
     size_t r;
     input.read((char*)&r,sizeof(size_t));
     return r;

}
void BinaryStreamArchiveReader::End(string key) {
    // nop
}


#define S_TYPE(type, name)                                              \
    type BinaryStreamArchiveReader::Read##name(string key) {            \
         type r;                                                        \
         input.read((char*)&r,sizeof(type));                            \
         return r;                                                      \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE


ISceneNode* BinaryStreamArchiveReader::ReadNode() {
    SceneNodeTags tag = SceneNodeTags(ReadInt(TAG_KEY));
    ISceneNode *node = NULL;
    // Read a node

    switch (tag) {
#define SCENE_NODE(type)                            \
        case NODE_##type :                          \
            node = new type();                      \
            break;
#include <Scene/SceneNodes.def>
#undef SCENE_NODE
    case NODE_NULL:
        return NULL;
    case NODE_END:
        throw Core::Exception("Unknown node tag in ReadScene");
        break;
    }
    // Read children...
    unsigned int size = Begin(CHILD_KEY);

    for (unsigned int i=0; i<size; i++) {
        node->AddNode(ReadNode());
    }

    End(CHILD_KEY);

    node->Deserialize(*this);
    return node;

}

ISceneNode* BinaryStreamArchiveReader::ReadScene(string key) {
    return ReadNode();
}

unsigned int BinaryStreamArchiveReader::ReadIndex() {
    return ReadInt(IDX_KEY);
}

string BinaryStreamArchiveReader::ReadString(string key) {
        size_t len = Begin(key);
        char *buf = new char[len];        
        input.read(buf,len);        
        string r(buf,len);
        delete buf;
        End(key);
        return r;
    }

// Writer

class BinaryStreamArchiveWriter::SceneWriter : public ISceneNodeVisitor {

    BinaryStreamArchiveWriter& w;

public:
    SceneWriter(BinaryStreamArchiveWriter& w) : w(w) {

    }

#define SCENE_NODE(type)                                \
    void Visit##type(type* node) {                      \
        w.WriteInt(TAG_KEY,NODE_##type);                \
        w.Begin(CHILD_KEY,node->GetNumberOfNodes());    \
        node->VisitSubNodes(*this);                     \
        w.End(CHILD_KEY);                               \
        node->Serialize(w);                             \
}


#include <Scene/SceneNodes.def>
#undef SCENE_NODE

};


BinaryStreamArchiveWriter::BinaryStreamArchiveWriter(ostream& output) : output(output),tabs(0) {
}

void BinaryStreamArchiveWriter::Begin(string key, size_t size) {
    output.write((char*)&size,sizeof(size_t));
    
}

void BinaryStreamArchiveWriter::End(string key) {


}

#define S_TYPE(type,name)                                               \
    void BinaryStreamArchiveWriter::Write##name(string key, type in) {  \
    output.write((char*)&in, sizeof(type));                             \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

void BinaryStreamArchiveWriter::WriteScene(string key, ISceneNode* node) {    
    if (node == NULL) {
        WriteInt(TAG_KEY,NODE_NULL);
        return;
    }
    node->Accept(*(new SceneWriter(*this)));
}

void BinaryStreamArchiveWriter::WriteIndex(unsigned int idx) {
    WriteInt(IDX_KEY,idx);
}

void BinaryStreamArchiveWriter::WriteString(string key, string str) {
    Begin(key,str.size());
    output << str;
    End(key);
}

} // NS Resources
} // NS OpenEngine
