// Dot graph visitor. 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/DotVisitor.h>
#include <Scene/GeometryNode.h>
#include <Scene/SceneNode.h>
#include <Scene/VertexArrayNode.h>

#include <iostream>

namespace OpenEngine {
namespace Scene {

/**
 * Construct unnamed graph.
 */
DotVisitor::DotVisitor() : id(""), currentName(1) {}

/**
 * Construct named graph.
 *
 * @param id Graph id/name
 */
DotVisitor::DotVisitor(string id) : id(id), currentName(1) {}

/**
 * Destructor.
 */
DotVisitor::~DotVisitor() {}

/**
 * Get dot graph string for the graph starting from \a node.
 *
 * @param node Starting node
 * @return dot graph string
 */
string DotVisitor::String(ISceneNode& node) {
    dotdata.flush();
    dotdata << "digraph " << id << " {\n";
    node.Accept(*this);
    dotdata << "}";
    return dotdata.str();
}

/**
 * Write dot graph for the scene starting from \a node.
 *
 * @param node Starting node
 * @param out Output stream to write to
 */
void DotVisitor::Write(ISceneNode& node, ostream* out) {
    *out << String(node);
}

/**
 * Node id generator/store.
 *
 * @param node Pointer to node
 * @return Id of node
 */
unsigned int DotVisitor::GetId(ISceneNode* node) {
    unsigned int nid = nodeNames[(size_t)&*node];
    if (!nid) nid = nodeNames[(size_t)&*node] = currentName++;
    return nid;
}

/**
 * Generic node generator with label.
 *
 * @param node Node to generate output for
 * @param label Label/name of node
 */
void DotVisitor::VisitNode(ISceneNode* node, string label) {
    map<string,string> options;
    options["label"] = label;
    VisitNode(node, options);
}

/**
 * Generic node generator with options.
 *
 * See the dot man page for valid options.
 *
 * @param node Node to generate output for
 * @param options Key-value map of options to set for the node
 */
void DotVisitor::VisitNode(ISceneNode* node, map<string,string>& options) {
    unsigned int nid = GetId(node);
    dotdata << "{" << nid << " [";
    for (map<string,string>::iterator op = options.begin(); op != options.end(); op++)
        dotdata << op->first << "=\"" << op->second << "\" ";
    dotdata << "]}";
    if (node->subNodes.size() > 0) {
        dotdata << " -> { ";
        for (std::list<ISceneNode*>::iterator n = node->subNodes.begin(); 
             n != node->subNodes.end(); n++) {
            dotdata << GetId(*n) << "; ";
        }
        dotdata << "} ";
    }
    dotdata << ";\n";
    node->VisitSubNodes(*this);
}

void DotVisitor::VisitSceneNode(SceneNode* node) {
    VisitNode((ISceneNode*)node, "Scene node");
}

void DotVisitor::VisitGeometryNode(GeometryNode* node) {
    ostringstream label;
    label << "Geometry\\n"
          << "Faces: " << node->GetFaceSet()->Size();
    VisitNode((ISceneNode*)node, label.str());
}

void DotVisitor::VisitVertexArrayNode(VertexArrayNode* node) {
    ostringstream label;
    label << "Vertex array\\n"
          << "Vertex arrays: " << node->GetVertexArrays().size();
    VisitNode((ISceneNode*)node, label.str());
}

void DotVisitor::VisitTransformationNode(TransformationNode* node) {
    VisitNode((ISceneNode*)node, "Transformation");
}

} // NS Modules
} // NS OpenEngine
