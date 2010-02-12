
#include <Resources/IArchiveWriter.h>
#include <Math/Vector.h>
#include <Resources/ISerializable.h>

namespace OpenEngine {
namespace Resources {

    using namespace Math;

#define S_TYPE(type,name)                                           \
    template <>                                                     \
    void IArchiveWriter::Write<type> (std::string key, type in) {   \
    Write##name(key,in);                                            \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

#define S_TYPE(type,name)                                           \
    template <>                                                     \
    void IArchiveWriter::Write<Vector<2,type> > (std::string key, Vector<2,type> in) { \
        WriteVector<2,type>(key,in);                                    \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

#define S_TYPE(type,name)                                           \
    template <>                                                     \
    void IArchiveWriter::Write<Vector<3,type> > (std::string key, Vector<3,type> in) { \
        WriteVector<3,type>(key,in);                                    \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE

#define S_TYPE(type,name)                                           \
    template <>                                                     \
    void IArchiveWriter::Write<Vector<4,type> > (std::string key, Vector<4,type> in) { \
        WriteVector<4,type>(key,in);                                    \
    }
#include <Resources/SerializationTypes.def>
#undef S_TYPE




void IArchiveWriter::WriteObject(std::string key, ISerializable* obj) {
    Begin(key,0);
    unsigned int idx = objects[obj];
    if (!idx) {
        unsigned int size = objects[obj] = objects.size();
        WriteIndex(size);
        WriteInt(TAG_KEY, obj->GetSerialzationTag());
        obj->Serialize(*this);
    } else {
        WriteIndex(idx);
    }
    End(key);
}

    
void IArchiveWriter::WriteObjectPtr(std::string key, boost::shared_ptr<ISerializable> objPtr) {
    Begin(key,0);
    ISerializable* obj = objPtr.get();
    unsigned int idx = objectsPtr[obj];
    if (!idx) {
        unsigned int size = objectsPtr[obj] = objectsPtr.size();
        WriteIndex(size);
        WriteInt(TAG_KEY, obj->GetSerialzationTag());
        obj->Serialize(*this);
    } else {
        WriteIndex(idx);
    }
    End(key);
}


} // NS Resources
} // NS OpenEngine

