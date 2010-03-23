// Data Block binder
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_DATA_BLOCK_BINDER_H_
#define _OE_DATA_BLOCK_BINDER_H_

#include <Renderers/IRenderer.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Core/IListener.h>

//#include <Renderers/OpenGL/Renderer.h>

namespace OpenEngine {

    //forward declarations
    namespace Scene {
        class ModelNode;
        class MeshNode;
        class ISceneNode;
    }

namespace Renderers {

using Core::IListener;
using Renderers::RenderingEventArg;
using Renderers::IRenderer;
using Scene::ModelNode;
using Scene::MeshNode;
using Scene::ISceneNode;
using Scene::ISceneNodeVisitor;

/**
 * Bind Data blocks
 *
 * @class BufferObjectBinder BufferObjectBinder.h Renderers/OpenGL/BufferObjectBinder.h
 */
class DataBlockBinder: public ISceneNodeVisitor, 
                       public IListener<RenderingEventArg> {
 private:
    IRenderer& r;
 public:

    DataBlockBinder(IRenderer& r);
    virtual ~DataBlockBinder();
        
    void Handle(RenderingEventArg arg);
    void VisitMeshNode(MeshNode* node);
        
};

} // NS OpenEngine
} // NS Renderers

#endif
