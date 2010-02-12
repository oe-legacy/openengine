// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#ifndef _OE_SERIALIZABLE_OBJECTS_TAGS_H_
#define _OE_SERIALIZABLE_OBJECTS_TAGS_H_


namespace OpenEngine {
namespace Resources {
    
enum SerializableObjectTags {
#define S_OBJECT(ns,klass) \
    S_OBJ_##ns##_##klass,
#include <Resources/SerializableObjects.def>
#undef S_OBJECT
    S_OBJ_END
};

} // NS Resources

#define S_OBJECT(ns,klass)                           \
    namespace ns {                                   \
        unsigned int klass::GetSerialzationTag() {   \
        return Resources::S_OBJ_##ns##_##klass;          \
        }                                            \
    }
#include <Resources/SerializableObjects.def>
#undef S_OBJECT


} // NS OpenEngine

#endif // _OE_SERIALIZABLE_OBJECTS_TAGS_H_
