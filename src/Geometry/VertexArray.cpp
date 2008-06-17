// Vertex Array
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------
 
#include <Geometry/VertexArray.h>
#include <Geometry/FaceSet.h>
#include <Geometry/Material.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;

VertexArray::VertexArray() {
    Init();
}

VertexArray::VertexArray(FaceSet& faces) {
    Init();
    // Set texture id, which should be the same for all faces in the set
    this->mat = (*faces.begin())->mat;
    int faceCount = faces.Size();
    // Create vertex array
    pVertices  = new float[faceCount*3*3];
    pNormals   = new float[faceCount*3*3];
    pColors    = new float[faceCount*3*4];
    pTexCoords = new float[faceCount*3*2];

    int index = 0;
    int texIndex = 0;
    int colorIndex = 0;
    for (FaceList::iterator itr = faces.begin(); itr != faces.end(); itr++) {
        FacePtr f = (*itr);
        // for each vertex ...
        for (int i=0; i<3; i++) {
             // Add each vertex and normal coordinate to array
            Vector<3,float> v = f->vert[i];
            Vector<3,float> n = f->norm[i];
            for(int j=0; j<3; j++) {
                pVertices[index] = v[j];
                pNormals[index]  = n[j];
                index++;
            }

            // Add texture coords to array
            Vector<2,float> t = f->texc[i];
            for( int j=0; j<2; j++ )
                pTexCoords[texIndex++] = t[j];

            // Add color components to array
            Vector<4,float> c = f->colr[i];
            for( int j=0; j<4; j++ )
                pColors[colorIndex++] = c[j];
        }
    }
    numFaces = faces.Size();
}


void VertexArray::Init() {
    pVertices = NULL;
    pNormals = NULL;
    pColors = NULL;
    pTexCoords = NULL;
    numFaces = 0;
}

VertexArray::~VertexArray() {
    if( pVertices ) delete[] pVertices;
    if( pNormals  ) delete[] pNormals;
    if( pColors   ) delete[] pColors;
    if( pTexCoords) delete[] pTexCoords;
}

float* VertexArray::GetVertices() {
    return pVertices;
}

int VertexArray::GetNumFaces() {
    return numFaces;
}

float* VertexArray::GetNormals() {
    return pNormals;
}
 

float* VertexArray::GetColors() {
    return pColors;
}

float* VertexArray::GetTexCoords() {
    return pTexCoords;
}

} // NS Gemometry
} // NS OpenEngine
