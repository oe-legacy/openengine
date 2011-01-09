// Transformation node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/TransformationNode.h>
#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>

#include <stdio.h>

namespace OpenEngine {
namespace Scene {

    //! Empty constructor.
    TransformationNode::TransformationNode() : scale(Vector<3,float>(1.0f)) {
    }

    /**
     * Copy constructor.
     * Performs a shallow copy.
     *
     * @param node Node to copy.
     */
    TransformationNode::TransformationNode(const TransformationNode& node)
        : ISceneNode(node)
        , ISceneNodeVisitor()
        , IReflectable()
    {
        rotation = node.rotation;
        position = node.position;
        scale = node.scale;
    }

    //! Empty destructor.
    TransformationNode::~TransformationNode() {}

    /**
     * Move transformation.
     * Moves according to the local coordinate system defined by the
     * current direction. 
     *
     * @param x Distance on local x-axis
     * @param y Distance on local y-axis
     * @param z Distance on local z-axis
     */
    void TransformationNode::Move(float x, float y, float z) {
        // add the rotation of v around the current quaternion to the position
        position += rotation.RotateVector(Vector<3,float>(x,y,z)); 
    }

    /**
     * Rotate by Euler angles.
     * Rotates according to the local origin defined by the current
     * position and direction. 
     *
     * @param x x angle
     * @param y y angle
     * @param z z angle
     */
    void TransformationNode::Rotate(float x, float y, float z) {
        // create a quaternion out of the euler angles
        Quaternion<float> q(x, y, z);
        q.Normalize();
        // apply the accumulated rotation
        rotation = rotation * q;
    }

    /**
     * Scaling transformation.
     * Scales the transformation node along the x,y and z axes.
     * For uniform scaling set x = y = z.
     *
     * @param x scale along local x-axis
     * @param y scale along local y-axis
     * @param z scale along local z-axis
     */
    void TransformationNode::Scale(float x, float y, float z) {
        scale[0] *= x;
        scale[1] *= y;
        scale[2] *= z;
    }


    /**
     * Get matrix representation of the transformation.
     *
     * @return Transformation matrix
     */
    Matrix<4,4,float> TransformationNode::GetTransformationMatrix() {
        // get the rotation from the quaternion
        Matrix<4,4,float> m = rotation.GetMatrix().GetExpanded();
        m.Transpose();
        // write in the positional information
        m(3,0) = position[0];
        m(3,1) = position[1];
        m(3,2) = position[2];
        return GetScaleMatrix() * m;
    }

    /**
     * Get the position.
     *
     * @return Vector<3,float> position.
     */
    Vector<3,float> TransformationNode::GetPosition() {
        return position;
    }

    /**
     * Set the position.
     *
     * @param position new position.
     */
    void TransformationNode::SetPosition(Vector<3,float> position) {
        this->position = position;
    }

    /**
     * Get the rotation.
     *
     * @return Quaternion<float> describing the rotation.
     */
    Quaternion<float> TransformationNode::GetRotation() {
        return rotation;
    }

    /**
     * Get the scaling vector.
     *
     * @return Scaling vector.
     */
    Vector<3,float> TransformationNode::GetScale() {
        return scale;
    }

    /**
     * Get the scaling matrix.
     *
     * @return Scaling matrix.
     */
    Matrix<4,4,float> TransformationNode::GetScaleMatrix() {
        return Matrix<4,4,float>(scale[0], 0.0f, 0.0f, 0.0f,
                                 0.0f, scale[1], 0.0f, 0.0f,
                                 0.0f, 0.0f, scale[2], 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f);
    }

    /**
     * Set the rotation.
     *
     * @param rotation new rotation.
     */
    void TransformationNode::SetRotation(Quaternion<float> rotation) {
        this->rotation = rotation;
    }

    /**
     * Set the scaling vector.
     *
     * @param scale new scaling.
     */
    void TransformationNode::SetScale(Vector<3,float> scale) {
        this->scale = scale;
    }

    /**
     * Set the scaling matrix.
     *
     * @param scale new scaling.
     */
    void TransformationNode::SetScale(Matrix<4,4,float> scale) {
        this->scale[0] = scale(0,0);
        this->scale[1] = scale(1,1);
        this->scale[2] = scale(2,2);
    }

    /**
     * Custom visit sub node method.
     * We overwrite the sub node selector to select the parenting node
     * instead. This results in a left-to-root traversal of the tree.
     *
     * @param node Currently visited node.
     */
    void TransformationNode::DefaultVisitNode(ISceneNode* node) {
        ISceneNode* p = node->GetParent();
        if (p != NULL)
            p->Accept(*this);
    }

    /**
     * Visit transformations to collect position and rotation
     * information.
     *
     * @param node Self or parenting transformation node.
     */
    void TransformationNode::VisitTransformationNode(TransformationNode* node) {
        DefaultVisitNode(node);

        // write the result added to this nodes values to the parameters
        accPosition = accRotation.RotateVector(node->position) + accPosition;

        Vector<3,float> rotated = accRotation.RotateVector(node->scale);
        accScale[0] *= rotated[0];
        accScale[1] *= rotated[1];
        accScale[2] *= rotated[2];

        accRotation = accRotation * node->rotation;
    }

    /**
     * Get the accumulated position.
     * Get the position by traversing upwards in the scene tree
     * accumulating the position of all the nodes in the chain.
     *
     * @return Accumulated position vector.
     */
    void TransformationNode::GetAccumulatedTransformations(Vector<3,float>* position, Quaternion<float>* rotation, Vector<3,float>* scale) {
        // reset the accumulators
        accPosition = Vector<3,float>();
        accRotation = Quaternion<float>();
        accScale    = Vector<3,float>(1.0f);
        
        // get the accumulators from the parenting chain
        VisitTransformationNode(this);
        
        // write in results
        *position = accPosition;
        *rotation = accRotation;
        if (scale) *scale = accScale;
    }

    /**
     * Serialize a transformation node.
     */    
    void TransformationNode::Serialize(Resources::IArchiveWriter& w) {
        w.WriteQuaternion<float>("rotation",rotation);
        w.WriteVector<3,float>("position",position);
        w.WriteVector<3,float>("scale",scale);
    }
    /**
     * Deserialize a transformation node.
     */    
    void TransformationNode::Deserialize(Resources::IArchiveReader& r) {
        rotation = r.ReadQuaternion<float>("rotation");
        position = r.ReadVector<3,float>("position");
        scale = r.ReadVector<3,float>("scale");
    }


    const std::string TransformationNode::ToString() const {
        TransformationNode t(*this);
        char str[256];
        /*
        Matrix<4,4,float> m = t.GetTransformationMatrix();
        // Print transformation matrix
        sprintf(str, "%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n", 
                m[0][0], m[0][1], m[0][2], m[0][3],
                m[1][0], m[1][1], m[1][2], m[1][3],
                m[2][0], m[2][1], m[2][2], m[2][3],
                m[3][0], m[3][1], m[3][2], m[3][3]); 
        */

              
        // Print each transformation matrix
        Matrix<4,4,float> m = rotation.GetMatrix().GetExpanded();
        Vector<3,float> pos = position;
        sprintf(str, "%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n", 
                m[0][0], m[0][1], m[0][2], pos[0],
                m[1][0], m[1][1], m[1][2], pos[1],
                m[2][0], m[2][1], m[2][2], pos[2],
                m[3][0], m[3][1], m[3][2], 1.0); 


        /*
        // Print accumulated transformation matrix
        Vector<3,float>   accPos;
        Quaternion<float> accRot;
        Vector<3,float>   accSca;
        t.GetAccumulatedTransformations(&accPos, &accRot, &accSca);
        Matrix<3,3,float> m = accRot.GetMatrix();
     
        sprintf(str, "%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n", 
                m[0][0], m[0][1], m[0][2], accPos[0],
                m[1][0], m[1][1], m[1][2], accPos[1],
                m[2][0], m[2][1], m[2][2], accPos[2],
                    0.0,     0.0,     0.0, 1.0); 
        */

        return str;
    }

} // NS Modules
} // NS OpenEngine
