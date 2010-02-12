// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#ifndef _OE_I_ARCHIVE_READER_H_
#define _OE_I_ARCHIVE_READER_H_

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>
#include <Core/Exceptions.h>

#include <string>
#include <sstream>


#include <Resources/Serialization.h>
#include <boost/shared_ptr.hpp>


namespace OpenEngine {
namespace Scene {
class ISceneNode;
}
namespace Resources {

    class ISerializable;

/**
 * Short description.
 *
 * @class IArchiveReader IArchiveReader.h Resources/IArchiveReader.h
 */
class IArchiveReader {
private:
    template <class T> T Read(std::string key);

protected:
    virtual size_t Begin(std::string key) = 0;
    virtual void End(std::string key) = 0;
    virtual unsigned int ReadIndex() = 0;
public:
    virtual int ReadInt(std::string key) = 0;
    virtual float ReadFloat(std::string key) = 0;
    virtual double ReadDouble(std::string key) = 0;
    virtual std::string ReadString (std::string key) = 0;

    virtual Scene::ISceneNode* ReadScene(std::string key) = 0;
    ISerializable* ReadObject(std::string key);
    boost::shared_ptr<ISerializable> ReadObjectPtr(std::string key);
    // 

    template <class T>
    Math::Quaternion<T> ReadQuaternion(std::string key) {
        size_t size = Begin(key);
#ifdef OE_SAFE
        if (size != 4) {
            throw Core::Exception("Quaternion need to have size 4");
        }
#endif
        Math::Quaternion<T> r;
        for (int i=0;i<4;i++) {
            r[i] = Read<T>(ELM_KEY);
        }
        End(key);
        return r;
    }

    template <int N, class T> 
    Math::Vector<N,T> ReadVector(std::string key) {
        size_t size = Begin(key);
#ifdef OE_SAFE
        if (size != N) {
            std::ostringstream os;
            os << "Deserialization size mismatch in ReadVector [";
            os << size << "] ";
            os << "should be";
            os << " [" << N << "]";
            throw Core::Exception(os.str());
        }
#endif
        Math::Vector<N,T> r;
        for (unsigned int i=0; i<N; i++) {
            r[i] = Read<T>(ELM_KEY);
        }
        End(key);
        return r;
    }    

    template <unsigned int M, unsigned int N, class T> 
    Math::Matrix<M,N,T> ReadMatrix(std::string key) {
        size_t rows = Begin(key);
#ifdef OE_SAFE
        if (rows != M)
            throw Core::Exception("Deserialization size mismatch in ReadMatrix");
#endif
        Math::Matrix<M,N,T> m;
        for (unsigned int i=0; i<M; i++) {
            m.SetRow(i, ReadVector<N,T>(ROW_KEY));
        }
        End(key);
        return m;
    }

    template <class C, class T>
    C ReadCollection(std::string key) {
        size_t size = Begin(key);
        C l;
        while(size--) {
            l.push_back(Read<T>(ELM_KEY));
        }
        End(key);
        return l;
    }

    template <class T>
    void ReadArray(std::string key, T* arr, size_t len) {
        size_t s = Begin(key);
#ifdef OE_SAFE
        if (s != len) {
            std::ostringstream os;
            os << "Deserialization size mismatch in ReadArray ["
               << key << "] should be: " << len << ", was: " << s;
            throw Core::Exception(os.str());
        }
#endif
        while(len--) {
            *(arr++) = Read<T>(ELM_KEY);
        }
        End(key);
        
    }

    std::map<unsigned int, ISerializable*> objects;

    // template <class T>
    // T* ReadObject(std::string key) {
    //     size_t s = Begin(key);
    //     unsigned int idx = ReadIndex();
    //     T* obj = (T*)(objects[idx]);
    //     if (!obj) {
    //         obj = new T();
    //         obj->Deserialize(*this);
    //         objects[idx] = obj;
    //     }
    //     End(key);
    //     return obj;
    // }


    std::map<unsigned int, boost::shared_ptr<ISerializable> > objectsPtr;

    // template <class T>
    // boost::shared_ptr<T> ReadObjectPtr(std::string key) {
    //     size_t s = Begin(key);
    //     unsigned int idx = ReadIndex();
    //     boost::shared_ptr<T> obj 
    //         = boost::static_pointer_cast<T>(objectsPtr[idx]);
    //     if (!obj.get()) {
    //         obj.reset(new T());
    //         obj->Deserialize(*this);
    //         objectsPtr[idx] = boost::static_pointer_cast<void>(obj);
    //     }
    //     End(key);
    //     return obj;
    // }

};



} // NS Resources
} // NS OpenEngine

#endif // _OE_I_ARCHIVE_READER_H_
