// Follow camera.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "FollowCamera.h"

#include <Display/ViewingVolume.h>
#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Display {

using OpenEngine::Scene::TransformationNode;

/**
 * Follow camera constructor.
 *
 * @param volume Viewing volume to decorate.
 */
FollowCamera::FollowCamera(IViewingVolume& volume)
    : Camera(volume), follow(NULL) {
    local = new Camera(*(new ViewingVolume()));
}

/**
 * Follow camera destructor.
 * Cleans local state. Will not free the followed transformation
 * node.
 */
FollowCamera::~FollowCamera() {
    delete local;
}

// all these methods forward to the local volume
void FollowCamera::SetDirection(const Vector<3,float> dir, const Vector<3,float> up) {
    local->SetDirection(dir, up);
}
void FollowCamera::Move(const float l, const float t, const float v) {
    local->Move(l,t,v);
}
void FollowCamera::LookAt(const Vector<3,float> point) {
    local->LookAt(point);
}
void FollowCamera::LookAt(const float x, const float y, const float z) {
    local->LookAt(x,y,z);
}
void FollowCamera::Rotate(const float roll, const float pitch, const float yaw) {
    local->Rotate(roll, pitch, yaw);
}
void FollowCamera::Rotate(const float angle, const Vector<3,float> axis) {
    local->Rotate(angle, axis);
}
void FollowCamera::Rotate(const Quaternion<float> rotation) {
    local->Rotate(rotation);
}
void FollowCamera::SetPosition(const Vector<3,float> position) {
    local->SetPosition(position);
}
void FollowCamera::SetDirection(const Quaternion<float> direction) {
    local->SetDirection(direction);
}

/**
 * On every signal from the renderer the follow camera collects the
 * transformation information from the node it is following and
 * calculates its current state from this and its local
 * transformation.
 */
void FollowCamera::SignalRendering(const float dt) {
    if (follow != NULL) {
        Vector<3,float> accPosition;
        Quaternion<float> accRotation;
        // get the transformations from the node chain
        follow->GetAccumulatedTransformations(&accPosition, &accRotation);
        volume.SetDirection( accRotation * local->GetDirection() );
        volume.SetPosition( accRotation.RotateVector(local->GetPosition()) + accPosition );
    } else {
        volume.SetPosition(local->GetPosition());
        volume.SetDirection(local->GetDirection());
    }
    // we call signal here for other volumes to perform signal tasks
    volume.SignalRendering(dt);
}

/**
 * Attach the camera to a transformation node.
 *
 * @param node Transformation node to "follow".
 */
void FollowCamera::Follow(TransformationNode* node) {
    follow = node;
}

} // NS Display
} // NS OpenEngine
