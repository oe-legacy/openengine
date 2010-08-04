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
#include <boost/shared_ptr.hpp>
#include <list>

using std::list;

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
            Resources::IDataBlockPtr vertices;
            Resources::IDataBlockPtr normals;
            Resources::IDataBlockList texCoords;
            Resources::IDataBlockPtr colors;

            Resources::IDataBlockPtr debugNormals;

            //map<string, IDataBlockPtr> vertexAttrib;

        public:
            GeometrySet();
            
            GeometrySet(Resources::IDataBlockPtr vertices,
                 Resources::IDataBlockPtr normals = Resources::IDataBlockPtr(),
                 Resources::IDataBlockList texCoords = Resources::IDataBlockList(),
                 Resources::IDataBlockPtr colors = Resources::IDataBlockPtr());

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
            inline Resources::IDataBlockPtr GetVertices() const { return vertices; }

            /**
             * Get normals.
             */
            inline Resources::IDataBlockPtr GetNormals() const { return normals; }

            /**
             * Get colors.
             */
            inline Resources::IDataBlockPtr GetColors() const { return colors; }

            /**
             * Get list of texcoords.
             */
            inline Resources::IDataBlockList GetTexCoords() const { return texCoords; }

            /**
             * Get a list of lines representing the normals.
             */
            Resources::IDataBlockPtr GetDebugNormals();

            template <class T> Vertex<T> GetVertex(const unsigned int index) const {
                std::map<std::string, Vector<4, T> > attrs;
                Vector<4, T> attr;
                if (vertices){
                    vertices->GetElement(index, attr);
                    attrs["vertex"] = attr;
                }
                if (normals){
                    normals->GetElement(index, attr);
                    attrs["normal"] = attr;
                }
                if (colors){
                    colors->GetElement(index, attr);
                    attrs["color"] = attr;
                }
                Resources::IDataBlockList::const_iterator itr = texCoords.begin();
                for (unsigned int i = 0; itr != texCoords.end(); ++i, ++itr){
                    (*itr)->GetElement(index, attr);
                    attrs["texCoord" + Utils::Convert::ToString<unsigned int>(i)] = attr;
                }

                return attrs;
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
