// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#ifndef _OE_STREAM_ARCHIVE_H_
#define _OE_STREAM_ARCHIVE_H_

#include <Resources/IArchiveReader.h>
#include <Resources/IArchiveWriter.h>


namespace OpenEngine {
namespace Scene {
class ISceneNode;
}
namespace Resources {

/**
 * Short description.
 *
 * @class StreamArchive StreamArchive.h ils/StreamArchive.h
 */
class StreamArchiveReader : public IArchiveReader {
private:
    std::istream& input;

    Scene::ISceneNode* ReadNode();

protected:
    size_t Begin(std::string key);
    void End(std::string key);    
    unsigned int ReadIndex();
    

public:
    StreamArchiveReader(std::istream& input);


    int ReadInt(std::string key);
    float ReadFloat(std::string key);
    double ReadDouble(std::string key);
    std::string ReadString(std::string key);

    Scene::ISceneNode* ReadScene(std::string key);
};

class StreamArchiveWriter : public IArchiveWriter {
private:
    std::ostream& output;   
    unsigned int tabs;    

    void _Write(std::string s);

protected:
    class SceneWriter;
    friend class SceneWriter;

    void Begin(std::string key, size_t size);
    void End(std::string key);    
    void WriteIndex(unsigned int idx);

public:
    StreamArchiveWriter(std::ostream& output);

    void WriteInt(std::string key, int in);
    void WriteFloat(std::string key, float in);
    void WriteDouble(std::string key, double in);
    void WriteString(std::string key, std::string in);

    void WriteScene(std::string key, Scene::ISceneNode* node);
};


} // NS Resources
} // NS OpenEngine

#undef WRITE_PRIM
#undef READ_PRIM

#endif // _OE_STREAM_ARCHIVE_H_
