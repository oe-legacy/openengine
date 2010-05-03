// Canvas Queue
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CANVAS_QUEUE_H_
#define _CANVAS_QUEUE_H_

#include <Display/ICanvas.h>
#include <deque>

namespace OpenEngine {
namespace Display {

using std::deque;

/**
 * Canvas Queue 
 *
 * A canvas queue represents a sequence of interdependent canvases,
 * meaning that canvas i+1 is processed before canvas i. The resulting
 * texture of this canvas will then be equal to the texture of the
 * first canvas in the queue.
 * 
 * @class CanvasQueue CanvasQueue.h Display/CanvasQueue.h
 */
class CanvasQueue : public ICanvas {
private:
    deque<ICanvas*> canvases;
public:
    CanvasQueue();
    virtual ~CanvasQueue();

    void Handle(Display::InitializeEventArg arg);
    void Handle(Display::ProcessEventArg arg);
    void Handle(Display::ResizeEventArg arg);
    void Handle(Display::DeinitializeEventArg arg);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void SetWidth(const unsigned int width);
    void SetHeight(const unsigned int height);
    ITexture2DPtr GetTexture();

    void PushCanvas(ICanvas* canvas);
};

} // NS Display
} // NS OpenEngine

#endif // _CANVAS_QUEUE_H_
