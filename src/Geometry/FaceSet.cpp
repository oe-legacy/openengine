// Face container.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Geometry/FaceSet.h>
#include <Geometry/Face.h>
#include <Core/Exceptions.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Geometry {

using OpenEngine::Core::Exception;
using namespace OpenEngine::Logging;

/**
 * Default constructor.
 */
FaceSet::FaceSet() {}

/**
 * Copy constructor.
 */
FaceSet::FaceSet(FaceSet& faces) {
    Add(&faces);
}

/**
 * Destructor.
 */
FaceSet::~FaceSet() {}

/**
 * Face starting iterator.
 * For iterating over all the faces in the set.
 * See the standard documentation of list::begin for documentation.
 *
 * @return Face iteratior
 */
FaceList::iterator FaceSet::begin() { return faces.begin(); }

/**
 * Face ending iterator.
 * For identifying the end when iterating over faces in the set.
 * See the standard documentation of list::end for documentation.
 *
 * @return Face iteratior
 */
FaceList::iterator FaceSet::end() { return faces.end(); }

/**
 * Add a face to the set.
 *
 * @param face Face to add
 */
void FaceSet::Add(FacePtr face) {
    faces.push_back(face);
}

/**
 * Add a set of faces to the set
 *
 * @param fset Set of faces to add
 */
void FaceSet::Add(FaceSet* fset) {
    if(fset == NULL ) return;
    for(FaceList::iterator itr=fset->begin(); itr!=fset->end(); itr++)
        faces.push_back(*itr);
}

/**
 * Remove a face from the face set.
 *
 * @param face Face iterator.
 */
void FaceSet::Remove(FaceList::iterator face) {
    faces.erase(face);
}

/**
 * Size of the set
 *
 * @return Size of set
 */
int FaceSet::Size() { return faces.size(); }

/**
 * Split the set into two non-overlapping sets.
 * If a face overlaps the splitting plane it will by split into two
 * new faces.
 *
 * @note This algorithm is based on triangle::split in CTA page 393.
 *
 * @param plane Face-plane to split by.
 * @param front Face set to add faces in front of the plane to.
 * @param span Face set to add faces in span of the plane to.
 * @param back  Face set to add faces behind the plane to.
 * @param epsilon Width of spanning plane [optional].
 */
void FaceSet::Split(FacePtr& plane, FaceSet& front, FaceSet& span, FaceSet& back, const float epsilon) {
    for (FaceList::iterator itr = faces.begin(); itr != faces.end(); itr++) {
        FacePtr face = *itr;
        Vector<3,int> positions = plane->ComparePosition(face, epsilon);
		switch (positions.Sum()) {
        case -3:
        case -2:
            // face is behind
            back.Add(face);
            break;
        case 3:
        case 2:
            // face is in front
            front.Add(face);
            break;
        case 0:
            if (positions[0] || positions[1] || positions[2]) {
                // one point in plane and one on each side
                // split the face in two
                int pos, neg, piv;
                if (!positions[0]) {
                    piv = 0;
                    if (positions[1] > 0) { pos = 1; neg = 2; }
                    else { pos = 2; neg = 1; }
                } else if (!positions[1]) {
                    piv = 1;
                    if (positions[0] > 0) { pos = 0; neg = 2; }
                    else { pos = 2; neg = 0; }
                } else if (!positions[2]) {
                    piv = 2;
                    if (positions[1] > 0) { pos = 1; neg = 0; }
                    else { pos = 0; neg = 1; }
                }
                // compute intersection between the positive and
                // negative points
                Vector<3,float>* fint = plane->PlaneIntersection(face->vert[pos], 
                                                                 face->vert[neg]);

                // if the vertex from the face equals the one we just found, the
                // face is too small to split and we throw it away.
                if (*fint == face->vert[piv]) {
                    delete fint;
                    break;
                }

                // texture intersection
                Vector<2,float> tint = face->SplitTexture(pos,neg,*fint);
                Vector<3,float> norm = face->norm[pos] + face->norm[neg];
                norm.Normalize();
                // create face on positive side
                FacePtr f1 = FacePtr(new Face(face));
                f1->vert[0] = face->vert[pos];
                f1->vert[1] = Vector<3,float>(*fint);
                f1->vert[2] = face->vert[piv];
                f1->norm[0] = face->norm[pos];
                f1->norm[1] = norm;
                f1->norm[2] = face->norm[piv];
                f1->texc[0] = face->texc[pos];
                f1->texc[1] = tint;
                f1->texc[2] = face->texc[piv];
                // create face on negative side
                FacePtr b1 = FacePtr(new Face(face));
                b1->vert[0] = face->vert[neg];
                b1->vert[1] = face->vert[piv];
                b1->vert[2] = Vector<3,float>(*fint);
                b1->norm[0] = face->norm[neg];
                b1->norm[1] = face->norm[piv];
                b1->norm[2] = norm;
                b1->texc[0] = face->texc[neg];
                b1->texc[1] = face->texc[piv];
                b1->texc[2] = tint;
                // add faces
                if (f1->Verify()) { f1->CalcHardNorm(); front.Add(f1); }
                if (b1->Verify()) { b1->CalcHardNorm(); back.Add(b1); }
                delete fint;
                break;
            } else {
                // face is in the plane
                span.Add(face);
                break;
            }
        case -1:
            if (positions[0] == 0 || positions[1] == 0 || positions[2] == 0) {
				// two points must be zero, so the face is behind
                back.Add(face);
                break;
            } else {
                // one point is positive and two negative
                int pos, neg1, neg2;
                if (positions[0] == 1) { pos=0; neg1=1; neg2=2; }
                if (positions[1] == 1) { pos=1; neg1=0; neg2=2; }
                if (positions[2] == 1) { pos=2; neg1=0; neg2=1; }


                Vector<3,float>* fint1 = plane->PlaneIntersection(face->vert[neg1],
                                                                  face->vert[pos]);
                Vector<3,float>* fint2 = plane->PlaneIntersection(face->vert[neg2],
                                                                  face->vert[pos]);


                Vector<2,float> tint1 = face->SplitTexture(pos,neg1,*fint1);
                Vector<2,float> tint2 = face->SplitTexture(pos,neg2,*fint2);

                Vector<3,float> norm1 = face->norm[pos] + face->norm[neg1];
                Vector<3,float> norm2 = face->norm[pos] + face->norm[neg2];
                norm1.Normalize();
                norm2.Normalize();

                // create front face (pos, i1, i2)
                FacePtr f1 = FacePtr(new Face(face));
                f1->vert[0] = face->vert[pos];
                f1->vert[1] = Vector<3,float>(*fint1);
                f1->vert[2] = Vector<3,float>(*fint2);                
                f1->norm[0] = face->norm[pos];
                f1->norm[1] = norm1;
                f1->norm[2] = norm2;
                f1->texc[0] = face->texc[pos];
                f1->texc[1] = tint1;
                f1->texc[2] = tint2;
                // create two back faces (neg2, i2, i1)
                FacePtr b1 = FacePtr(new Face(face));
                b1->vert[0] = face->vert[neg2];
                b1->vert[1] = Vector<3,float>(*fint2);
                b1->vert[2] = Vector<3,float>(*fint1);
                b1->norm[0] = face->norm[neg2];
                b1->norm[1] = norm2;
                b1->norm[2] = norm1;
                b1->texc[0] = face->texc[neg2];
                b1->texc[1] = tint2;
                b1->texc[2] = tint1;
                // (neg2, i1, neg1)
                FacePtr b2 = FacePtr(new Face(face));
                b2->vert[0] = face->vert[neg2];
                b2->vert[1] = Vector<3,float>(*fint1);
                b2->vert[2] = face->vert[neg1];
                b2->norm[0] = face->norm[neg2];
                b2->norm[1] = norm1;
                b2->norm[2] = face->norm[neg1];
                b2->texc[0] = face->texc[neg2];
                b2->texc[1] = tint1;
                b2->texc[2] = face->texc[neg1];

                // if the two intersection points are equal we have
                // found a face that is very slim and therefor the
                // intersection point on each line becomes the same
                // due to our limited precision. In this case we
                // choose to add the one resulting back face and throw
                // away the collapsed front face.
                if (*fint1 == *fint2) {
                    if (b2->Verify()) {
                        b2->CalcHardNorm();
                        back.Add(b2);
                    } else logger.warning << "Back face is invalid" << logger.end;
                } else {
                    // add the faces
                    if (f1->Verify()) { f1->CalcHardNorm(); front.Add(f1); }
                    else logger.warning << "f1 in case -1 is invalid after split, "
                                        << "a larger epsilon value might help." << logger.end;
                    if (b1->Verify()) { b1->CalcHardNorm(); back.Add(b1); }
                    else logger.warning << "b1 in case -1 is invalid after split, "
                                        << "a larger epsilon value might help." << logger.end;
                    if (b2->Verify()) { b2->CalcHardNorm(); back.Add(b2); }
                    else logger.warning << "b2 in case -1 is invalid after split, "
                                        << "a larger epsilon value might help." << logger.end;
                }
                delete fint1;
                delete fint2;
                break;
            }
        case 1:
			if (positions[0]==0 || positions[1]==0 || positions[2] == 0) {
    			// two points must be zero, so the face is in front
				front.Add(face);
                break;
            } else {
                // one point is negative and two positive
                int pos1, pos2, neg;
                if (positions[0] == -1) { pos1=1; pos2=2; neg=0; }
                if (positions[1] == -1) { pos1=0; pos2=2; neg=1; }
                if (positions[2] == -1) { pos1=0; pos2=1; neg=2; }

                Vector<3,float>* fint1 = plane->PlaneIntersection(face->vert[pos1],
                                                                 face->vert[neg]);

                Vector<3,float>* fint2 = plane->PlaneIntersection(face->vert[pos2],
                                                                 face->vert[neg]);
                
                Vector<2,float> tint1 = face->SplitTexture(pos1,neg,*fint1);
                Vector<2,float> tint2 = face->SplitTexture(pos2,neg,*fint2);
                Vector<3,float> norm1 = face->norm[pos1] + face->norm[neg];
                Vector<3,float> norm2 = face->norm[pos2] + face->norm[neg];
                norm1.Normalize();
                norm2.Normalize();
                // create front face (pos1, i1, i2)
                FacePtr f1 = FacePtr(new Face(face));
                f1->vert[0] = face->vert[pos1];
                f1->vert[1] = Vector<3,float>(*fint1);
                f1->vert[2] = Vector<3,float>(*fint2);
                f1->norm[0] = face->norm[pos1];
                f1->norm[1] = norm1;
                f1->norm[2] = norm2;
                f1->texc[0] = face->texc[pos1];
                f1->texc[1] = tint1;
                f1->texc[2] = tint2;
                // one of two back faces (pos1, i2, pos2)
                FacePtr f2 = FacePtr(new Face(face));
                f2->vert[0] = face->vert[pos1];
                f2->vert[1] = Vector<3,float>(*fint2);
                f2->vert[2] = face->vert[pos2];
                f2->norm[0] = face->norm[pos1];
                f2->norm[1] = norm2;
                f2->norm[2] = face->norm[pos2];
                f2->texc[0] = face->texc[pos1];
                f2->texc[1] = tint2;
                f2->texc[2] = face->texc[pos2];
                // create back face (neg, i2, i1)
                FacePtr b1 = FacePtr(new Face(face));
                b1->vert[0] = face->vert[neg];
                b1->vert[1] = Vector<3,float>(*fint2);
                b1->vert[2] = Vector<3,float>(*fint1);
                b1->norm[0] = face->norm[neg];
                b1->norm[1] = norm2;
                b1->norm[2] = norm1;
                b1->texc[0] = face->texc[neg];
                b1->texc[1] = tint2;
                b1->texc[2] = tint1;

                // check we don't collapse any edges when splitting
                // symmetrical to the previous case (case -1).
                if (*fint1 == *fint2) {
                    if (f2->Verify()) {
                        f2->CalcHardNorm();
                        front.Add(f2);
                    } else logger.warning << "Front face is invalid" << logger.end;
                } else {
                    // add the faces
                    if (f1->Verify()) { f1->CalcHardNorm(); front.Add(f1); }
                    else logger.warning << "f1 in case 1 is invalid after split, "
                                        << "a larger epsilon value might help." << logger.end;
                    if (f2->Verify()) { f2->CalcHardNorm(); front.Add(f2); }
                    else logger.warning << "f2 in case 1 is invalid after split, "
                                        << "a larger epsilon value might help." << logger.end;
                    if (b1->Verify()) { b1->CalcHardNorm(); back.Add(b1); }
                    else logger.warning << "b1 in case 1 is invalid after split, "
                                        << "a larger epsilon value might help." << logger.end;
                }
                delete fint1;
                delete fint2;
                break;
            }
        }
    }
}

/**
 * Divide the set into two possibly overlapping sets by a given face.
 *
 * @param plane Face-plane to divide by.
 * @param front Face set to add faces in front of the plane to.
 * @param back  Face set to add faces behind the plane to.
 * @param epsilon Width of spanning plane [optional].
 */
void FaceSet::Divide(FacePtr& plane, FaceSet& front, FaceSet& back, const float epsilon) {
    FaceList::iterator itr;
    for (itr = faces.begin(); itr!=faces.end(); itr++) {
        FacePtr f = (*itr);
        int pos = plane->ComparePosition(f,epsilon).Sum();
        if (pos <= -2)
            back.Add(f);
        else if (pos >= 2)
            front.Add(f);
        else {
            back.Add(f);
            front.Add(f);
        }
    }
}

/**
 * Calculate tangent and binormals for all faces
 *
 * @see Face::CalcTangentSpace();
 */
void FaceSet::CalcTangentSpace(){
    FaceList::iterator itr;
    for (itr = faces.begin(); itr!=faces.end(); itr++) {
        (*itr)->CalcTangentSpace();
    }
}

/**
 * Empty the face set.
 */
void FaceSet::Empty(){
    faces.clear();
}

} // NS Geometry
} // NS OpenEngine
