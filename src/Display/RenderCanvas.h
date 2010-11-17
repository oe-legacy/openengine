// Concrete Render canvas implementation
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CONCRETE_RENDER_CANVAS_H_
#define _CONCRETE_RENDER_CANVAS_H_

#include <Display/IRenderCanvas.h>
#include <Math/Vector.h>

using OpenEngine::Math::Vector;

namespace OpenEngine {
namespace Display {
    class ICanvasBackend;


class RenderCanvas : public IRenderCanvas {
private:
    bool init;
    Vector<2,int> initSize;
public:
    RenderCanvas(ICanvasBackend* backend, 
                 Vector<2, int> initSize = (Vector<2, int>(0,0)));
    virtual ~RenderCanvas();

    void Handle(Display::InitializeEventArg arg);
    void Handle(Display::ProcessEventArg arg);
    void Handle(Display::ResizeEventArg arg);
    void Handle(Display::DeinitializeEventArg arg);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void SetWidth(const unsigned int width);
    void SetHeight(const unsigned int height);
    ITexture2DPtr GetTexture();
};

} // NS Display
} // NS OpenEngine

#endif // _CONCRETE_RENDER_CANVAS_H_
