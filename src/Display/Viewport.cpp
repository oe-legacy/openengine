// Viewport.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/Viewport.h>
#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Display {

using OpenEngine::Core::InvalidArgument;

/**
 * Create viewport spanning the entire frame.
 *
 * @param frame Frame to span.
 */
Viewport::Viewport(const IFrame& frame) : volume(NULL) {
    SetDimension(0, 0, frame.GetWidth(), frame.GetHeight());
}

/**
 * Create a viewport of width and height.
 *
 * @param width Width of viewport.
 * @param height Height of viewport.
 */
Viewport::Viewport(const int width, const int height) : volume(NULL) {
    SetDimension(0, 0, width, height);
}

/**
 * Create viewport in bounding box.
 * Same semantic as calling \a SetDimension() after creation.
 * 
 * @see SetDimension()
 */
Viewport::Viewport(const int x1, const int y1, const int x2, const int y2) : volume(NULL) {
    SetDimension(x1, y1, x2, y2);
}


/**
 * Destructor.
 */
Viewport::~Viewport() {
    
}

/**
 * Set dimensions of viewport bounding box.
 * Takes two coordinate pairs - \a x1,\a y1 and \a x2,\a y2 - and
 * creates a viewport spanning the resulting box.
 * 
 * @note The implementation works regardless of pair order. The
 *       call ViewportImpl(1,1 , 10,10) has the  exact same
 *       outcome as Viewport(10,10 , 1,1), Viewport(1,10 , 10,1)
 *       and Viewport(10,1 , 1,10). 
 *
 * @param x1 x coordinate of first pair
 * @param y1 y coordinate of first pair
 * @param x2 x coordinate of second pair
 * @param y2 y coordinate of second pair
 */
void Viewport::SetDimension(const int x1, const int y1, const int x2, const int y2) {
    int x = std::min(x1, x2);
    int y = std::min(y1, y2);
    if (x < 0 || y < 0)
        throw InvalidArgument("Camera dimensions must be non-negative.");
    int w = std::max(x1, x2) - x;
    int h = std::max(y1, y2) - y;
    dim = Vector<4,int>(x, y, w, h);
}

/**
 * Get viewport dimensions.
 * The returned vector \a v corresponds to two pairs spanning the
 * viewport bounding box: (v(0), v(1)) and (v(2), v(3)).
 * The order of the pairs does not necessary match the order they
 * were given to \a SetDimension().
 *
 * @return Point-pair of the viewports bounding box
 */
Vector<4,int> Viewport::GetDimension() {
    return dim;
}

/**
 * Set the viewing volume of the viewport.
 *
 * @param volume Viewing volume, NULL to unset the current volume.
 */
void Viewport::SetViewingVolume(IViewingVolume* volume) {
    this->volume = volume;
}

/**
 * Get the viewing volume of the viewport.
 *
 * @return Current viewing volume, NULL if no volume has been set.
 */
IViewingVolume* Viewport::GetViewingVolume() {
    return volume;
}


} // NS Display
} // NS OpenEngine
