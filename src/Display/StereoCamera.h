// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_STEREO_CAMERA_H_
#define _OE_STEREO_CAMERA_H_

#include <Display/Camera.h>
#include <Display/ViewingVolume.h>
#include <Logging/Logger.h>
#include <Renderers/IRenderer.h>

namespace OpenEngine {
namespace Display {

using namespace OpenEngine::Renderers;

/**
 * Short description.
 *
 * @class StereoCamera StereoCamera.h ts/Boids/StereoCamera.h
 */
class StereoCamera : public Camera {
private:
    Matrix<4,4,float> vm;
    Matrix<4,4,float> pm;
    
    ViewingVolume* right;

public:
    float dist;

    StereoCamera(IViewingVolume& volume) : Camera(volume),dist(10) {
        right = new ViewingVolume();
    }
    virtual void SignalRendering(const float dt) {
         volume.SignalRendering(dt);
         
         //logger.info << "signal" << logger.end;
         Vector<3,float> pos = volume.GetPosition();
         Quaternion<float> rot = volume.GetDirection();
         right->SetPosition(pos + rot.RotateVector(Vector<3,float>(dist,0,0)));
         right->SetDirection(rot);
     }


    IViewingVolume* GetLeft() {
        return this;
    }
    IViewingVolume* GetRight() {
        return right;
    }
    

};

}
}

#endif // _OE_STEREO_CAMERA_H_
