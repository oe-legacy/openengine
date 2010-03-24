// Data Blockbinder
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/DataBlockBinder.h>

#include <Scene/MeshNode.h>
#include <Geometry/Model.h>
#include <Geometry/Mesh.h>
#include <Geometry/GeometrySet.h>
#include <Resources/DataBlock.h>


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
    
    void DataBlockBinder::VisitMeshNode(MeshNode* node) {
        MeshPtr mesh = node->GetMesh();

        if (mesh->GetIndices() && mesh->GetIndices()->GetID() == 0)
            r.BindDataBlock(mesh->GetIndices().get());
        
        GeometrySetPtr geom = mesh->GetGeometrySet();
        if (geom->GetVertices() && geom->GetVertices()->GetID() == 0)
            r.BindDataBlock(geom->GetVertices().get());
        if (geom->GetNormals() && geom->GetNormals()->GetID() == 0)
            r.BindDataBlock(geom->GetNormals().get());
        if (geom->GetColors() && geom->GetColors()->GetID() == 0) 
            r.BindDataBlock(geom->GetColors().get());
        
        IDataBlockList tl = geom->GetTexCoords();
        IDataBlockList::iterator texc = tl.begin();
        for (; texc != tl.end(); ++texc) {
            if (*texc && (*texc)->GetID() == 0)
                r.BindDataBlock((*texc).get());
        }

        node->VisitSubNodes(*this);
    }
    
} // NS OpenEngine
} // NS Renderers
