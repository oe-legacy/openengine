// Serialization functions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_UTIL_SERIALIZATION_H_
#define _OE_UTIL_SERIALIZATION_H_

#include <iostream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#define ELM_KEY "elm"
#define ROW_KEY "row"
#define TAG_KEY "tag"
#define CHILD_KEY "children"
#define IDX_KEY "idx"
#define OBJ_TAG "obj"

//#define TREE_KEY "tree"

namespace OpenEngine {
namespace Resources {

using std::istream;
using std::ostream;

/**
 * Serialization functions for objects and streams.
 * This utility class must be used for serialization otherwise
 * compilation will not be possible when using serialization on
 * several structures.
 *
 * The objects on which it is used must implement the serialize
 * template method. See Scene/GeometryNode.h for a reference
 * implementation.
 *
 * @class Serialization Serialization.h Resources/Serialization.h
 */
// class Serialization {
// public:

//     /**
//      * Serialize an object to a stream.
//      *
//      * @param obj Object supporting serialization.
//      * @param out Output stream.
//      */
//     template <class T> static void Serialize(const T& obj, ostream* out) {
//         boost::archive::binary_oarchive oa(*out);
//         oa << obj;
//     }

//     /**
//      * Recreate a serialized object from a stream.
//      *
//      * @param obj Object supporting serialization.
//      * @param in  Input stream.
//      */
//     template <class T> static void Deserialize(T& obj, istream* in) {
//         boost::archive::binary_iarchive ia(*in);
//         ia >> obj;
//     }
// };

} // NS Resources
} // NS OpenEngine

#endif // _OE_UTIL_SERIALIZATION_H_
