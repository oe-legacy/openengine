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
        NONE                  = 0x00000000,
        RENDER_WIREFRAMED     = 0x00000001,
        RENDER_TEXTURES       = 0x00000010,
        RENDER_SHADERS        = 0x00000100,
        RENDER_NORMALS        = 0x00001000,
        RENDER_HARD_NORMAL    = 0x00010000,
        RENDER_BACKFACES      = 0x00100000,
        RENDER_BINORMALS      = 0x01000000,
        RENDER_TANGENTS       = 0x10000000
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
