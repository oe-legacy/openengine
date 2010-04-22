// Stereo camera implementation
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _STEREO_CAMERA_H_
#define _STEREO_CAMERA_H_

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
    ViewingVolume* left;
    ViewingVolume* right;
    float eyedist, halfdist;
public:

    StereoCamera(IViewingVolume& volume) : Camera(volume), eyedist(1.0), halfdist(0.5 * eyedist) {
        left = new ViewingVolume();
        right = new ViewingVolume();
    }

    ~StereoCamera() {
        delete left;
        delete right;
    }

    virtual void SignalRendering(const float dt) {
         volume.SignalRendering(dt);
         // Vector<3,float> pos = volume.GetPosition();
         // Quaternion<float> rot = volume.GetDirection();
         // right->SetPosition(pos + rot.RotateVector(Vector<3,float>(dist,0,0)));
         // right->SetDirection(rot);
     }

    IViewingVolume* GetLeft() {
        Vector<3,float> pos = volume.GetPosition();
        Quaternion<float> rot = volume.GetDirection();
        left->SetPosition(pos + rot.RotateVector(Vector<3,float>(-halfdist,0,0)));
        left->SetDirection(rot);
        return left;
    }

    IViewingVolume* GetRight() {
         Vector<3,float> pos = volume.GetPosition();
         Quaternion<float> rot = volume.GetDirection();
         right->SetPosition(pos + rot.RotateVector(Vector<3,float>(halfdist,0,0)));
         right->SetDirection(rot);
        return right;
    }
    
    void SetEyeDistance(float dist) {
        eyedist = dist;
        halfdist = 0.5 * eyedist;
    }

    float GetEyeDistance() {
        return eyedist;
    }

    void SetViewingVolume(IViewingVolume& v) {
        volume = v;
    }
};

}
}

#endif // _STEREO_CAMERA_H_
