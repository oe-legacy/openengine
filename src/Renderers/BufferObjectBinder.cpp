// OpenGL buffer object binder
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/BufferObjectBinder.h>

#include <Scene/ModelNode.h>
#include <Geometry/Model.h>
#include <Geometry/DrawPrimitive.h>
#include <Geometry/Mesh.h>


namespace OpenEngine {
namespace Renderers {

    using namespace Scene;
    using namespace Geometry;

    BufferObjectBinder::BufferObjectBinder(IRenderer& r)
        :r(r) {
        
    }
    
    BufferObjectBinder::~BufferObjectBinder() {

    }
        
    void BufferObjectBinder::Handle(RenderingEventArg arg) {
        r = arg.renderer;
        r.GetSceneRoot()->Accept(*this);
    }
    
    void BufferObjectBinder::VisitModelNode(ModelNode* node) {
        Model* model = node->model;
        DrawPrimitiveList prims = model->GetDrawPrimitives();
        DrawPrimitiveList::iterator prim = prims.begin();
        for (; prim != prims.end(); ++prim) {
            if ((*prim)->GetIndexBuffer())
                r.BindBufferObject((*prim)->GetIndexBuffer().get());

            MeshPtr mesh = (*prim)->GetMesh();
            if (mesh->GetVertices())
                r.BindBufferObject(mesh->GetVertices().get());
            if (mesh->GetNormals())
                r.BindBufferObject(mesh->GetNormals().get());
            if (mesh->GetColors()) 
                r.BindBufferObject(mesh->GetColors().get());
          
            IBufferObjectList tl = mesh->GetTexCoords();
            IBufferObjectList::iterator texc = tl.begin();
            for (; texc != tl.end(); ++texc) {
                if (*texc)
                    r.BindBufferObject((*texc).get());
            }
        }
        node->VisitSubNodes(*this);
    }
    
} // NS OpenEngine
} // NS Renderers
