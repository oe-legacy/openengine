// Canvas Queue
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/CanvasQueue.h>

namespace OpenEngine {
namespace Display {

    CanvasQueue::CanvasQueue() {

    }
    
    CanvasQueue::~CanvasQueue() {

    }

    void CanvasQueue::Handle(Display::InitializeEventArg arg) {
        deque<ICanvas*>::reverse_iterator i = canvases.rbegin();
        for (; i != canvases.rend(); ++i) {
            ((IListener<Display::InitializeEventArg>*)*i)->Handle(arg);
        }
    }
    
    void CanvasQueue::Handle(Display::ProcessEventArg arg) {
        deque<ICanvas*>::reverse_iterator i = canvases.rbegin();
        for (; i != canvases.rend(); ++i) {
            ((IListener<Display::ProcessEventArg>*)*i)->Handle(arg);
        }
    }
    
    void CanvasQueue::Handle(Display::ResizeEventArg arg) {
        deque<ICanvas*>::reverse_iterator i = canvases.rbegin();
        for (; i != canvases.rend(); ++i) {
            ((IListener<Display::ResizeEventArg>*)*i)->Handle(arg);
        }
    }
    
    void CanvasQueue::Handle(Display::DeinitializeEventArg arg) {
        deque<ICanvas*>::reverse_iterator i = canvases.rbegin();
        for (; i != canvases.rend(); ++i) {
            ((IListener<Display::DeinitializeEventArg>*)*i)->Handle(arg);
        }
    }

    unsigned int CanvasQueue::GetWidth() const {
        return canvases.front()->GetWidth();

    }
    
    unsigned int CanvasQueue::GetHeight() const {
        return canvases.front()->GetHeight();
    }
    
    void CanvasQueue::SetWidth(const unsigned int width) {
        canvases.front()->SetWidth(width);
    }
    
    void CanvasQueue::SetHeight(const unsigned int height) {
        canvases.front()->SetHeight(height);
    }
    
    ITexture2DPtr CanvasQueue::GetTexture() {
        return canvases.front()->GetTexture();
    }

    void CanvasQueue::PushCanvas(ICanvas* canvas) {
        canvases.push_back(canvas);
    }

} // NS Display
} // NS OpenEngine
