// OpenGL rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OPENGL_RENDERING_VIEW_H_
#define _OPENGL_RENDERING_VIEW_H_

#include <Geometry/FaceSet.h>
#include <Renderers/IRenderingView.h>
#include <Renderers/RenderStateNode.h>
#include <vector>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

using namespace OpenEngine::Renderers;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Geometry;
using namespace std;

/**
 * Concrete RenderingView using OpenGL.
 */
class RenderingView : virtual public IRenderingView {
    IRenderer* renderer;
    vector<RenderStateNode*> stateStack;

    void RenderBinormals(FacePtr face);
    void RenderTangents(FacePtr face);
    void RenderNormals(FacePtr face);
    void RenderHardNormal(FacePtr face);
    void RenderLine(Vector<3,float> vert, Vector<3,float> norm, Vector<3,float> color);
    bool IsOptionSet(RenderStateNode::RenderStateOption o);
public:
    RenderingView(Viewport& viewport);
    virtual ~RenderingView();
    void VisitGeometryNode(GeometryNode* node);
    void VisitTransformationNode(TransformationNode* node);
    void VisitRenderStateNode(RenderStateNode* node);
    void VisitRenderNode(IRenderNode* node);
    void Render(IRenderer* renderer, ISceneNode* root);
    IRenderer* GetRenderer();
};

} // NS OpenGL
} // NS Renderers
} // NS OpenEngine

#endif // _OPENGL_RENDERING_VIEW_H_
