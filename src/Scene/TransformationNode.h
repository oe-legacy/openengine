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
#include <Core/IReflectable.h>

namespace OpenEngine {
    namespace Resources {
        class IArchiveWriter;
        class IArchiveReader;
    }
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
    class TransformationNode : public ISceneNode
                             , public ISceneNodeVisitor
                             , public Core::IReflectable {
#ifndef SWIG
    OE_SCENE_NODE(TransformationNode, ISceneNode)
#endif
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
    void SetScale(Vector<3,float> scale);
    void SetScale(Matrix<4,4,float> scale);

    Vector<3,float>   GetPosition();
    Quaternion<float> GetRotation();
    Vector<3,float>   GetScale();
    Matrix<4,4,float> GetScaleMatrix();
    Matrix<4,4,float> GetTransformationMatrix();
    void GetAccumulatedTransformations(Vector<3,float>* position, 
                                       Quaternion<float>* rotation, 
                                       Vector<3,float>* scale = NULL);

    void Serialize(Resources::IArchiveWriter& w);
    void Deserialize(Resources::IArchiveReader& r);
    
private:

    //! current rotation quaternion
    Quaternion<float> rotation;

    //! current absolute position vector
    Vector<3,float> position;
    
    //! accumulated rotation from collection traversal
    Quaternion<float> accRotation;

    //! accumulated position from collection traversal
    Vector<3,float> accPosition;

    //! accumulated scale from collection traversal
    Vector<3,float> accScale;

    //! current scaling factor
    //! @todo - represent the scale as x,y,z. Using a 4x4 matrix is plain wast.
    Vector<3,float> scale;
	

protected:

    //! overwritten visiting method
    virtual void DefaultVisitNode(ISceneNode* node);

};

} // NS Scene
} // NS OpenEngine

#endif // _OE_TRANSFORMATION_NODE_H_
