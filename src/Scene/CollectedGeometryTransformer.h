// Face Collecting Transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _COLLECTED_GEOMETRY_TRANSFORMER_H_
#define _COLLECTED_GEOMETRY_TRANSFORMER_H_

#include <Scene/GeometryNode.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Geometry/FaceSet.h>

namespace OpenEngine {
namespace Scene {

/**
 * Face Collecting Transformation.
 * This transformation will traverse a scene and collect the faces of
 * all contained geometry nodes. The resulting scene tree will be the
 * same root node as supplied and exactly one sub node that is a
 * geometry node with the collected faces.
 *
 * @see GeometryNode
 *
 * @class CollectedGeometryTransformer CollectedGeometryTransformer.h Scene/CollectedGeometryTransformer.h
 */
class CollectedGeometryTransformer : public ISceneNodeVisitor {
private:
    FaceSet *faces;
    GeometryNode* georoot;
public:
    CollectedGeometryTransformer();
    ~CollectedGeometryTransformer();

    void Transform(ISceneNode &node);
    GeometryNode* GetCollectedGeometryNode() const;
    FaceSet* GetCollectedFaceSet() const;

    void VisitGeometryNode(GeometryNode *node);
};

} // NS Scene
} // NS OpenEngine

#endif // _COLLECTED_GEOMETRY_TRANSFORMER_H_
