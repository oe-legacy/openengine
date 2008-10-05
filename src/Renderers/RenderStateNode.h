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
        TEXTURE                = 1<<0,
        SHADER                 = 1<<1,
        BACKFACE               = 1<<2,
        LIGHTING               = 1<<3,
        DEPTH_TEST             = 1<<4,
        // DEBUG THINGS
        WIREFRAME              = 1<<5,
        SOFT_NORMAL            = 1<<6,
        HARD_NORMAL            = 1<<7,
        BINORMAL               = 1<<8,
        TANGENT                = 1<<9,
    };

private:
    RenderStateOption enabled;
    RenderStateOption disabled;

public:

    //! Default constructor
    RenderStateNode();
    //! Copy constructor
    RenderStateNode(RenderStateNode& node);
    //! Destructor
    ~RenderStateNode();

    ISceneNode* CloneSelf();
    void Accept(ISceneNodeVisitor& v);
    void EnableOption(RenderStateOption options);
    void DisableOption(RenderStateOption options);
    void ToggleOption(RenderStateOption options);
    void Enable(RenderStateOption option);
    void Disable(RenderStateOption option);
    RenderStateOption GetEnabled();
    RenderStateOption GetDisabled();
    bool IsOptionEnabled(RenderStateOption o);
    bool IsOptionDisabled(RenderStateOption o);
    RenderStateNode* GetInverse();
    std::string ToString();
};

} //NS Renderers
} //NS OpenEngine


#endif // _RENDER_STATE_NODE_H_
