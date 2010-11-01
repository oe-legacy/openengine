// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_I_REFLECTABLE_H_
#define _OE_I_REFLECTABLE_H_


namespace OpenEngine {
namespace Core {

/**
 * Interface for reflectable objects.
 * 
 * See extensions/Reflect
 *
 * @class IReflectable IReflectable.h Core/IReflectable.h
 */
class IReflectable {
public:
    virtual ~IReflectable() {}
};

} // NS Core
} // NS OpenEngine

#endif // _OE_I_RELECTABLE_H_
