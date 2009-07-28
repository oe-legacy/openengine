// Box.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GEOMETRY_BOX_H_
#define _GEOMETRY_BOX_H_

#include <Geometry/FaceSet.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Scene/ISceneNode.h>
#include <Scene/GeometryNode.h>
#include <string>
#include <vector>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Math::Vector;
using namespace OpenEngine::Scene;
using std::vector;


/**
 * Geometry box.
 *
 * @class Box Box.h Geometry/Box.h
 */
class Box {

friend class Tests;
    
private:
// private visitor class to collect faces in scene graphs
 class FaceCollector : public ISceneNodeVisitor {
 private:
    FaceSet* faces;
 public:
    FaceCollector(ISceneNode& node) {
        faces = new FaceSet();
        node.Accept(*this);
    }
    
    virtual ~FaceCollector() {};
    
    void VisitGeometryNode(GeometryNode* node) {
        faces->Add(node->GetFaceSet());
    }
     
     FaceSet* GetFaceSet() {
         return faces;
     }
 };
    
    Vector<3,float> center;     //!< Box center
    Vector<3,float> corner;     //!< Box corner (relative)
    Vector<3,float> corners[8]; //!< Box corners (absolute)

    void SetCorner(const bool x, const bool y, const bool z, Vector<3,float> c);
    void SetFromFaces(FaceSet& faces);
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & center;
        ar & corner;
        ar & corners;
    }


public:
    Box() {}; // empty constructor for serialization

    explicit Box(FaceSet& faces);
    explicit Box (ISceneNode& node);
    explicit Box(Vector<3, float> center, Vector<3, float> relCorner);
    
    Vector<3,float> GetCenter() const;
    Vector<3,float> GetCorner() const;
    Vector<3,float> GetCorner(const int index) const;
    Vector<3,float> GetCorner(const bool signX, const bool signY, const bool signZ) const;
};

} //NS Common
} //NS OpenEngine

#endif
