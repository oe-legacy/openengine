// Follow camera.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "TrackingFollowCamera.h"

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
TrackingFollowCamera::TrackingFollowCamera(IViewingVolume& volume)
    : Camera(volume), track(NULL), follow(NULL) {
    local = new Camera(*(new ViewingVolume()));
}

/**
 * Follow camera destructor.
 * Cleans local state. Will not free the followed transformation
 * node.
 */
TrackingFollowCamera::~TrackingFollowCamera() {
    delete local;
}

// all these methods forward to the local volume
void TrackingFollowCamera::SetDirection(const Vector<3,float> dir, const Vector<3,float> up) {
    local->SetDirection(dir, up);
}
void TrackingFollowCamera::Move(const float l, const float t, const float v) {
    local->Move(l,t,v);
}
void TrackingFollowCamera::LookAt(const Vector<3,float> point) {
    local->LookAt(point);
}
void TrackingFollowCamera::LookAt(const float x, const float y, const float z) {
    local->LookAt(x,y,z);
}
void TrackingFollowCamera::Rotate(const float roll, const float pitch, const float yaw) {
    local->Rotate(roll, pitch, yaw);
}
void TrackingFollowCamera::Rotate(const float angle, const Vector<3,float> axis) {
    local->Rotate(angle, axis);
}
void TrackingFollowCamera::Rotate(const Quaternion<float> rotation) {
    local->Rotate(rotation);
}
void TrackingFollowCamera::SetPosition(const Vector<3,float> position) {
    local->SetPosition(position);
}
void TrackingFollowCamera::SetDirection(const Quaternion<float> direction) {
    local->SetDirection(direction);
}

/**
 * On every signal from the renderer the follow camera collects the
 * transformation information from the node it is tracking and
 * calculates its current state from this and its local
 * transformation.
 */
void TrackingFollowCamera::SignalRendering(const float dt) {

    if (follow != NULL) {
        Vector<3,float> accPosition;
        Quaternion<float> accRotation;
        // get the transformations from the node chain
        follow->GetAccumulatedTransformations(&accPosition, &accRotation);
        //volume.SetDirection( accRotation * local->GetDirection() );
        volume.SetPosition( accRotation.RotateVector(local->GetPosition()) + accPosition );
    } else {
        volume.SetPosition(local->GetPosition());
        //volume.SetDirection(local->GetDirection());
    }


    if (track != NULL) {
        Vector<3,float> accPosition;
        Quaternion<float> accRotation;
        // get the transformations from the node chain
        track->GetAccumulatedTransformations(&accPosition, &accRotation);
        Vector<3,float> pos = volume.GetPosition();
        Vector<3,float> direction = accPosition - pos;
 

        if (direction.IsZero()) {
            //logger.warning << "Ignoring call to Camera::SetDirection with the zero vector." << logger.end;
            return;
        }

        
        Vector<3,float> z(-direction);
        z.Normalize();
        Vector<3,float> x = Vector<3,float>(0,1,0) % z;
        Vector<3,float> y = z % x;
        Matrix<3,3,float> m(x, y, z);
        Quaternion<float> q(m);
        volume.SetDirection(q.GetNormalize());    
    } else {
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
void TrackingFollowCamera::Follow(TransformationNode* node) {
    follow = node;
}


void TrackingFollowCamera::Track(TransformationNode* node) {
    track = node;
}


} // NS Display
} // NS OpenEngine
