// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#ifndef _OE_I_ARCHIVE_WRITER_H_
#define _OE_I_ARCHIVE_WRITER_H_

#include <Resources/Serialization.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>
#include <boost/shared_ptr.hpp>

#include <string>
#include <map>

namespace OpenEngine {

namespace Scene {
class ISceneNode;
}

namespace Resources {

class ISerializable;

/**
 * Short description.
 *
 * @class IArchiveWriter IArchiveWriter.h Resources/IArchiveWriter.h
 */
class IArchiveWriter {
private:
    template <class T>
    void Write(std::string key, T in);

protected:
    virtual void Begin(std::string key, size_t len) = 0;
    virtual void End(std::string key) = 0;
    virtual void WriteIndex(unsigned int idx) = 0;
public:
    virtual ~IArchiveWriter() {}
    virtual void WriteInt(std::string key, int in) = 0;
    virtual void WriteFloat(std::string key, float in) = 0;
    virtual void WriteDouble(std::string key, double in) = 0;
    virtual void WriteString(std::string key, std::string str) = 0;

    virtual void WriteScene(std::string key, Scene::ISceneNode* node) = 0;
    void WriteObject(std::string key, ISerializable* obj);
    void WriteObjectPtr(std::string key, boost::shared_ptr<ISerializable> obj);

    template <class T>
    void WriteQuaternion(std::string key, Math::Quaternion<T> q) {
        Begin(key,4);

        for (unsigned int i=0;i<4;i++) {            
            Write<T>(ELM_KEY,q[i]);
        }

        End(key);
    }


    template <int N, class T>
    void WriteVector(std::string key, Math::Vector<N,T> v) {
        Begin(key,N);

        for (unsigned int i=0;i<N;i++) {            
            Write<T>(ELM_KEY,v[i]);
        }

        End(key);
    }

    template <unsigned int M, unsigned int N, class T>
    void WriteMatrix(std::string key, Math::Matrix<M,N,T> matrix) {
        Begin(key, M);        
        for (unsigned int i=0; i<M; i++) {
            WriteVector<N,T>(ROW_KEY, matrix[i]);            
        }
        End(key);        
    }

    template <class C, class T>
    void WriteCollection(std::string key, C l) {
        size_t size = l.size();
        Begin(key, size);

        typename C::iterator itr;
        for(itr = l.begin();
            itr != l.end();
            itr++) {
            Write<T>(ELM_KEY,*itr);
        }
        End(key);
    }

    template <class T>
    void WriteArray(std::string key, T* arr, size_t len) {
        Begin(key,len);
        
        while(len--) {
            Write<T>(ELM_KEY,*(arr++));
        }

        End(key);
    }
    
    std::map<ISerializable*, unsigned int> objects;
    std::map<ISerializable*, unsigned int> objectsPtr;

    /*
    template <class T>
    void WriteObject(std::string key, T* obj) {
        Begin(key,0);
        unsigned int idx = objects[obj];
        if (!idx) {
            unsigned int size = objects[obj] = objects.size();
            WriteIndex(size);
            obj->Serialize(*this);
        } else {
            WriteIndex(idx);
        }
        End(key);
    }

    std::map<void*, unsigned int> objectsPtr;

    template <class T>
    void WriteObjectPtr(std::string key, boost::shared_ptr<T> objPtr) {
        Begin(key,0);
        T* obj = objPtr.get();
        unsigned int idx = objectsPtr[obj];
        if (!idx) {
            unsigned int size = objectsPtr[obj] = objectsPtr.size();
            WriteIndex(size);
            obj->Serialize(*this);
        } else {
            WriteIndex(idx);
        }
        End(key);
    }
    */
};


} // NS Resources
} // NS OpenEngine

#endif // _OE_I_ARCHIVE_WRITER_H_
