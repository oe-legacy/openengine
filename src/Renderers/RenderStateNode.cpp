// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/RenderStateNode.h>

namespace OpenEngine {
namespace Renderers {

/**
 * Default constructor clearing all options
 */
RenderStateNode::RenderStateNode() : options(NONE) {
}

RenderStateNode::RenderStateNode(RenderStateNode& node) : SceneNode(node) {
    options = node.options;
}

/**
 * Set constructor
 */
RenderStateNode::RenderStateNode(RenderStateOption options) {
    this->options = options;
}

/**
 * Destructor
 */
RenderStateNode::~RenderStateNode() {
}

ISceneNode* RenderStateNode::CloneSelf() {
    return new RenderStateNode(*this);
}

/**
 * Accepting visitor by make callback to the visitor.
 *
 * @see ISceneNode::Accept
 */
void RenderStateNode::Accept(ISceneNodeVisitor& v) { 
    v.VisitRenderStateNode(this);
}

/**
 * Check if an option is set.
 *
 * @param o Frame option(s) to check
 * @return True if set
 */
bool RenderStateNode::IsOptionSet(RenderStateOption o) {
    return (o & GetOptions()) == o;
}

/**
 * Get current options set in this RenderStateNode.
 *
 * @return RenderStateOption
 */
RenderStateNode::RenderStateOption RenderStateNode::GetOptions() {
    return options;
}

/**
 * Overwrites current options with options specified.
 *
 * @param options new settings for this RenderStateNode
 */
void RenderStateNode::SetOptions(RenderStateOption options) {
    this->options = options;
}

/**
 * Add options flag to the already existing,
 * options specified are or'ed with whose already
 * set.
 *
 * @param options option(s) to add.
 */
void RenderStateNode::AddOptions(RenderStateOption options) {
    unsigned int opt = this->options | (unsigned int)options;
    this->options = (RenderStateOption)opt;
}

/**
 * Remove option flags specified by xor'ing them
 * together with whose already specified. 
 *
 * @param options option(s) to be removed.
 */
void RenderStateNode::RemoveOptions(RenderStateOption options) {
    int opt = this->options & ~((unsigned int)options);
    this->options = (RenderStateOption)opt;
}

/**
 * Toggle specified option.
 *
 * @param options Options to turn on/off.
 */
void RenderStateNode::ToggleOptions(RenderStateOption options) {
    int opt = this->options ^ (unsigned int)options;
    this->options = (RenderStateOption)opt;
}

} //NS Renderers
} //NS OpenEngine
