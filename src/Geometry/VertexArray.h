// Vertex Array
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_VERTEX_ARRAY_H_
#define _OE_VERTEX_ARRAY_H_

#include <Geometry/Material.h>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/extended_type_info.hpp>

namespace OpenEngine {
namespace Geometry {

class FaceSet;

/**
 * Vertex Array.
 *
 * @class VertexArray VertexArray.h Geometry/VertexArray.h
 */
class VertexArray {
public:
    VertexArray();
    explicit VertexArray(FaceSet& faces);
    virtual ~VertexArray();

    MaterialPtr mat;            //!< Shared material definition

    float* GetVertices();
    float* GetNormals();
    float* GetColors();
    float* GetTexCoords();

    int GetNumFaces();

private:
    float* pVertices;           //!< Pointer to vertex array
    float* pNormals;            //!< Pointer to normal array
    float* pColors;             //!< Pointer to color array
    float* pTexCoords;          //!< Pointer to texture coordinate array

    int numFaces;

    void Init();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & numFaces;
        for (int i=0; i<numFaces; i++) {
            ar & pVertices[i];
            ar & pNormals[i];
            ar & pColors[i];
            ar & pTexCoords[i];
        }
    }

};

} // NS Geometry
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Geometry::VertexArray)

#endif // _VERTEX_ARRAY_H_
