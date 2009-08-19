// Frustum viewing volume.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Display/Frustum.h>
#include <Math/Math.h>

namespace OpenEngine {
namespace Display {

/**
 * Frustum constructor.
 *
 * @param volume Viewing volume to decorate.
 * @param distNear Near plane [optional]
 * @param distFar Far plane [optional]
 * @param aspect Aspect ratio [optional]
 * @param fov Field of view [optional]
 */
Frustum::Frustum(IViewingVolume& volume,
                 const float farClip)
    : IViewingVolumeDecorator(volume)
    , visualizeClipping(false)
    , farClip(farClip) 
{
    // initialize planes.
    for (unsigned int i=0; i<6; i++)
        planes[i] = new Plane(Vector<3,float>(1), 0);

    // update the volume first as we depend on its structure.
    volume.SignalRendering(0);

    // initialize the frustum
    UpdatePlanes();

    // create a render node
    node = new FNode(*this);
}

/**
 * Frustum destructor.
 * Deletes the frustum node plus some internal structures.
 */
Frustum::~Frustum() {
    delete node;
    for (unsigned int i=0; i<6; i++)
        delete planes[i];
}

/**
 * Get the distance to the far clipping plane.
 * This is the clipping plane of the frustum *not* of the
 * underlying viewing volume.
 *
 * @return Far clipping plane.
 */
float Frustum::GetFarClippingPlane() {
    return farClip;
}

/**
 * Set the distance to the far clipping plane.
 * This is the clipping plane of the frustum *not* of the
 * underlying viewing volume.
 *
 * @param Far clipping plane.
 */
void Frustum::SetFarClippingPlane(const float farClip) {
    this->farClip = farClip;
}

/**
 * Get a render node that visualizes this frustum.
 * The render node can be placed in the rendering scene to have it
 * drawn on screen.
 *
 * Note that the render node will be deleted if the frustum is
 * deleted.
 *
 * @return Render node of the frustum.
 */
RenderNode* Frustum::GetFrustumNode() {
    return node;
}

/**
 * Signal from the renderer that processing is about to begin.
 */
void Frustum::SignalRendering(const float dt) {
    // update the volume first as we depend on its structure.
    volume.SignalRendering(dt);
    UpdatePlanes();
    // clear the visible tests
    visible.clear();
    clipped.clear();
}

/**
 * Switch clipping visualization state.
 *
 * Note that the frustum render node must be added to the scene after
 * the nodes that are tested for clipping. If not the visual state will
 * have been reset before the testing has occurred. (Every call to
 * GetViewMatrix resets the state).
 *
 * @see GetFrustumNode
 */
void Frustum::VisualizeClipping(const bool visualize) {
    visualizeClipping = visualize;
}

/**
 * Test if a box is visible in the frustum.
 *
 * @param box Box to test for visibility.
 * @return True if visible in the frustum.
 */
bool Frustum::IsVisible(const Box& box) {
    bool v = true;
    for (int p=0; p<6; p++) {
        Vector<3,float> vn = box.GetCorner(planes[p]->GetNormal()[0]>0,
                                           planes[p]->GetNormal()[1]>0,
                                           planes[p]->GetNormal()[2]>0);
        if (vn * planes[p]->GetNormal() + planes[p]->GetDistance() < 0) {
            v = false; break;
        }
    }

    if (visualizeClipping) {
        list< Vector<3,float> >* lst = (v) ? &visible : &clipped;
        lst->push_back(box.GetCorner(1,1,1));
        lst->push_back(box.GetCorner(1,1,0));
        lst->push_back(box.GetCorner(1,1,1));
        lst->push_back(box.GetCorner(1,0,1));
        lst->push_back(box.GetCorner(1,1,1));
        lst->push_back(box.GetCorner(0,1,1));
        lst->push_back(box.GetCorner(0,0,1));
        lst->push_back(box.GetCorner(0,0,0));
        lst->push_back(box.GetCorner(0,0,1));
        lst->push_back(box.GetCorner(0,1,1));
        lst->push_back(box.GetCorner(0,0,1));
        lst->push_back(box.GetCorner(1,0,1));
        lst->push_back(box.GetCorner(0,1,0));
        lst->push_back(box.GetCorner(0,1,1));
        lst->push_back(box.GetCorner(0,1,0));
        lst->push_back(box.GetCorner(0,0,0));
        lst->push_back(box.GetCorner(0,1,0));
        lst->push_back(box.GetCorner(1,1,0));
        lst->push_back(box.GetCorner(1,0,0));
        lst->push_back(box.GetCorner(1,0,1));
        lst->push_back(box.GetCorner(1,0,0));
        lst->push_back(box.GetCorner(1,1,0));
        lst->push_back(box.GetCorner(1,0,0));
        lst->push_back(box.GetCorner(0,0,0));
    }
    return v;
}

/**
 * Compute all the clipping planes of the frustum.
 */
void Frustum::UpdatePlanes() {
    // get the product of the projection and view matrix.
    Matrix<4,4,float> mat(volume.GetProjectionMatrix() * volume.GetDirection().GetInverse().GetMatrix().GetExpanded());
    Vector<3,float> pos(mat(3,0), mat(3,1), mat(3,2));
    Matrix<3,3,float> clip(mat.GetReduced());
        
    // calculate all the planes (normals and distances)
    Vector<3,float> pn[6];  float pd[6];
    //pn[0] = pos + clip[0];  pd[0] =  mat(0,3);
    pn[1] = pos - clip[0];  pd[1] = -mat(0,3);
    pn[2] = pos + clip[1];  pd[2] =  mat(1,3);
    pn[3] = pos - clip[1];  pd[3] = -mat(1,3);
    pn[4] = pos + clip[2];  pd[4] =  mat(2,3);
    pn[5] = pos - clip[2];  pd[5] = -mat(2,3);
    for (unsigned int i=1; i<6; i++)
        planes[i]->Set(pn[i], pd[i] / pn[i].GetLength() - pn[i] * volume.GetPosition());

    // overwrite the far plane with the frustum's far clipping plane (index 0)
    Vector<3, float> normal = volume.GetDirection().RotateVector(Vector<3,float>(0,0,1));
    float distance = normal * volume.GetPosition() + farClip;
    planes[0]->Set(normal, distance);
}

// /**
//  * Compute the frustum frame.
//  */
// void Frustum::UpdateFrame() {
//     float left, right, top, bottom;
//     CalculateNearPlane(left, right, top, bottom);
    
//     // far plane corners
//     float r, fleft, fright, ftop, fbottom, n, f;
//     r = distFar / distNear;
//     fleft   = r * left;
//     fright  = r * right;
//     ftop    = r * top;
//     fbottom = r * bottom;
//     n = -distNear;
//     f = -distFar;

//     // near plane
//     frame[0] = Vector<3,float>(left,  top,    n);
//     frame[1] = Vector<3,float>(right, top,    n);
//     frame[2] = Vector<3,float>(right, top,    n);
//     frame[3] = Vector<3,float>(right, bottom, n);
//     frame[4] = Vector<3,float>(right, bottom, n);
//     frame[5] = Vector<3,float>(left,  bottom, n);
//     frame[6] = Vector<3,float>(left,  bottom, n);
//     frame[7] = Vector<3,float>(left,  top,    n);
    
//     // far plane
//     frame[8]  = Vector<3,float>(fleft,  ftop,    f);
//     frame[9]  = Vector<3,float>(fright, ftop,    f);
//     frame[10] = Vector<3,float>(fright, ftop,    f);
//     frame[11] = Vector<3,float>(fright, fbottom, f);
//     frame[12] = Vector<3,float>(fright, fbottom, f);
//     frame[13] = Vector<3,float>(fleft,  fbottom, f);
//     frame[14] = Vector<3,float>(fleft,  fbottom, f);
//     frame[15] = Vector<3,float>(fleft,  ftop,    f);

//     // pyramid
//     frame[16] = Vector<3,float>(0,     0,      0);
//     frame[17] = Vector<3,float>(left,  top,    n);
//     frame[18] = Vector<3,float>(0,     0,      0);
//     frame[19] = Vector<3,float>(right, top,    n);
//     frame[20] = Vector<3,float>(0,     0,      0);
//     frame[21] = Vector<3,float>(left,  bottom, n);
//     frame[22] = Vector<3,float>(0,     0,      0);
//     frame[23] = Vector<3,float>(right, bottom, n);

//     // box
//     frame[24] = Vector<3,float>(left,   top,     n);
//     frame[25] = Vector<3,float>(fleft,  ftop,    f);
//     frame[26] = Vector<3,float>(right,  top,     n);
//     frame[27] = Vector<3,float>(fright, ftop,    f);
//     frame[28] = Vector<3,float>(left,   bottom,  n);
//     frame[29] = Vector<3,float>(fleft,  fbottom, f);
//     frame[30] = Vector<3,float>(right,  bottom,  n);
//     frame[31] = Vector<3,float>(fright, fbottom, f);
// }

/**
 * Frustum rendering node constructor.
 *
 * @param frustum Frustum instance.
 */
Frustum::FNode::FNode(Frustum& frustum) : frustum(frustum) {

}

/**
 * Frustum rendering node destructor.
 */
Frustum::FNode::~FNode() {

}

Frustum::FNode::FNode(FNode& node)
  : RenderNode(node)
  , frustum(node.frustum)
{

}

ISceneNode* Frustum::FNode::Clone() {
    return new FNode(*this);
}

/**
 * Apply method for rendering nodes.
 * @see RenderingNode::Apply
 */
void Frustum::FNode::Apply(IRenderingView* view) {

    IRenderer* r = view->GetRenderer();

    // draw clipped and visible objects
    list<Vector<3,float> >::iterator l;
    for (l = frustum.visible.begin(); l != frustum.visible.end(); l++)
        r->DrawLine(Line(*l, *l++), Vector<3,float>(0,1,0), 1);
    for (l = frustum.clipped.begin(); l != frustum.clipped.end(); l++)
        r->DrawLine(Line(*l, *l++), Vector<3,float>(1,0,0), 4);

    // draw frustum plane normals
    for (unsigned int i=0; i<6; i++) {
        Plane* p = frustum.planes[i];
        r->DrawLine( Line( - p->GetDistance() * p->GetNormal(), p->GetNormal() * (100 - p->GetDistance())),
                     Vector<3,float>(1,0,0), 2);
    }

    /* removed after moving the OpenGL renderer to its own extension.
    glPushMatrix();
    glTranslatef(frustum.volume.GetPosition()[0], frustum.volume.GetPosition()[1], frustum.volume.GetPosition()[2]);

    Matrix<4,4,float> m = frustum.volume.GetDirection().GetInverse().GetMatrix().GetExpanded();
    float f[16] = {0};
    m.ToArray(f);
    glMultMatrixf(f);

    // draw frustum frame
    for (unsigned int i=0; i<32; i += 2)
        r->DrawLine(Line(frustum.frame[i], frustum.frame[i+1]), Vector<3,float>(0,1,0));

    glPopMatrix();
    */
}

} // NS Display
} // NS OpenEngine
