// Data Blockbinder
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/DataBlockBinder.h>

#include <Scene/ModelNode.h>
#include <Geometry/Model.h>
#include <Geometry/DrawPrimitive.h>
#include <Geometry/Mesh.h>


namespace OpenEngine {
namespace Renderers {

    using namespace Scene;
    using namespace Geometry;

    DataBlockBinder::DataBlockBinder(IRenderer& r)
        :r(r) {
        
    }
    
    DataBlockBinder::~DataBlockBinder() {

    }
        
    void DataBlockBinder::Handle(RenderingEventArg arg) {
        r = arg.renderer;
        r.GetSceneRoot()->Accept(*this);
    }
    
    void DataBlockBinder::VisitModelNode(ModelNode* node) {
        Model* model = node->model;
        DrawPrimitiveList prims = model->GetDrawPrimitives();
        DrawPrimitiveList::iterator prim = prims.begin();
        for (; prim != prims.end(); ++prim) {
            if ((*prim)->GetIndexBuffer() && (*prim)->GetIndexBuffer()->GetID() == 0)
                r.BindDataBlock((*prim)->GetIndexBuffer().get());

            MeshPtr mesh = (*prim)->GetMesh();
            if (mesh->GetVertices() && mesh->GetVertices()->GetID() == 0)
                r.BindDataBlock(mesh->GetVertices().get());
            if (mesh->GetNormals() && mesh->GetNormals()->GetID() == 0)
                r.BindDataBlock(mesh->GetNormals().get());
            if (mesh->GetColors() && mesh->GetColors()->GetID() == 0) 
                r.BindDataBlock(mesh->GetColors().get());
          
            IDataBlockList tl = mesh->GetTexCoords();
            IDataBlockList::iterator texc = tl.begin();
            for (; texc != tl.end(); ++texc) {
                if (*texc && (*texc)->GetID() == 0)
                    r.BindDataBlock((*texc).get());
            }
        }
        node->VisitSubNodes(*this);
    }
    
} // NS OpenEngine
} // NS Renderers
