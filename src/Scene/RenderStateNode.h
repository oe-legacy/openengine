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
        BINORMAL               = 1<<8,
        TANGENT                = 1<<9,
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
    void Enable(RenderStateOption option);
    void Disable(RenderStateOption option);
    RenderStateOption GetEnabled() const;
    RenderStateOption GetDisabled() const;
    bool IsOptionEnabled(RenderStateOption o) const;
    bool IsOptionDisabled(RenderStateOption o) const;
    RenderStateNode* GetInverse();
    const std::string ToString() const;

private:
    RenderStateOption enabled;
    RenderStateOption disabled;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & enabled;
        ar & disabled;
    }

};

} //NS Scene
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::RenderStateNode)

#endif // _OE_RENDER_STATE_NODE_H_
