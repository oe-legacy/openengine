// Face representation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/Face.h>
#include <Logging/Logger.h>
#include <math.h>
#include <Math/Math.h>

namespace OpenEngine {
namespace Geometry {

using namespace std;
using namespace OpenEngine::Math;

// Shared initialization code
void Face::Init() {
    // Set white as default color
    colr[0] = colr[1] = colr[2] = colr[3] = Vector<4,float>(1);
    // Calculate the face hard normal
    CalcHardNorm();
    // Calculate the binormals and tangents
    CalcTangentSpace();

    // For now we initialize a default material to avoid NULL pointer exceptions
    mat = MaterialPtr(new Material());
}

// Shared copy initialization code
void Face::Copy(const Face& face) {
    for (int i=0; i<3; i++) {
        vert[i] = face.vert[i];
        norm[i] = face.norm[i];
        texc[i] = face.texc[i];
        colr[i] = face.colr[i];
		tang[i] = face.tang[i];
		bino[i] = face.bino[i];
    }
  	hardNorm = face.hardNorm;
    mat = face.mat;
//     texr = face.texr;
//     shad = face.shad;    
}

/**
 * Construct a face by points.
 *
 * @param p1 first point.
 * @param p2 second point.
 * @param p3 third point.
 */
Face::Face(Vector<3,float> p1, Vector<3,float> p2, Vector<3,float> p3) {
    vert[0] = p1;
    vert[1] = p2;
    vert[2] = p3;
    Init();
}

/**
 * Construct a face by points and normals.
 *
 * @param p1 first point.
 * @param p2 second point.
 * @param p3 third point.
 * @param n1 first normal.
 * @param n2 second normal.
 * @param n3 third normal.
 */
Face::Face(Vector<3,float> p1, Vector<3,float> p2, Vector<3,float> p3,
           Vector<3,float> n1, Vector<3,float> n2, Vector<3,float> n3) {
    vert[0] = p1;
    vert[1] = p2;
    vert[2] = p3;
    norm[0] = n1;
    norm[1] = n2;
    norm[2] = n3;
    Init();
}

/**
 * Copy constructor for a smart pointer.
 *
 * @param face Face to copy
 */
Face::Face(const FacePtr& face) {
    Copy(*face);
}

/**
 * Copy constructor for a smart pointer.
 *
 * @param face Face to copy
 */
Face::Face(const Face& face) {
    Copy(face);
}

/**
 * Destructor.
 */
Face::~Face() {

}

/**
 * Compare the position of a face and a point.
 *
 * -1: point is behind the plane.
 *  0: point is in the plane
 *  1: point is in front of the plane.
 *
 * @param point Point to test up againt face.
 * @param epsilon Thickness of face [optional]
 * @return Vector of point positions as described above
 */
int Face::ComparePointPlane(const Vector<3,float>& point, const float epsilon) {
	if (hardNorm.GetLength() == 0.0f) {
		logger.warning << "hardNorm is 0.0f: " << vert[0] << ","
                       << vert[1] << "," << vert[2] << logger.end;
    }

    // Calculate the distance from constraint p1 to plane.
    float distance = (hardNorm * (point - vert[0]));

    // If the distance is behind the plane correct p1
    if (distance > epsilon) return 1;
    else if (distance < -epsilon) return -1;
	else return 0;
}

/**
 * Compare the position of two faces.
 *
 * -1: point is behind the plane.
 *  0: point is in the plane
 *  1: point is in front of the plane.
 *
 * @param face Face to compare with
 * @param epsilon Thickness of faces [optional]
 * @return Vector of point positions as described above
 */
Vector<3,int> Face::ComparePosition(const FacePtr& face, const float epsilon) {
    if( this == face.get() ) return Vector<3,int>(0);
    Vector<3,int> result;
	for(int i=0; i<3; i++)
		result[i] = this->ComparePointPlane(face->vert[i], epsilon);
	return result;
}

/**
 * Find the intersection of a line in the plane defined by the face.
 *
 * @todo Add errors for special cases
 *
 * @param p1 First point of line.
 * @param p2 Second point of line.
 * @return Point of intersection or NULL if no intersection is found.
 */
Vector<3,float>* Face::PlaneIntersection(Vector<3,float> p1, Vector<3,float> p2) {
    // convert to doubles to preserve precision in calculations
    Vector<3,double> hn = hardNorm.ToDouble();
    Vector<3,double> d1 = p1.ToDouble();
    Vector<3,double> d2 = p2.ToDouble();

    double a = hn * (d2 - d1);
    if (fabs(a) < EPS)
        // the line is parallel with the plane
        return NULL;

    double s = (hn * (vert[0].ToDouble() - d1)) / a;
    if (s < 0 || s > 1) 
        // the line segment does not intersect between p1 and p2.
        return NULL;

    // calculate the intersection
    Vector<3,double> tmp(d1 + ((d2-d1) * s));

    // return as a float vector
    return new Vector<3,float>(tmp.ToFloat());  
}

/**
 * Find the intersection of a line in the face.
 *
 * @param p1 First point of line
 * @param p2 Second point of line
 * @return Point of intersection or null if not intersecting.
 */
Vector<3,float>* Face::Intersection(Vector<3,float> p1, Vector<3,float> p2) {
    Vector<3,float>* intersectionPoint = PlaneIntersection(p1,p2);

    // If not intersecting just return NULL
    if (intersectionPoint == NULL)
        return NULL;
    
    if (this->Contains(*intersectionPoint))
        return intersectionPoint;

    // If the intersection was not in the face itself delete the
    // pointer and return null.
    delete intersectionPoint;
    return NULL;
}
    
/**  
 * Method 3, from http://www.blackpawn.com/texts/pointinpoly/default.html
 **/
bool Face::Contains( Vector<3,float> point ) {
    // Compute vectors        
    Vector<3,float> v0 = vert[2] - vert[0];
    Vector<3,float> v1 = vert[1] - vert[0];
    Vector<3,float> v2 = point - vert[0];

    // Compute dot products
    double dot00 = v0 * v0;
    double dot01 = v0 * v1;
    double dot02 = v0 * v2;
    double dot11 = v1 * v1;
    double dot12 = v1 * v2;

    // Compute barycentric coordinates
    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    if ((u >= 0) && (v >= 0) && (u + v <= 1))
        return true;
    else
        return false;
}

/**
 * Get the texture coordinate vector for a face split.
 *
 * @param p1 Index of first face edge point
 * @param p2 Index of second face edge point
 * @param inter Point of intersection on face edge
 * @return Vector with texture coordinates for the point of intersection
 */
Vector<2,float> Face::SplitTexture(int p1, int p2, Vector<3,float> inter) {
    float scale = (inter - vert[p1]).GetLength() / (vert[p2] - vert[p1]).GetLength();
    return texc[p1] + (texc[p2] - texc[p1]) * scale;
}

/**
 * Calculate the hard normal for a face.
 *
 * If the face contains soft normals the calculated hard normal will
 * point in the same direction and the points of the face will be
 * swapped if necessary.
 *
 * If a face point is changed this method will need to be called in
 * order to update the hard normal.
 */
void Face::CalcHardNorm() {
    // Verify that the face defines a plane
    if (!Verify()) throw Exception("CalcHardNorm on invalid face");

    // Calculate face normal - we need normals perpendicular to the face
    // so we can't use the loaded face normals because they might be soft.
    Vector<3,double> v1 = vert[1].ToDouble() - vert[0].ToDouble();
    Vector<3,double> v2 = vert[2].ToDouble() - vert[0].ToDouble();
    Vector<3,double> h = v1 % v2;
    h.Normalize();
    hardNorm = h.ToFloat();

    // check if the normal is valid
    if (h.IsZero()) {
        logger.warning << "Normal is zero due to invalid face." << logger.end;
        return;
    }

    // If no soft normals are set calculate the hard normal by point order.
    if (norm[0].IsZero()) return;

    // Else check the sign against a soft normal in case the normal
    // points in the wrong direction!
    Vector<3,float> softNorm = hardNorm - norm[0].GetNormalize();
    float signVec = softNorm * softNorm;
    if (signVec > 2.0f) {
        // swap data for vert[1] and vert[2] and flip the hard normal
        Vector<3,float> tmp = vert[1];
        vert[1] = vert[2];
        vert[2] = tmp;

        tmp = norm[1];
        norm[1] = norm[2];
        norm[2] = tmp;

        tmp = tang[1];
        tang[1] = tang[2];
        tang[2] = tmp;

        tmp = bino[1];
        bino[1] = bino[2];
        bino[2] = tmp;

        Vector<2,float> tmp2 = texc[1];
        texc[1] = texc[2];
        texc[2] = tmp2;

        Vector<4,float> tmp3 = colr[1];
        colr[1] = colr[2];
        colr[2] = tmp3;

        hardNorm *= -1;
    }
}

/**
 * Calculate tangents and binormals for each vertex
 */
void Face::CalcTangentSpace() {
    // int len = v.length;
	Vector<3,float> s[3];
	Vector<3,float> t[3];
	Vector<3,int> triCount;
	for(int i=0; i<3; i++) {
		float u13u = texc[2][0] - texc[0][0];
		float u13v = texc[2][1] - texc[0][1];
		float u12u = texc[1][0] - texc[0][0];
		float u12v = texc[1][1] - texc[0][1];
		Vector<3,float> v1v2 = vert[1] - vert[0];
		Vector<3,float> v1v3 = vert[2] - vert[0];
				
		float det_inv = 1.0f / (u12u * u13v - u13u * u12v);

		Vector<3,float> p = det_inv * (u13v * v1v2 - u12v * v1v3);
		Vector<3,float> q = det_inv * (u12u * v1v3 - u13u * v1v2);

        for (int k=0; k<3; k++) {
            s[k] += p;
            t[k] += q;
        }
		triCount[0]++;
		triCount[1]++;
		triCount[2]++;
	}
	for(int i=0; i<3; i++) {
		if(triCount[i]) {
			s[i] /= triCount[i];
			t[i] /= triCount[i];
		}
		s[i].Normalize();
		t[i].Normalize();
        for (int k=0; k<3; k++) {
            bino[i][k] = t[i][k];
            tang[i][k] = s[i][k];
        }
	}
}

/**
 * Verify that no edges are collapsed.
 *
 */
bool Face::Verify() {
    // Verify that the face defines a plane
    if (vert[0] == vert[1] ||
        vert[1] == vert[2] ||
        vert[0] == vert[2]) return false;
    return true;
}


/**
 * Scale face by s.
 *
 * @param s scaling factor.
 */
void Face::Scale(float s) {
    for (int i=0; i<3; ++i)
        vert[i] *= s;
}

/**
 * Create string representation of face, just for debugging purpose.
 *
 * @return string rep. of face.
 */
std::string Face::ToString() {
    std::string str = "\n";
    str += " vert[0]: " + vert[0].ToString() + "\n";
    str += " vert[1]: " + vert[1].ToString() + "\n";
    str += " vert[2]: " + vert[2].ToString() + "\n";
    str += " norm[0]: " + norm[0].ToString() + "\n";
    str += " norm[1]: " + norm[1].ToString() + "\n";
    str += " norm[2]: " + norm[2].ToString() + "\n";
    str += " hardNorm: " + hardNorm.ToString();
    return str;
}

} // NS Geometry
} // NS OpenEngine
