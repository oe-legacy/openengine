// Geometry node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#include <Scene/GeometryNode.h>
#include <Math/Vector.h>
#include <Math/Quaternion.h>
#include <Utils/Convert.h>
#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>
#include <Resources/ISerializable.h>

#include <boost/shared_ptr.hpp>


namespace OpenEngine {
namespace Scene {

using namespace Geometry;
using OpenEngine::Math::Vector;
using OpenEngine::Math::Quaternion;

/**
 * Default constructor.
 * Creates an initial empty face set.
 */
GeometryNode::GeometryNode() {
    faces = new FaceSet();
}

/**
 * Copy constructor.
 * Copy will contain a new face set (with the same faces).
 *
 * @param node Geometry node to copy.
 */
GeometryNode::GeometryNode(const GeometryNode& node)
    : ISceneNode(node)
{
    faces = new FaceSet(*node.faces);
}

/**
 * Face set constructor.
 * The face set will be deleted if replaced by SetFaceSet or upon
 * destruction of the geometry node.
 *
 * @param faces Content of this Geometry Node.
 */
GeometryNode::GeometryNode(FaceSet* faces)
    : faces(faces) {

}

/**
 * Destructor.
 * Deletes the contained face set.
 */
GeometryNode::~GeometryNode() {
    delete faces;
}

/**
 * Get faces this Geometry Node contains.
 * The geometry node retains ownership of the face set.
 *
 * @return FaceSet pointer.
 */
FaceSet* GeometryNode::GetFaceSet() {
    return faces;
}

/**
 * Set FaceSet for this geometry node.
 * This will delete the current face set and bind the new one to
 * the node.
 *
 * @param faces FaceSet pointer.
 */
void GeometryNode::SetFaceSet(FaceSet* faces){
    delete this->faces;
    this->faces = faces;
}

const std::string GeometryNode::ToString() const {
    return GetNodeName()
        + "\nFaces: "
        + Utils::Convert::ToString(faces->Size());
}

void GeometryNode::Serialize(Resources::IArchiveWriter& w) {
    w.WriteInt("length",faces->Size());
    for (FaceList::iterator itr = faces->begin();
         itr != faces->end();
         itr++) {
        w.WriteObjectPtr("face", *itr);
    }
}

void GeometryNode::Deserialize(Resources::IArchiveReader& r) {
    size_t len = r.ReadInt("length");
    while (len--)
        faces->Add(r.ReadObjectPtr<Face>("face"));
}

} //NS Scene
} //NS OpenEngine
