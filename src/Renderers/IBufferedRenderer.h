// Renderer that contains a buffered texture representation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_BUFFERED_RENDERER_H_
#define _OE_INTERFACE_BUFFERED_RENDERER_H_

#include <Renderers/IRenderer.h>

// forward declerations
namespace OpenEngine {
    namespace Resources{
        class ITexture2D;
        typedef boost::shared_ptr<ITexture2D> ITexture2DPtr;
    }
}

namespace OpenEngine {
namespace Renderers {

/**
 * Renderer that contains a buffered texture representation.
 *
 * @class IBufferedRenderer IBufferedRenderer.h Renderers/IBufferedRenderer.h
 */
class IBufferedRenderer : public virtual IRenderer {
public:
    /**
     * Get the texture representation of the current color buffer.
     *
     * @return Current color buffer
     */
    virtual Resources::ITexture2DPtr GetColorBuffer() const = 0;
};

} // NS Renderers
} // NS OpenEngine

#endif // _OE_INTERFACE_BUFFERED_RENDERER_H_
