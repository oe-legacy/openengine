// Box.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Box.h>
#include <Geometry/Face.h>
#include <Geometry/Line.h>
#include <Core/Exceptions.h>

#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>

#include <Resources/IDataBlock.h>
#include <Geometry/Mesh.h>
#include <Geometry/GeometrySet.h>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Core::NotImplemented;
using OpenEngine::Math::Vector;

/**
 * Create a bounding box from a set of faces.
 * If the face set is empty the box will have center in [0,0,0] and
 * the corner will be [0,0,0].
 *
 * @param faces Face set to create a box from.
 */
Box::Box(FaceSet& faces) {
    SetFromFaces(faces);
}

/**
 * Create a bounding box from a scene graph.
 * If the scene graph contains no non-empty geometry nodes
 * the box will have center in [0,0,0] and
 * the corner will be [0,0,0].
 *
 * @TODO Make sure that transformation nodes are accounted for!
 * @param node root node to create a box from.
 */
Box::Box(ISceneNode& node) {
    
    FaceCollector fc(node);
    FaceSet* faces = fc.GetFaceSet();
    
    SetFromFaces(*faces);
    delete faces;

}

Box::Box(IDataBlockPtr vecs) {
    Vector<3,float> minV, maxV;

    for (unsigned int i=0;i<vecs->GetSize();i++) {
        Vector<3,float> elm;
        vecs->GetElement(i, elm);
        if (elm[0] < minV[0]) minV[0] = elm[0];
        if (elm[1] < minV[1]) minV[1] = elm[1];
        if (elm[2] < minV[2]) minV[2] = elm[2];

        if (elm[0] > maxV[0]) maxV[0] = elm[0];
        if (elm[1] > maxV[1]) maxV[1] = elm[1];
        if (elm[2] > maxV[2]) maxV[2] = elm[2];
    }

    SetCorner(0,0,0, minV);
    SetCorner(1,1,1, maxV);

    SetCorner(0,0,1, Vector<3,float>(minV[0], minV[1], maxV[2]));
    SetCorner(0,1,0, Vector<3,float>(minV[0], maxV[1], minV[2]));
    SetCorner(1,0,0, Vector<3,float>(maxV[0], minV[1], minV[2]));

    SetCorner(1,0,1, Vector<3,float>(maxV[0], minV[1], maxV[2]));
    SetCorner(0,1,1, Vector<3,float>(minV[0], maxV[1], maxV[2]));
    SetCorner(1,1,0, Vector<3,float>(maxV[0], maxV[1], minV[2]));

    center = (maxV - minV) / 2 + minV;
    corner = maxV - center;

 }

/**
 * Create a bounding box specified by it's center and the relative
 * corner.
 */
Box::Box(Vector<3, float> center, Vector<3, float> relCorner) : center(center), corner(relCorner){
    // compute the corners
    float x = corner[0];
    float y = corner[1];
    float z = corner[2];
    SetCorner(1,1,1, center+Vector<3,float>( x, y, z));
    SetCorner(1,1,0, center+Vector<3,float>( x, y,-z));
    SetCorner(1,0,1, center+Vector<3,float>( x,-y, z));
    SetCorner(1,0,0, center+Vector<3,float>( x,-y,-z));
    SetCorner(0,1,1, center+Vector<3,float>(-x, y, z));
    SetCorner(0,1,0, center+Vector<3,float>(-x, y,-z));
    SetCorner(0,0,1, center+Vector<3,float>(-x,-y, z));
    SetCorner(0,0,0, center+Vector<3,float>(-x,-y,-z));
}
   
void Box::SetFromFaces(FaceSet& faces) {
    if (faces.Size() == 0) return;

    // initialize max and min with the first member of the face set
    FaceList::iterator itr = faces.begin();
    Vector<3,float> max((*itr)->vert[0]);
    Vector<3,float> min(max);

    // find the boundary values
    for (; itr != faces.end(); itr++) {
        for (int i=0; i<3; i++) {
            Vector<3,float> v = (*itr)->vert[i];
            for (int j=0; j<3; j++)
                if (v[j] < min[j]) min[j] = v[j];
                else if (v[j] > max[j]) max[j] = v[j];
        }
    }
    // set box center
    center = (max - min) / 2 + min;
    // set corner vector
    corner = max - center;
    // compute the corners
    float x = corner[0];
    float y = corner[1];
    float z = corner[2];
    SetCorner(1,1,1, center+Vector<3,float>( x, y, z));
    SetCorner(1,1,0, center+Vector<3,float>( x, y,-z));
    SetCorner(1,0,1, center+Vector<3,float>( x,-y, z));
    SetCorner(1,0,0, center+Vector<3,float>( x,-y,-z));
    SetCorner(0,1,1, center+Vector<3,float>(-x, y, z));
    SetCorner(0,1,0, center+Vector<3,float>(-x, y,-z));
    SetCorner(0,0,1, center+Vector<3,float>(-x,-y, z));
    SetCorner(0,0,0, center+Vector<3,float>(-x,-y,-z));
}


Vector<3,float> Box::GetSize() const {
    return GetCorner(1,1,1) - GetCorner(0,0,0);

}

/**
 * Get the center of the box.
 *
 * @return Center of the box.
 */
Vector<3,float> Box::GetCenter() const {
    return center;
}

/**
 * Get the relative corner value.
 * The vector is from the center to the corner and all components have
 * a positive sign.
 *
 * @return Corner vector from center.
 */
Vector<3,float> Box::GetCorner() const {
    return corner;
}

/**
 * Set a corner by its signed index.
 *
 * A positive sign given with: true / 1.
 * A negative sign given with: false / 0.
 *
 * @param signX The sign of the x component relative to the center.
 * @param signY The sign of the y component relative to the center.
 * @param signZ The sign of the z component relative to the center.
 * @param corner The corner position (not relative to the center).
 */
void Box::SetCorner(const bool signX, const bool signY, const bool signZ, Vector<3,float> corner) {
    corners[ signX*1 + signY*2 + signZ*4 ] = corner;
}

/**
 * Get a corner by index.
 * The order of the corners is unspecified. The index range is 0 to 7.
 *
 * @param index The of the corner.
 * @return The absolute corner position given by the index.
 */
Vector<3,float> Box::GetCorner(const int index) const {
    return corners[ index ];
}

/**
 * Get a corner by its signed index.
 *
 * A positive sign given with: true / 1.
 * A negative sign given with: false / 0.
 *
 * @param signX The sign of the x component relative to the center.
 * @param signY The sign of the y component relative to the center.
 * @param signZ The sign of the z component relative to the center.
 * @return The absolute corner position given by the sign index.
 */
Vector<3,float> Box::GetCorner(const bool signX, const bool signY, const bool signZ) const {
    return corners[ signX*1 + signY*2 + signZ*4 ];
}

void Box::Serialize(Resources::IArchiveWriter& w) {
    w.WriteVector<3,float>("center",center);
    w.WriteVector<3,float>("corner",corner);
    w.WriteArray("corners",corners,8);
}
void Box::Deserialize(Resources::IArchiveReader& r) {
    center = r.ReadVector<3,float>("center");
    corner = r.ReadVector<3,float>("corner");
    r.ReadArray("corners",corners,8);
}


} //NS Geometry
} //NS OpenEngine
