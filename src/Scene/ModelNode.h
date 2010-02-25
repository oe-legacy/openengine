// Model node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MODEL_NODE_H_
#define _MODEL_NODE_H_

#include <boost/shared_ptr.hpp>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

namespace OpenEngine {
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
    namespace Resources {
        struct Indices;
    }
    namespace Scene {

        class ModelNode{
        protected:
            Geometry::MeshPtr mesh;
            vector<pair<Resources::Indices, Geometry::MaterialPtr> > mats;

        public:
            ModelNode();
            ModelNode(Geometry::MeshPtr g);

            inline Geometry::MeshPtr GetMesh() const;

            inline void AddIndices(Resources::Indices, Geometry::MaterialPtr);
            inline void RemoveIndice(unsigned int i);

            

        };

    }
}

#endif
