// Texturing backend interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_CANVAS_BACKEND_H_
#define _INTERFACE_CANVAS_BACKEND_H_

#include <Resources/ITexture2D.h>

namespace OpenEngine {
namespace Display {

/**
 * Canvas backend.
 *
 * A canvas backend determines how the canvas texture will be
 * constructed and updated.
 *
 * @see ICanvas
 *
 * @class ICanvasBackend ICanvasBackend.h Display/ICanvasBackend.h
 */
class ICanvasBackend
{
public:
    virtual ~ICanvasBackend() {}
    
    virtual void Create(unsigned int width, unsigned int height) = 0;
    virtual void Init(unsigned int width, unsigned int height) = 0;
    virtual void Deinit() = 0;
    virtual void Pre() = 0;
    virtual void Post() = 0;
    virtual void SetDimensions(unsigned int width, unsigned int height) = 0;
    virtual Resources::ITexture2DPtr GetTexture() = 0;
    virtual ICanvasBackend* Clone() = 0;
};

} // NS Display
} // NS OpenEngine

#endif // _INTERFACE_CANVAS_H_
