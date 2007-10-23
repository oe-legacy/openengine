// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _FACE_H_
#define _FACE_H_

#include <Math/Vector.h>
#include <Resources/ITextureResource.h>
#include <Resources/IShaderResource.h>
#include <Math/Math.h>


namespace OpenEngine {
namespace Geometry {

    //using OpenEngine::Math::Vector;
using namespace OpenEngine::Math;


class Face;
//! Smart pointer to a face object.
typedef boost::shared_ptr<Face> FacePtr;

/**
 * Face structure.
 * Face elements contained in a FaceSet group.
 *
 * @class Face FaceSet.h Geometry/FaceSet.h
 */
class Face {
private:
    void Init();
    void Copy(const Face& face);

public:
    Vector<3,float> vert[3];    //!< vertex vectors
    Vector<3,float> norm[3];    //!< normal vectors
    Vector<2,float> texc[3];    //!< texture coordinates
    Vector<4,float> colr[3];    //!< colors
    Vector<3,float> tang[3];    //!< tangent
    Vector<3,float> bino[3];    //!< binormal
	Vector<3,float> hardNorm;   //!< normal perpendicular to plane defined by face.

    OpenEngine::Resources::ITextureResourcePtr texr; //!< texture resource
    OpenEngine::Resources::IShaderResourcePtr  shad; //!< shader resource

    Face(Vector<3,float> p1, Vector<3,float> p2, Vector<3,float> p3);
    Face(Vector<3,float> p1, Vector<3,float> p2, Vector<3,float> p3,
         Vector<3,float> n1, Vector<3,float> n2, Vector<3,float> n3);

    Face(const Face& face);
    explicit Face(const FacePtr& face);

    ~Face();

	int ComparePointPlane(const Vector<3,float>& point, const float epsilon = EPS);
	Vector<3,int>    ComparePosition(const FacePtr& face, const float epsilon = EPS);

    Vector<3,float>* PlaneIntersection(Vector<3,float> p1, Vector<3,float> p2);
    Vector<3,float>* Intersection(Vector<3,float> p1, Vector<3,float> p2);
    Vector<2,float>  SplitTexture(int p1, int p2, Vector<3,float> inter);
    bool Contains( Vector<3,float> point );

    void CalcTangentSpace();
	void CalcHardNorm();

    bool Verify();
	void Scale(float s);
    std::string ToString();
};

} // NS Geometry
} // NS OpenEngine

#endif
