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

//#include <Meta/OpenGL.h>

namespace OpenEngine {
namespace Display {

using OpenEngine::Geometry::Geometry;

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
                 const float distNear, const float distFar,
                 const float aspect, const float fov)
    : IViewingVolumeDecorator(volume),
      fov(fov),
      aspect(aspect),
      distNear(distNear),
      distFar(distFar),
      visualizeClipping(false)
{
    // initialize planes.
    for (unsigned int i=0; i<6; i++)
        planes[i] = new Plane(Vector<3,float>(), 0);

    // update the volume first as we depend on its structure.
    volume.SignalRendering(0);

    // initialize the frustum
    UpdateDimensions();
    sphere.SetCenter(volume.GetDirection().RotateVector(center)
                     + volume.GetPosition());
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
 * Set the field of view.
 *
 * @param fov Field of view.
 */
void Frustum::SetFOV(const float fov) {
    UpdateDimensions();
    this->fov = fov;
}

/**
 * Get the current field of view.
 *
 * @return Field of view.
 */
float Frustum::GetFOV() const {
    return fov;
}

/**
 * Set the aspect ratio.
 *
 * @param aspect Aspect ratio.
 */
void Frustum::SetAspect(const float aspect) {
    this->aspect = aspect;
    UpdateDimensions();
}

/**
 * Get the current aspect ratio.
 */
float Frustum::GetAspect() const {
    return aspect;
}

/**
 * Set the distance to the near clipping plane.
 *
 * @param distNear Near clipping plane.
 */
void Frustum::SetNear(const float distNear) {
    this->distNear = distNear;
    UpdateDimensions();
}

/**
 * Get the current distance to the near clipping plane.
 *
 * @return Near clipping plane.
 */
float Frustum::GetNear() const {
    return distNear;
}

/**
 * Set the distance to the far clipping plane.
 *
 * @param distFar Far clipping plane.
 */
void Frustum::SetFar(float distFar) {
    this->distFar = distFar;
    UpdateDimensions();
}

/**
 * Get the current distance to the far clipping plane.
 *
 * @return Far clipping plane.
 */
float Frustum::GetFar() const {
    return distFar;
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
IRenderNode* Frustum::GetFrustumNode() {
    return node;
}

/**
 * Signal from the renderer that processing is about to begin.
 */
void Frustum::SignalRendering(const float dt) {
    // update the volume first as we depend on its structure.
    volume.SignalRendering(dt);
    // always update the sphere position and the frustum planes.
    sphere.SetCenter(volume.GetDirection().RotateVector(center)
                     + volume.GetPosition());
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
 * Test if a square is visible to the frustum.
 * This test is currently implemented as a sphere/square test and
 * therefor suffers from some false positives (but no false
 * negatives).
 *
 * @param square Square to test for visibility.
 * @return True if visible in the frustum.
 */
bool Frustum::IsVisible(const Square& square) {
    bool v = Geometry::Intersects(square, sphere);
    if (visualizeClipping) {
        Vector<2,float> center = square.GetCenter();
        float size = square.GetHalfSize();
        list< Vector<3,float> >* lst = (v) ? &visible : &clipped;
        lst->push_back(Vector<3,float>(center[0]-size, 0, center[1]-size));
        lst->push_back(Vector<3,float>(center[0]+size, 0, center[1]-size));
        lst->push_back(Vector<3,float>(center[0]-size, 0, center[1]+size));
        lst->push_back(Vector<3,float>(center[0]+size, 0, center[1]+size));
        lst->push_back(Vector<3,float>(center[0]-size, 0, center[1]-size));
        lst->push_back(Vector<3,float>(center[0]-size, 0, center[1]+size));
        lst->push_back(Vector<3,float>(center[0]+size, 0, center[1]+size));
        lst->push_back(Vector<3,float>(center[0]+size, 0, center[1]-size));
    }
    return v;
}

// bool Frustum::IsVisible(const Square& square) const {
//     Vector<2,float> sides[4], corner(square.GetHalfSize());
//     sides[0] = square.GetCenter() + corner;
//     sides[1] = square.GetCenter() - corner;
//     corner[0] *= -1;
//     sides[2] = square.GetCenter() + corner;
//     sides[3] = square.GetCenter() - corner;
//     for (unsigned int j=0; j<4; j++) {
//         bool inside = true;
//         // Go through all the sides of the frustum
//         for (unsigned int i = 0; i < 6; i++ ) {
//             // Calculate the plane equation and check if the point is behind a side of the frustum
//             if (planes[i]->normal[0] * sides[i][0] +  planes[i]->normal[2] * sides[i][1] + planes[i]->distance <= 0)
//                 // The point was behind a side, so it ISN'T in the frustum
//                 return false;
//             if (inside)
//                 // The point was inside of the frustum (In front of ALL the sides of the frustum)
//                 return true;
//         }
//     }
//     // no corner was in the frustum
//     return false;
// }

/**
 * Test if a box is visible in the frustum.
 *
 * @param box Box to test for visibility.
 * @return True if visible in the frustum.
 */
bool Frustum::IsVisible(const Box& box) {
    bool v = true;
    for (int p=0; p<6; p++) {
        Vector<3,float> vn = box.GetCorner(planes[p]->normal[0]>0,
                                        planes[p]->normal[1]>0,
                                        planes[p]->normal[2]>0);
        if (vn * planes[p]->normal + planes[p]->distance < 0) {
            v = false; break;
        }
    }
    if (visualizeClipping && true) {
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
 * Calculate the corners of the near clipping plane.
 *
 * @param[out] left Left corner.
 * @param[out] right Right corner.
 * @param[out] top Top corner.
 * @param[out] bottom Bottom corner.
 */
void Frustum::CalculateNearPlane(float& left, float& right, float& top, float& bottom) {
    float t, ty, tx;
    t  = fov * 0.5f;            // half of the angle
    ty = tan(t);                // unit distance on the y-axis
    tx = ty * aspect;           // unit distance on the x-axis
    // set the corners
    right  = tx * distNear;
    left   = -right;
    top    = ty * distNear;
    bottom = -top;
}

/**
 * Update the necessary parts of the frustum.
 * Recomputes the frustum based on change variables set by the frustum
 * set-methods.
 */
void Frustum::UpdateDimensions() {
    UpdateProjection();     // frame depends on proj
    UpdateFrame();          // sphere depends on frame
    UpdateSphere();
}

/**
 * Compute all the clipping planes of the frustum.
 */
void Frustum::UpdatePlanes() {
    // get the product of the projection and view matrix.
    Matrix<4,4,float> mat(proj * volume.GetDirection().GetInverse().GetMatrix().GetExpanded());
    Vector<3,float> pos(mat(3,0), mat(3,1), mat(3,2));
    Matrix<3,3,float> clip(mat.GetReduced());

    // calculate all the planes
    planes[0]->Set(pos + clip[0],  mat(0,3));
    planes[1]->Set(pos - clip[0], -mat(0,3));
    planes[2]->Set(pos + clip[1],  mat(1,3));
    planes[3]->Set(pos - clip[1], -mat(1,3));
    planes[4]->Set(pos + clip[2],  mat(2,3));
    planes[5]->Set(pos - clip[2], -mat(2,3));

    // normalize all the planes
    for (unsigned int i=0; i<6; i++) {
        float l = planes[i]->normal.GetLength();
        planes[i]->distance /= l;
        planes[i]->normal.Normalize();
        // update the distance from the current position
        planes[i]->distance -= planes[i]->normal * volume.GetPosition();
    }
}

/**
 * Compute the frustum projection matrix.
 */
void Frustum::UpdateProjection() {
    float left, right, top, bottom;
    CalculateNearPlane(left, right, top, bottom);

    float inv_w, inv_h, inv_d;
    inv_w = 1 / (right - left);
    inv_h = 1 / (top - bottom);
    inv_d = 1 / (distFar - distNear);

    // calculate matrix elements
    proj(0,0) = 2 * distNear * inv_w;
    proj(0,2) = (right + left) * inv_w;
    proj(1,1) = 2 * distNear * inv_h;
    proj(1,2) = (top + bottom) * inv_h;
    proj(2,2) = - (distFar + distNear) * inv_d;
    proj(2,3) = -2 * (distFar * distNear) * inv_d;
    proj(3,2) = -1;
    proj(3,3) = 0;
}

/**
 * Compute the frustum frame.
 */
void Frustum::UpdateFrame() {
    float left, right, top, bottom;
    CalculateNearPlane(left, right, top, bottom);
    
    // far plane corners
    float r, fleft, fright, ftop, fbottom, n, f;
    r = distFar / distNear;
    fleft   = r * left;
    fright  = r * right;
    ftop    = r * top;
    fbottom = r * bottom;
    n = -distNear;
    f = -distFar;

    // near plane
    frame[0] = Vector<3,float>(left,  top,    n);
    frame[1] = Vector<3,float>(right, top,    n);
    frame[2] = Vector<3,float>(right, top,    n);
    frame[3] = Vector<3,float>(right, bottom, n);
    frame[4] = Vector<3,float>(right, bottom, n);
    frame[5] = Vector<3,float>(left,  bottom, n);
    frame[6] = Vector<3,float>(left,  bottom, n);
    frame[7] = Vector<3,float>(left,  top,    n);
    
    // far plane
    frame[8]  = Vector<3,float>(fleft,  ftop,    f);
    frame[9]  = Vector<3,float>(fright, ftop,    f);
    frame[10] = Vector<3,float>(fright, ftop,    f);
    frame[11] = Vector<3,float>(fright, fbottom, f);
    frame[12] = Vector<3,float>(fright, fbottom, f);
    frame[13] = Vector<3,float>(fleft,  fbottom, f);
    frame[14] = Vector<3,float>(fleft,  fbottom, f);
    frame[15] = Vector<3,float>(fleft,  ftop,    f);

    // pyramid
    frame[16] = Vector<3,float>(0,     0,      0);
    frame[17] = Vector<3,float>(left,  top,    n);
    frame[18] = Vector<3,float>(0,     0,      0);
    frame[19] = Vector<3,float>(right, top,    n);
    frame[20] = Vector<3,float>(0,     0,      0);
    frame[21] = Vector<3,float>(left,  bottom, n);
    frame[22] = Vector<3,float>(0,     0,      0);
    frame[23] = Vector<3,float>(right, bottom, n);

    // box
    frame[24] = Vector<3,float>(left,   top,     n);
    frame[25] = Vector<3,float>(fleft,  ftop,    f);
    frame[26] = Vector<3,float>(right,  top,     n);
    frame[27] = Vector<3,float>(fright, ftop,    f);
    frame[28] = Vector<3,float>(left,   bottom,  n);
    frame[29] = Vector<3,float>(fleft,  fbottom, f);
    frame[30] = Vector<3,float>(right,  bottom,  n);
    frame[31] = Vector<3,float>(fright, fbottom, f);
}

/**
 * Compute a bounding sphere for the frustum.
 */
void Frustum::UpdateSphere() {
    Vector<3,float> ntl, ftl, n, f;
    float c, z, d;
    ntl = frame[0];             // near top left corner
    ftl = frame[10];            // far top left corner
    c = -distFar*0.5f;              // halving variable
    z = c;                      // position on z-axis (center of frustum)

    // reset and recalculate the sphere with a binary search for when
    // the `n' and `f' vectors differ by less then 1.
    sphere.SetRadius(0);
    while (sphere.GetRadius() == 0) {
        c = c * 0.5f;
        n = Vector<3,float>(0,0,z) - ntl;
        f = Vector<3,float>(0,0,z) - ftl;
        d = f*f - n*n;
        if (d > 1)       z += c;
        else if (d < -1) z -= c;
        else sphere.SetRadius(((d >= 0)?n:f).GetLength());
    }
    center = Vector<3,float>(0,0,z);
    sphere.SetCenter(center);
}


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

Frustum::FNode::FNode(FNode& node) : frustum(node.frustum) {

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
        r->DrawLine( Line( - p->distance * p->normal, p->normal * (100 - p->distance)),
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

    // draw bounding sphere
    // glTranslatef(frustum.sphere.GetCenter()[0], frustum.sphere.GetCenter()[1], frustum.sphere.GetCenter()[2]);
    // glutWireSphere(frustum.sphere.GetRadius(), 10, 10);
    
    glPopMatrix();
    */
}

} // NS Display
} // NS OpenEngine
