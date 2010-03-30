// Mesh node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MESH_NODE_H_
#define _OE_MESH_NODE_H_

#include <Scene/ISceneNode.h>

#include <boost/shared_ptr.hpp>

namespace OpenEngine {
    namespace Geometry {
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
    namespace Scene {
        
        using Geometry::MeshPtr;

        /**
         * Mesh node.
         * Acts as a simple node wrapping a mesh.
         *
         * @class MeshNode MeshNode.h Scene/MeshNode.h
         */
        class MeshNode : public ISceneNode {
            OE_SCENE_NODE(MeshNode, ISceneNode)
        public:
            MeshNode();
            MeshNode(const MeshNode& node);
            explicit MeshNode(MeshPtr mesh);

            MeshPtr GetMesh() const;
            void SetMesh(MeshPtr mesh);

        protected:
            MeshPtr mesh;
            
        };
    }
}


#endif
