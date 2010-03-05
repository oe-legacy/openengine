// OpenGL buffer object binder
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_BUFFER_OBJECT_BINDER_H_
#define _OE_BUFFER_OBJECT_BINDER_H_

#include <Renderers/IRenderer.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Core/IListener.h>

#include <Renderers/OpenGL/Renderer.h>

namespace OpenEngine {

    //forward declarations
    namespace Scene {
        class ModelNode;
        class ISceneNode;
    }

namespace Renderers {

using Core::IListener;
using Renderers::RenderingEventArg;
using Renderers::IRenderer;
using Scene::ModelNode;
using Scene::ISceneNode;

/**
 * Bind buffer object in OpenGL
 *
 * @class BufferObjectBinder BufferObjectBinder.h Renderers/OpenGL/BufferObjectBinder.h
 */
class BufferObjectBinder: public ISceneNodeVisitor, public IListener<RenderingEventArg> {
 private:
    IRenderer& r;
 public:

    BufferObjectBinder(IRenderer& r);
    virtual ~BufferObjectBinder();
        
    void Handle(RenderingEventArg arg);
    void VisitModelNode(ModelNode* node);
        
};

} // NS OpenEngine
} // NS Renderers

#endif
