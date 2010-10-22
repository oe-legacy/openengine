//
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#include <Resources/StreamArchive.h>

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

StreamArchiveReader::StreamArchiveReader(istream& input) : input(input) {

}

size_t StreamArchiveReader::Begin(string key) {
     size_t r;
     string k;
     input >> k;
     if (k != key) {
         throw Core::Exception("Key mismatch in Begin [" + k + 
                         "] should be [" + key + "]");
     }

     input >> r;
     return r;

}
void StreamArchiveReader::End(string key) {
    // nop
}


#define S_TYPE(type, name)                                           \
    type StreamArchiveReader::Read##name(string key) {               \
        type r;                                                      \
        string k;                                                    \
        input >> k;                                                  \
        if (k != key)                                                \
            throw Core::Exception("key mismatch in Read [" + k +     \
                            "] should be [" + key + "]");            \
        input >> r;                                                  \
        return r;                                                    \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE


ISceneNode* StreamArchiveReader::ReadNode() {
    string klass;
    input >> klass; // Human only, we ignore it

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

ISceneNode* StreamArchiveReader::ReadScene(string key) {
    string k;
    input >> k;

    if (k != key)
        throw Core::Exception("key mismatch in ReadScene [" +
                        k + "] should be [" + key + "]");

    return ReadNode();
}

unsigned int StreamArchiveReader::ReadIndex() {
    return ReadInt(IDX_KEY);
}

string StreamArchiveReader::ReadString(string key) {
        size_t len = Begin(key);
        char *buf = new char[len];
        input.ignore(); // Ignore the newline
        input.read(buf,len);        
        string r(buf,len);
        delete buf;
        End(key);
        return r;
    }

// Writer

class StreamArchiveWriter::SceneWriter : public ISceneNodeVisitor {

    StreamArchiveWriter& w;

public:
    SceneWriter(StreamArchiveWriter& w) : w(w) {

    }

#define SCENE_NODE(type)                                \
    void Visit##type(type* node) {                      \
        w._Write(node->GetNodeName());                  \
        w.WriteInt(TAG_KEY,NODE_##type);                \
        w.Begin(CHILD_KEY,node->subNodes.size());       \
        /* only serialize subNodes! */                  \
        /* was: node->VisitSubNodes(*this); */          \
        std::list<ISceneNode*>::iterator itr;           \
        for(itr = node->subNodes.begin();               \
            itr != node->subNodes.end();                \
            itr++) {                                    \
            (*itr)->Accept(*this);                      \
        }                                               \
        w.End(CHILD_KEY);                               \
        node->Serialize(w);                             \
}


#include <Scene/SceneNodes.def>
#undef SCENE_NODE

};

void StreamArchiveWriter::_Write(string s) {
    for(unsigned int i=0;i<tabs;i++)
        output << "\t";
    output << s << endl;
}

StreamArchiveWriter::StreamArchiveWriter(ostream& output) : output(output),tabs(0) {
}

void StreamArchiveWriter::Begin(string key, size_t size) {
    ostringstream os;
    os << key << " "  << size;
    _Write(os.str());
    //output << size << endl;
    tabs++;
}

void StreamArchiveWriter::End(string key) {
    tabs--;

}

#define S_TYPE(type,name)                                            \
    void StreamArchiveWriter::Write##name(string key, type in) {     \
        ostringstream os;                                            \
        os << key << " " << in;                                      \
        _Write(os.str());                                            \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

void StreamArchiveWriter::WriteScene(string key, ISceneNode* node) {
    _Write(key);
    //output << key << " ";
    if (node == NULL) {
        _Write("null");
        WriteInt(TAG_KEY,NODE_NULL);
        return;
    }
    node->Accept(*(new SceneWriter(*this)));
    //output << endl;
}

void StreamArchiveWriter::WriteIndex(unsigned int idx) {
    WriteInt(IDX_KEY,idx);
}

void StreamArchiveWriter::WriteString(string key, string str) {
    Begin(key,str.size());
    output << str << endl;
    //_Write(str);
    End(key);
}

} // NS Resources
} // NS OpenEngine
