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
            : size(0) {
            attributeBlocks.clear();
        }

        GeometrySet::GeometrySet(IDataBlockPtr vertices,
                                 IDataBlockPtr normals,
                                 IDataBlockList texCoords,
                                 IDataBlockPtr colors) {
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

#if OE_SAFE
            map<string, IDataBlockPtr>::const_iterator itr = attributeBlocks.begin();
            while (itr != attributeBlocks.end()){
                if (itr->second->GetSize() != size)
                    throw Math::Exception(itr->first + "DataBlock not of same size as " + attributeBlocks.begin()->first +  " block");
                ++itr;
            }
#endif
        }

        GeometrySet::GeometrySet(map<string, IDataBlockPtr> attrBlocks) 
            : attributeBlocks(attrBlocks) {}

        GeometrySetPtr GeometrySet::Clone() {
            map<string, IDataBlockPtr> newBlocks;
            map<string, IDataBlockPtr>::const_iterator itr = attributeBlocks.begin();
            while (itr != attributeBlocks.end()){
                newBlocks[itr->first] = itr->second->Clone();
                ++itr;
            }

            return GeometrySetPtr(new GeometrySet(newBlocks));
        }


        IDataBlockPtr GeometrySet::GetDebugNormals() {
            if (debugNormals == NULL) {
                IDataBlockPtr normals;
                if (attributeBlocks.find("normal") == attributeBlocks.end())
                    return IDataBlockPtr();
                else
                    normals = attributeBlocks.find("normal")->second;

                IDataBlockPtr vertices;
                if (attributeBlocks.find("vertex") == attributeBlocks.end())
                    return IDataBlockPtr();
                else
                    vertices = attributeBlocks.find("vertex")->second;

                Float3DataBlockPtr dn = Float3DataBlockPtr(new DataBlock<3, float>(size * 2, 
                                                                                   new float[2 * 3 * size]));
                
                for (unsigned int i = 0; i < size; ++i){
                    Math::Vector<3, float> vert;
                    vertices->GetElement(i, vert);
                    
                    Math::Vector<3, float> norm;
                    normals->GetElement(i, norm);
                    
                    dn->SetElement(2 * i, vert);
                    dn->SetElement(2 * i + 1, vert + norm);
                }

                debugNormals = dn;
            }
            return debugNormals; 
        }        

    }
}
