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

namespace OpenEngine {
namespace Geometry {

class FaceSet;

/**
 * Vertex Array.
 *
 * @class VertexArray VertexArray.h Geometry/VertexArray.h
 */
class VertexArray {
private:
    float* pVertices;           //!< Pointer to vertex array
    float* pNormals;            //!< Pointer to normal array
    float* pColors;             //!< Pointer to color array
    float* pTexCoords;          //!< Pointer to texture coordinate array

    int numFaces;

    void Init();
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
};

} // NS Geometry
} // NS OpenEngine


#endif // _VERTEX_ARRAY_H_
