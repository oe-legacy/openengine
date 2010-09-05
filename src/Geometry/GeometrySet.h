// GeometrySet.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_SET_H_
#define _GEOMETRY_SET_H_

#include <Resources/DataBlock.h>
#include <Geometry/Vertex.h>
#include <Utils/Convert.h>
#include <boost/shared_ptr.hpp>
#include <list>
#include <vector>
#include <Logging/Logger.h>

using std::list;
using std::vector;

namespace OpenEngine {
    namespace Geometry{

        /**
         * Forward decleration used for shared pointer.
         */
        class GeometrySet;

        /**
         * Shared pointer
         */
        typedef boost::shared_ptr<GeometrySet> GeometrySetPtr;

        /**
         * The geometry set class contains all of the pr. vertex
         * information of a mesh.
         */
        class GeometrySet {
        protected:
            unsigned int size;
            map<string, IDataBlockPtr> attributeBlocks;

            Resources::IDataBlockPtr debugNormals;

        public:
            GeometrySet();
            
            GeometrySet(Resources::IDataBlockPtr vertices,
                 Resources::IDataBlockPtr normals = Resources::IDataBlockPtr(),
                 Resources::IDataBlockList texCoords = Resources::IDataBlockList(),
                 Resources::IDataBlockPtr colors = Resources::IDataBlockPtr());

            GeometrySet(map<string, IDataBlockPtr> attrBlocks);

            /**
             * Clones the data in the geometry set.
             *
             * @return A new GeometrySet with the cloned data.
             */
            GeometrySetPtr Clone();

            /**
             * Get the size of each IDataBlock in the GeometrySet.
             */
            inline unsigned int GetSize() const { return size; }

            /**
             * Get vertices.
             */
            inline Resources::IDataBlockPtr GetVertices() const { return GetDataBlock("vertex"); }

            /**
             * Get normals.
             */
            inline Resources::IDataBlockPtr GetNormals() const { return GetDataBlock("normal"); }

            /**
             * Get colors.
             */
            inline Resources::IDataBlockPtr GetColors() const { return GetDataBlock("color"); }

            /**
             * Get list of texcoords.
             */
            inline Resources::IDataBlockList GetTexCoords() const { 
                Resources::IDataBlockList list;
                unsigned int count = 0;
                map<string, IDataBlockPtr>::const_iterator itr = attributeBlocks.find("texCoord0");
                while (itr != attributeBlocks.end()) {
                    list.push_back(itr->second);
                    ++count;
                    itr = attributeBlocks.find("texCoord" + Utils::Convert::ToString<unsigned int>(count));
                }
                return list;
            }

            /**
             * Get IDataBlockPtr corrosponding to given attribute name.
             */
            inline Resources::IDataBlockPtr GetDataBlock(const std::string name) const { 
                map<string, IDataBlockPtr>::const_iterator itr = attributeBlocks.find(name);
                if (itr == attributeBlocks.end()) return Resources::IDataBlockPtr();
                return itr->second;
            }

            /**
             * Get IDataBlockPtr corrosponding to given attribute name.
             */
            inline map<string, IDataBlockPtr> GetDataBlocks() const { 
                return attributeBlocks;
            }

            /**
             * Get a list of lines representing the normals.
             */
            Resources::IDataBlockPtr GetDebugNormals();

            template <class T> Vertex<T> GetVertex(const unsigned int index) const {
                std::map<std::string, Vector<4, T> > attrs;
                Vector<4, T> attr;
                map<string, IDataBlockPtr>::const_iterator itr = attributeBlocks.begin();
                while (itr != attributeBlocks.end()){
                    itr->second->GetElement(index, attr);
                    attrs[itr->first] = attr;
                    ++itr;
                }
                return Vertex<T>(attrs);
            }

            inline std::string ToString() const {
                std::ostringstream out;
                out << "{";
                for (unsigned int i = 0; i < size; ++i){
                    out << GetVertex<float>(i).ToString();
                    out << "\n";
                }
                out << "}";
                return out.str();
            }

        };

    }
}

#endif
