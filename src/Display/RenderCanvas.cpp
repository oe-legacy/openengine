// Concrete Render canvas implementation
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/RenderCanvas.h>
#include <Display/IViewingVolume.h>
#include <Renderers/IRenderer.h>
#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Display {

using Core::Exception;

RenderCanvas::RenderCanvas(ICanvasBackend* backend)
    : IRenderCanvas(backend)
    , init(false)
{
}

RenderCanvas::~RenderCanvas() {   
}

void RenderCanvas::Handle(Display::InitializeEventArg arg) {
    if (init) return;
#if OE_SAFE
    if (renderer == NULL) throw new Exception("NULL renderer in RenderCanvas.");
#endif
    if (init) return;
    backend->Init(arg.canvas.GetWidth(), arg.canvas.GetHeight());
    vv->Update(arg.canvas.GetWidth(), arg.canvas.GetHeight());
    ((IListener<Renderers::InitializeEventArg>*)renderer)->Handle(Renderers::InitializeEventArg(*this));
    init = true;
}

void RenderCanvas::Handle(ResizeEventArg arg) {
        backend->SetDimensions(arg.canvas.GetWidth(), arg.canvas.GetHeight());
        vv->Update(arg.canvas.GetWidth(), arg.canvas.GetHeight());        
}

void RenderCanvas::Handle(Display::ProcessEventArg arg) {
#if OE_SAFE
    if (!init) throw new Exception("RenderCanvas not initialized.");
    if (renderer == NULL) throw new Exception("NULL renderer in RenderCanvas.");
#endif
    backend->Pre();
    ((IListener<Renderers::ProcessEventArg>*)renderer)
        ->Handle(Renderers::ProcessEventArg(*this, arg.start, arg.approx));
    backend->Post();
}

void RenderCanvas::Handle(DeinitializeEventArg arg) { 
    if (!init) return;
    ((IListener<Renderers::DeinitializeEventArg>*)renderer)->Handle(Renderers::DeinitializeEventArg(*this));
    backend->Deinit();
    init = false;
}

unsigned int RenderCanvas::GetWidth() const {
    return backend->GetTexture()->GetWidth();
}

unsigned int RenderCanvas::GetHeight() const {
    return backend->GetTexture()->GetHeight();
}
    
void RenderCanvas::SetWidth(const unsigned int width) {
    backend->SetDimensions(width, backend->GetTexture()->GetHeight());
}

void RenderCanvas::SetHeight(const unsigned int height) {
    backend->SetDimensions(backend->GetTexture()->GetWidth(), height);
}
    
ITexture2DPtr RenderCanvas::GetTexture() {
    return backend->GetTexture();
}


} // NS Display
} // NS OpenEngine
