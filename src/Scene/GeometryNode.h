// Geometry node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_NODE_H_
#define _GEOMETRY_NODE_H_

#include <Scene/SceneNode.h>
#include <Geometry/FaceSet.h>
#include <Math/Vector.h>
#include <Math/Quaternion.h>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Geometry::FaceSet;
using OpenEngine::Math::Vector;
using OpenEngine::Math::Quaternion;


/**
 * Geometry node.
 * Acts as a simple node wrapping a face set.
 *
 * @class GeometryNode GeometryNode.h Scene/GeometryNode.h
 */
class GeometryNode : public SceneNode {
private:
    FaceSet* faces;

public:
    /**
     * Default constructor.
     */
    GeometryNode();

    /**
     * Set constructor.
     *
     * @param faces content of this Geometry Node.
     */
    GeometryNode(FaceSet* faces);

    /**
     * Destructor.
     */
    ~GeometryNode();

    /**
     * Get faces this Geometry Node contains.
     *
     * @return FaceSet pointer.
     */
    FaceSet* GetFaceSet();

    /**
     * Set FaceSet for this Geometry Nod.
     *
     * @param faces FaceSet pointer.
     */
    void SetFaceSet(FaceSet* faces);

    /**
     * Accept a visitor.
     *
     * @see ISceneNode::Accept
     */
    void Accept(ISceneNodeVisitor& visitor);

};

} // NS Scene
} // NS OpenEngine

#endif // _GEOMETRY_NODE_H_
