// Rendering state node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include <Scene/RenderStateNode.h>
#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>
#include <string>

namespace OpenEngine {
namespace Scene {

/**
 * Default constructor.
 * No options are set and are thus inherieted from ancestoring
 * RenderStateNodes.
 */
RenderStateNode::RenderStateNode()
    : ISceneNode()
    , enabled(NONE)
    , disabled(NONE)
{

}

RenderStateNode::RenderStateNode(const RenderStateNode& node)
    : ISceneNode(node)
    , enabled(node.enabled)
    , disabled(node.disabled)
{

}

/**
 * Destructor
 */
RenderStateNode::~RenderStateNode() {

}

/**
 * Check if an option is enabled.
 *
 * @param o Frame option(s) to check
 * @return True if enabled
 */
bool RenderStateNode::IsOptionEnabled(RenderStateOption o) const {
    return (o & GetEnabled()) == o;
}

/**
 * Check if an option is disabled.
 *
 * @param o Frame option(s) to check
 * @return True if disabled
 */
bool RenderStateNode::IsOptionDisabled(RenderStateOption o) const {
    return (o & GetDisabled()) == o;
}

/**
 * Get current enabled options set in this RenderStateNode.
 *
 * @return RenderStateOption
 */
RenderStateNode::RenderStateOption RenderStateNode::GetEnabled() const {
    return enabled;
}

/**
 * Get current disabled options set in this RenderStateNode.
 *
 * @return RenderStateOption
 */
RenderStateNode::RenderStateOption RenderStateNode::GetDisabled() const {
    return disabled;
}

/**
 * Add options flag to the already existing,
 * options specified are or'ed with whose already
 * set.
 *
 * @param options option(s) to add.
 */
void RenderStateNode::EnableOption(RenderStateOption options) {
    // removed from disabled
    unsigned int optDis = disabled & ~((unsigned int)options);
    disabled = (RenderStateOption)optDis;

    // add to enabled
    unsigned int optEn = enabled | (unsigned int)options;
    enabled = (RenderStateOption)optEn;
}

/**
 * Add options flag to the already existing,
 * options specified are or'ed with whose already
 * set.
 *
 * @param options option(s) to add.
 */
void RenderStateNode::DisableOption(RenderStateOption options) {
    // removed from enabled
    unsigned int optEn = enabled & ~((unsigned int)options);
    enabled = (RenderStateOption)optEn;

    // add to disabled
    unsigned int optDis = disabled | (unsigned int)options;
    disabled = (RenderStateOption)optDis;
}

void RenderStateNode::InheritOption(RenderStateOption options) {
    // remove from enabled and disabled
    enabled  = (RenderStateOption) (enabled  & ~((unsigned int)options));
    disabled = (RenderStateOption) (disabled & ~((unsigned int)options));
}

/**
 * Toggle specified option.
 *
 * @param options Options to turn on/off.
 */
void RenderStateNode::ToggleOption(RenderStateOption options) {
    if (IsOptionEnabled(options))
        DisableOption(options);
    else // if (IsOptionDisabled(options))
         //  - If an option have neither been enabled or disabled, we cant toggle it?
        EnableOption(options);
}

/**
 * Get a render state node with the inverse options.
 *
 * Thus an explicate enabled option becomes an explicate disabled
 * option. Inherited options remain unchanged (i.e., implicit).
 *
 * Ownership of the created node is transferred to the caller.
 *
 * @return New inverted render state node (plus ownership)
 */
RenderStateNode* RenderStateNode::GetInverse() const {
    RenderStateNode* inverse = new RenderStateNode();
    inverse->enabled  = this->disabled;
    inverse->disabled = this->enabled;
    return inverse;
}

/**
 * Destructively invert the options of the render state node.
 *
 * Thus an explicate enabled option becomes an explicate disabled
 * option. Inherited options remain unchanged (i.e., implicit).
 */
void RenderStateNode::Invert() {
    RenderStateOption tmp = this->enabled;
    this->enabled  = this->disabled;
    this->disabled = tmp;
}

/**
 * Get the difference in options between \a this node and \a other
 * node (i.e., \a this - \a other).
 *
 * Creates a new node with every explicitly enabled or disabled
 * option from \a this, except if it is also set in \a other.
 *
 * Ownership of the new node is transferred to the caller.
 *
 * @return New difference render state node (plus ownership)
 */
RenderStateNode* RenderStateNode::GetDifference(RenderStateNode& other) const {
    RenderStateNode* diff = new RenderStateNode();
    diff->enabled  = RenderStateOption(enabled  & ~other.enabled);
    diff->disabled = RenderStateOption(disabled & ~other.disabled);
    return diff;
}


const std::string RenderStateNode::ToString() const {
    std::string str(GetNodeName());
    if (enabled != NONE) {
        str += "\nEnabled:";
        if ( IsOptionEnabled(TEXTURE) )
            str += " TEXTURE,";
        if ( IsOptionEnabled(SHADER) )
            str += " SHADER,";
        if ( IsOptionEnabled(BACKFACE) )
            str += " BACKFACE,";
        if ( IsOptionEnabled(LIGHTING) )
            str += " LIGHTING,";
        if ( IsOptionEnabled(DEPTH_TEST) )
            str += " DEPTH_TEST,";
        if ( IsOptionEnabled(WIREFRAME) )
            str += " WIREFRAME,";
        if ( IsOptionEnabled(SOFT_NORMAL) )
            str += " SOFT_NORMAL,";
        if ( IsOptionEnabled(HARD_NORMAL) )
            str += " HARD_NORMAL,";
        if ( IsOptionEnabled(BINORMAL) )
            str += " BINORMAL,";
        if ( IsOptionEnabled(TANGENT) )
            str += " TANGENT,";
        if ( IsOptionEnabled(COLOR_MATERIAL) )
            str += " COLOR_MATERIAL,";
        str[str.length() - 1] = ' ';
    }
    if (disabled != NONE) {
        str += "\nDisabled:";
        if ( IsOptionDisabled(TEXTURE) )
            str += " TEXTURE,";
        if ( IsOptionDisabled(SHADER) )
            str += " SHADER,";
        if ( IsOptionDisabled(BACKFACE) )
            str += " BACKFACE,";
        if ( IsOptionDisabled(LIGHTING) )
            str += " LIGHTING,";
        if ( IsOptionDisabled(DEPTH_TEST) )
            str += " DEPTH_TEST,";
        if ( IsOptionDisabled(WIREFRAME) )
            str += " WIREFRAME,";
        if ( IsOptionDisabled(SOFT_NORMAL) )
            str += " SOFT_NORMAL,";
        if ( IsOptionDisabled(HARD_NORMAL) )
            str += " HARD_NORMAL,";
        if ( IsOptionDisabled(BINORMAL) )
            str += " BINORMAL,";
        if ( IsOptionDisabled(TANGENT) )
            str += " TANGENT,";
        if ( IsOptionDisabled(COLOR_MATERIAL) )
            str += " COLOR_MATERIAL,";
        str[str.length()-1] = ' ';
    }
    return str;
}

void RenderStateNode::Serialize(Resources::IArchiveWriter& w) {
    w.WriteInt("enabled",enabled);
    w.WriteInt("disabled",disabled);
}

void RenderStateNode::Deserialize(Resources::IArchiveReader& r) {
    enabled = (RenderStateOption)r.ReadInt("enabled");
    disabled = (RenderStateOption)r.ReadInt("disabled");
}

} //NS Scene
} //NS OpenEngine
