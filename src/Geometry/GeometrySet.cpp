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

        GeometrySet::GeometrySet() 
            : size(0), 
              vertices(IDataBlockPtr()), 
              normals(IDataBlockPtr()), 
              texCoords(), 
              colors(IDataBlockPtr()) {
        }

        GeometrySet::GeometrySet(IDataBlockPtr vertices,
                                 IDataBlockPtr normals,
                                 IDataBlockList texCoords,
                                 IDataBlockPtr colors)
            : vertices(vertices), normals(normals), texCoords(texCoords), colors(colors){                       

            if (vertices){
                attributeBlocks["vertex"] = vertices;
            }
            if (normals){
                attributeBlocks["normal"] = normals;
            }
            if (colors){
                attributeBlocks["color"] = colors;
            }
            IDataBlockList::const_iterator texs = texCoords.begin();
            for (unsigned int i = 0; texs != texCoords.end(); ++i, ++texs){
                attributeBlocks["texCoord" + Utils::Convert::ToString<unsigned int>(i)] = *texs;
            }

            if (attributeBlocks.begin() != attributeBlocks.end())
                size = attributeBlocks.begin()->second->GetSize();

#ifdef OE_SAFE
            if (normals != NULL && normals->GetSize() != size)
                throw Math::Exception("Normal block not of same size as vertex block");
            if (colors != NULL && colors->GetSize() != size)
                throw Math::Exception("Color block not of same size as vertex block");
            IDataBlockList::iterator itr = texCoords.begin();
            while (itr != texCoords.end()){
                IDataBlockPtr texcoord = *itr;
                if (texcoord != NULL && texcoord->GetSize() != size)
                    throw Math::Exception("Texcoord block not of same size as vertex block");
                ++itr;
            }
#endif
        }

        GeometrySetPtr GeometrySet::Clone() {            
            IDataBlockPtr v = vertices ? vertices->Clone() : IDataBlockPtr();
            IDataBlockPtr n = normals ? normals->Clone() : IDataBlockPtr();
            IDataBlockPtr c = colors ? colors->Clone() : IDataBlockPtr();

            IDataBlockList tcs;
            for (IDataBlockList::iterator itr = texCoords.begin();
                 itr != texCoords.end(); ++itr) {
                tcs.push_back((*itr)->Clone());
            }

            return GeometrySetPtr(new GeometrySet(v, n, tcs, c));
        }


        IDataBlockPtr GeometrySet::GetDebugNormals() {
#ifdef OE_SAFE
            if (vertices->GetType() != Types::FLOAT)
                throw Math::Exception("Cannot calculate debug normals of non float vertices.");
#endif
            if (debugNormals == NULL) {
                unsigned int size = vertices->GetSize();

                DataBlock<3, float>* ns = (DataBlock<3, float>*)normals.get();

                Float3DataBlockPtr dn = Float3DataBlockPtr(new DataBlock<3, float>(size * 2, 
                                                                                   new float[2 * 3 * size]));
                
                for (unsigned int i = 0; i < size; ++i){
                    Math::Vector<3, float> vert;
                    if (vertices->GetDimension() == 3){
                        DataBlock<3, float>* vs = (DataBlock<3, float>*)vertices.get();
                        vert = vs->GetElement(i);
                    } else if (vertices->GetDimension() == 4){
                        DataBlock<4, float>* vs = (DataBlock<4, float>*)vertices.get();
                        Math::Vector<4, float> v = vs->GetElement(i);
                        vert = Math::Vector<3, float>(v[0], v[1], v[2]);
                    }
                    
                    Math::Vector<3, float> norm = ns->GetElement(i);
                    
                    dn->SetElement(2 * i, vert);
                    dn->SetElement(2 * i + 1, vert + norm);
                }

                debugNormals = dn;
            }
            return debugNormals; 
        }        

    }
}
