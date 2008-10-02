// Render state node
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _RENDER_STATE_NODE_H_
#define _RENDER_STATE_NODE_H_

#include <Scene/SceneNode.h>
#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
namespace Renderers {

using namespace OpenEngine::Scene;

/**
 * Node describing specific rendering state. 
 * Ex. wire framed rendering. Enable/disable normals etc.
 *
 * @class RenderStateNode RenderStateNode.h Scene/RenderStateNode.h
 */
class RenderStateNode : public SceneNode {
public:
    /**
     * RenderState options.
     *
     * @enum RenderStateOption
     */
    enum RenderStateOption {
        NONE                   = 0,
        RENDER_WIREFRAMED      = 1<<0,
        RENDER_TEXTURES        = 1<<1,
        RENDER_SHADERS         = 1<<2,
        RENDER_NORMALS         = 1<<3,
        RENDER_HARD_NORMAL     = 1<<4,
        RENDER_BACKFACES       = 1<<5,
        RENDER_BINORMALS       = 1<<6,
        RENDER_TANGENTS        = 1<<7,
        RENDER_LIGHTING        = 1<<8,
        RENDER_WITH_DEPTH_TEST = 1<<9
    };

private:
    RenderStateOption options;

public:

    //! Default constructor
    RenderStateNode();
    //! Copy constructor
    RenderStateNode(RenderStateNode& node);
    //! Set constructor
    explicit RenderStateNode(RenderStateOption options);
    //! Destructor
    ~RenderStateNode();

    ISceneNode* CloneSelf();
    void Accept(ISceneNodeVisitor& v);
    bool IsOptionSet(RenderStateOption o);
    RenderStateOption GetOptions();
    void SetOptions(RenderStateOption options);
    void AddOptions(RenderStateOption options);
    void RemoveOptions(RenderStateOption options);
    void ToggleOptions(RenderStateOption options);
};

} //NS Renderers
} //NS OpenEngine

#endif // _RENDER_STATE_NODE_H_
