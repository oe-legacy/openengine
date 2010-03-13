// GeometrySet.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/GeometrySet.h>
#include <Resources/DataBlock.h>

using namespace OpenEngine::Resources;

namespace OpenEngine {
    namespace Geometry{

        GeometrySet::GeometrySet(IDataBlockPtr vertices,
                                 IDataBlockPtr normals,
                                 IDataBlockList texCoords,
                                 IDataBlockPtr colors)
            : vertices(vertices), normals(normals), texCoords(texCoords), colors(colors){
#ifdef OE_SAFE
            unsigned int size = vertices->GetSize();
            if (normals != NULL && normals->GetSize() != size)
                throw Exception("Normal block not of same size as vertex block");
            if (colors != NULL && colors->GetSize() != size)
                throw Exception("Color block not of same size as vertex block");
            IDataBlockList::iterator itr = texCoords.begin();
            while (itr != texCoords.end()){
                IDataBlockPtr texcoord = *itr;
                if (texcoord != NULL && texcoord->GetSize() != size)
                    throw Exception("Texcoord block not of same size as vertex block");
                ++itr;
            }
#endif
        }
        
        IDataBlockPtr GeometrySet::GetDebugNormals() {
#ifdef OE_SAFE
            if (vertices->GetType() != FLOAT)
                throw Exception("Cannot calculate debug normals of non float vertices.");
#endif
            if (debugNormals == NULL) {
                unsigned int size = vertices->GetSize();

                DataBlock<3, float>* ns = (DataBlock<3, float>*)normals.get();

                Float3DataBlockPtr dn = Float3DataBlockPtr(new DataBlock<3, float>(new float[2 * 3 * size], 
                                                                                   size * 2));
                
                for (unsigned int i = 0; i < size; ++i){
                    Vector<3, float> vert;
                    if (vertices->GetDimension() == 3){
                        DataBlock<3, float>* vs = (DataBlock<3, float>*)vertices.get();
                        vert = vs->GetElement(i);
                    } else if (vertices->GetDimension() == 4){
                        DataBlock<4, float>* vs = (DataBlock<4, float>*)vertices.get();
                        Vector<4, float> v = vs->GetElement(i);
                        vert = Vector<3, float>(v[0], v[1], v[2]);
                    }
                    
                    Vector<3, float> norm = ns->GetElement(i);
                    
                    dn->SetElement(2 * i, vert);
                    dn->SetElement(2 * i + 1, vert + norm * 50);
                }

                debugNormals = dn;
            }
            return debugNormals; 
        }        

    }
}
