// Render state node
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_RENDER_STATE_NODE_H_
#define _OE_RENDER_STATE_NODE_H_

#include <Scene/ISceneNode.h>

namespace OpenEngine {
    namespace Resources {
        class IArchiveWriter;
        class IArchiveReader;
    }
namespace Scene {

/**
 * Node describing specific rendering state. 
 * Ex. wire framed rendering. Enable/disable normals etc.
 *
 * @class RenderStateNode RenderStateNode.h Scene/RenderStateNode.h
 */
class RenderStateNode : public ISceneNode {
    OE_SCENE_NODE(RenderStateNode, ISceneNode)

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
        AUTO_NORMAL            = 1<<8,
        BINORMAL               = 1<<9,
        TANGENT                = 1<<10,
        COLOR_MATERIAL         = 1<<11,
    };

    //! Default constructor
    RenderStateNode();
    //! Copy constructor
    RenderStateNode(const RenderStateNode& node);
    //! Destructor
    ~RenderStateNode();

    void EnableOption(RenderStateOption options);
    void DisableOption(RenderStateOption options);
    void InheritOption(RenderStateOption options);
    void ToggleOption(RenderStateOption options);
    RenderStateOption GetEnabled() const;
    RenderStateOption GetDisabled() const;
    bool IsOptionEnabled(RenderStateOption o) const;
    bool IsOptionDisabled(RenderStateOption o) const;
    void Invert();
    RenderStateNode* GetInverse() const;
    RenderStateNode* GetDifference(RenderStateNode& other) const;
    RenderStateNode* GetCombined(RenderStateNode& other) const;
    const std::string ToString() const;

    void Serialize(Resources::IArchiveWriter& w);
    void Deserialize(Resources::IArchiveReader& r);

private:
    RenderStateOption enabled;
    RenderStateOption disabled;


};

} //NS Scene
} //NS OpenEngine


#endif // _OE_RENDER_STATE_NODE_H_
