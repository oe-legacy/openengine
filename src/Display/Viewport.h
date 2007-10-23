// Viewport.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <Display/IViewingVolume.h>
#include <Display/IFrame.h>

namespace OpenEngine {
namespace Display {

/**
 * Short description.
 *
 * @class Viewport Viewport.h Display/Viewport.h
 */
class Viewport {

private:

    IViewingVolume* volume;     //!< viewport viewing volume
    Vector<4,int>   dim;        //!< viewport dimensions

public:

    Viewport(const IFrame& frame);
    Viewport(const int width, const int height);
    Viewport(const int x1, const int y1, const int x2, const int y2);
    virtual ~Viewport();

    void SetDimension(const int x1, const int y1, const int x2, const int y2);
    void SetViewingVolume(IViewingVolume* volume);
    Vector<4,int> GetDimension();
    IViewingVolume* GetViewingVolume();

};

} // NS Display
} // NS OpenEngine

#endif // _VIEWPORT_H_
