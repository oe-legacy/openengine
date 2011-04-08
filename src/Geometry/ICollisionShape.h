// Common interface for Collision Geometry.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_COLLISION_SHAPE_H_
#define _OE_INTERFACE_COLLISION_SHAPE_H_

namespace OpenEngine {
namespace Geometry {

/**
 * Collision Geometry Interface.  
 *
 * The purpose of this interface is simply to provide a common super
 * type for collision geometry.
 * 
 * @class ICollisionShape ICollisionShape.h Geometry/ICollisionShape.h
 */
class ICollisionShape {
public:
    virtual ~ICollisionShape() {};
};

} // NS Geometry
} // NS OpenEngine

#endif //_OE_INTERFACE_COLLISION_SHAPE_H_
