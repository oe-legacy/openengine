// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------


#ifndef _OE_I_SERIALIZABLE_H_
#define _OE_I_SERIALIZABLE_H_

/**
 * Serializable object header macro.
 * This should be the first line in the definition of a serializable
 * object definition.
 */
#define OE_SERIALIZABLE_OBJECT(klass)           \
public:                                         \
virtual unsigned int GetSerialzationTag();      \
private:

#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>

namespace OpenEngine {
namespace Resources {

/**
 * Short description.
 *
 * @class ISerializable ISerializable.h ils/ISerializable.h
 */
class ISerializable {
private:

public:
    virtual void Serialize(IArchiveWriter&) = 0;
    virtual void Deserialize(IArchiveReader&) = 0;
    virtual unsigned int GetSerialzationTag() = 0;
};

} // NS Resources
} // NS OpenEngine

#endif // _OE_I_SERIALIZABLE_H_
