

#include <Resources/IArchiveReader.h>
#include <Resources/SerializableObjects.h>
#include <Resources/SerializableObjectTags.h>
#include <Math/Vector.h>
#include <boost/shared_ptr.hpp>

namespace OpenEngine {
namespace Resources {

using namespace Math;
using namespace boost;

#define S_TYPE(type,name)                                               \
    template <>                                                         \
    type IArchiveReader::Read<type >(std::string key) {                 \
        return Read##name(key);                                         \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

#define S_TYPE(type,name)                                               \
    template <>                                                         \
        Vector<2,type> IArchiveReader::Read<Vector<2, type> >(std::string key) { \
        return ReadVector<2,type>(key);                           \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

#define S_TYPE(type,name)                                               \
    template <>                                                         \
        Vector<3,type> IArchiveReader::Read<Vector<3, type> >(std::string key) { \
        return ReadVector<3,type>(key);                           \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

#define S_TYPE(type,name)                                               \
    template <>                                                         \
        Vector<4,type> IArchiveReader::Read<Vector<4, type> >(std::string key) { \
        return ReadVector<4,type>(key);                           \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE


ISerializable* IArchiveReader::ReadObject(string key) {
    size_t s = Begin(key);
    if (s != 0)
        throw Exception("Invalid size in ReadObject");
    unsigned int idx = ReadIndex();
    ISerializable* obj = objects[idx];
    if (!obj) {
        SerializableObjectTags tag = (SerializableObjectTags)ReadInt(TAG_KEY);


        switch(tag) {
#define S_OBJECT(ns,klass)                  \
        case S_OBJ_##ns##_##klass:          \
            obj = new ns::klass();          \
            break;                 
#include <Resources/SerializableObjects.def>
#undef S_OBJECT;
        default:
            throw Exception("Unknown class in ReadObject");
        };
            
        obj->Deserialize(*this);
        objects[idx] = obj;
    } 

    End(key);
    return obj;
}

shared_ptr<ISerializable> IArchiveReader::ReadObjectPtr(string key) {
    size_t s = Begin(key);
    if (s != 0)
        throw Exception("Invalid size in ReadObject");
    unsigned int idx = ReadIndex();
    shared_ptr<ISerializable> obj = objectsPtr[idx];
    if (!obj.get()) {
        SerializableObjectTags tag = (SerializableObjectTags)ReadInt(TAG_KEY);


        switch(tag) {
#define S_OBJECT(ns,klass)                  \
        case S_OBJ_##ns##_##klass:          \
            obj.reset(new ns::klass());     \
            break;                 
#include <Resources/SerializableObjects.def>
#undef S_OBJECT;
        default:
            throw Exception("Unknown class in ReadObjectPtr");
        };
            
        obj->Deserialize(*this);
        objectsPtr[idx] = obj;
    } 

    End(key);
    return obj;
}




} // NS Resources
} // NS OpenEngine
