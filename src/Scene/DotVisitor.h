// Dot graph visitor. 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DOT_VISITOR_H_
#define _DOT_VISITOR_H_

#include <Scene/ISceneNodeVisitor.h>

#include <string>
#include <ostream>
#include <sstream>
#include <map>

namespace OpenEngine {
namespace Scene {

// forward declarations of node types
class ISceneNode;
class SceneNode;
class GeometryNode;

using std::string;
using std::ostream;
using std::ostringstream;
using std::map;

/**
 * Dot graph visitor.
 *
 * Creates dot output of a scene structure by crawling the graph as a
 * visitor [GoF 331].
 *
 * Usage:
 * @code
 * ofstream out("mygraph.dot", ios::out); // create output file
 * DotVisitor dot;                        // create dot visitor
 * dot.Write(myGraphNode, out);           // build and write the graph
 * out.close();                           // close your file
 *
 * // To create an image file of the graph your need graphvis
 * // installed. If so you can run the following to create a SVG
 * // image: 
 * $ dot mygraph.dot -Tsvg > mygraph.svg
 * @endcode
 *
 * @class DotVisitor DotVisitor.h Scene/DotVisitor.h
 */
class DotVisitor : public ISceneNodeVisitor {
private:
    ostringstream dotdata;      //!< graph data
    string id;                  //!< id/name of graph
    map<size_t,unsigned int> nodeNames; //!< map of defined names
    unsigned int currentName;   //!< current generated name

    unsigned int GetId(ISceneNode* node);
    void VisitNode(ISceneNode* node, string label);
    void VisitNode(ISceneNode* node, map<string,string>& options);
    
public:
    DotVisitor();
    DotVisitor(string id);
    ~DotVisitor();
    string String(ISceneNode& node);
    void Write(ISceneNode& node, ostream* out);

    void VisitSceneNode(SceneNode* node);
    void VisitGeometryNode(GeometryNode* node);
    void VisitTransformationNode(TransformationNode* node);

};

} // NS Scene
} // NS OpenEngine

#endif // _DOT_VISITOR_H_
