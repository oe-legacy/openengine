// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_VERTEX_ARRAY_TRANSFORMER_H_
#define _OE_VERTEX_ARRAY_TRANSFORMER_H_

#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
namespace Scene {

/**
 * Vertex Array Transformer.
 * Destructively transforms all nodes of type \a GeometryNode in a scene
 * to nodes of type \a VertexArrayNode.
 *
 * @class VertexArrayTransformer VertexArrayTransformer.h Scene/VertexArrayTransformer.h
 */
class VertexArrayTransformer : public ISceneNodeVisitor{
public:
    VertexArrayTransformer();
    ~VertexArrayTransformer();

    void Transform(ISceneNode& node);
    void VisitGeometryNode(GeometryNode* node);

};

} // NS Scene
} // NS OpenEngine

#endif // _OE_VERTEX_ARRAY_TRANSFORMER_H_
