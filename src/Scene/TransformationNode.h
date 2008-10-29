// Transformation node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_TRANSFORMATION_NODE_H_
#define _OE_TRANSFORMATION_NODE_H_

#include <Scene/ISceneNode.h>
#include <Scene/ISceneNodeVisitor.h>

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Math::Vector;
using OpenEngine::Math::Matrix;
using OpenEngine::Math::Quaternion;

/**
 * Transformation node.
 * When inserted in the scene graph, all successive nodes
 * are influenced by the rotation and positioning of the
 * transformation node. It is the renderer, traversing the
 * scene graph, who is responsible for applying the
 * rotation and positioning.
 *
 * @class TransformationNode TransformationNode.h Scene/TransformationNode.h
 */
class TransformationNode : public ISceneNode, public ISceneNodeVisitor {
    OE_SCENE_NODE(TransformationNode, ISceneNode)

public:

    // constructor / destructor
    TransformationNode();
    TransformationNode(const TransformationNode& node);
    virtual ~TransformationNode();

    // ISceneNodeVisitor methods
    void VisitTransformationNode(TransformationNode* node);

    // New transformation methods
    void Move(float x, float y, float z);
    void Rotate(float x, float y, float z);
    void Scale(float x, float y, float z);

    void SetPosition(Vector<3,float> position);
    void SetRotation(Quaternion<float> rotation);
    void SetScale(Matrix<4,4,float> scale);

    Vector<3,float>   GetPosition();
    Quaternion<float> GetRotation();
    Matrix<4,4,float> GetScale();
    Matrix<4,4,float> GetTransformationMatrix();
    void GetAccumulatedTransformations(Vector<3,float>* position, Quaternion<float>* rotation);

private:

    //! current rotation quaternion
    Quaternion<float> rotation;

    //! current absolute position vector
    Vector<3,float> position;
    
    //! accumulated rotation from collection traversal
    Quaternion<float> accRotation;

    //! accumulated position from collection traversal
    Vector<3,float> accPosition;

    //! current scaling factor
    //! @todo - represent the scale as x,y,z. Using a 4x4 matrix is plain wast.
    Matrix<4,4,float> scale;
	
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & rotation;
        ar & position;
        ar & accRotation;
        ar & accPosition;
        ar & scale;
    }

protected:

    //! overwritten visiting method
    virtual void DefaultVisitNode(ISceneNode* node);

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::TransformationNode)

#endif // _OE_TRANSFORMATION_NODE_H_
