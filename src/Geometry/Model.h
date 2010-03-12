// Model node.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MODEL_H_
#define _OE_MODEL_H_

#include <boost/shared_ptr.hpp>
#include <list>

using std::list;

namespace OpenEngine {
    namespace Geometry{
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;
        typedef list<MeshPtr> MeshList;

        /**
         * Model class. Contains a list of draw primitives.
         */
        class Model{
        protected:
            MeshList prims;

        public:
            Model();
            Model(MeshPtr prim);
            Model(MeshList prims);

            /**
             * Add a new draw primitive to the model.
             */
            void AddMesh(MeshPtr prim);

            /**
             * Get a list of all draw primitives.
             */
            inline MeshList GetMeshs() const { return prims; }

            /**
             * Removes the draw primitive specified by the iterator.
             */
            inline void RemoveMesh(MeshList::iterator prim){
                prims.erase(prim);
            }
            
        };

    }
}

#endif
