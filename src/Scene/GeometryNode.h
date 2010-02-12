// Geometry node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _OE_GEOMETRY_NODE_H_
#define _OE_GEOMETRY_NODE_H_

#include <Scene/ISceneNode.h>
#include <Geometry/FaceSet.h>

namespace OpenEngine {
    namespace Resources {
        class IArchiveWriter;
        class IArchiveReader;
    }
namespace Scene {

/**
 * Geometry node.
 * Acts as a simple node wrapping a face set.
 *
 * @class GeometryNode GeometryNode.h Scene/GeometryNode.h
 */
class GeometryNode : public ISceneNode {
    OE_SCENE_NODE(GeometryNode, ISceneNode)

public:
    GeometryNode();
    GeometryNode(const GeometryNode& node);
    explicit GeometryNode(Geometry::FaceSet* faces);
    ~GeometryNode();

    Geometry::FaceSet* GetFaceSet();
    void SetFaceSet(Geometry::FaceSet* faces);

    const std::string ToString() const;

    void Serialize(Resources::IArchiveWriter& w);
    void Deserialize(Resources::IArchiveReader& r);

private:
    Geometry::FaceSet* faces;


};

} // NS Scene
} // NS OpenEngine


#endif // _OE_GEOMETRY_NODE_H_
