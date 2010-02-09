// Face container.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _FACE_SET_H_
#define _FACE_SET_H_

#include <list>
#include <Math/Vector.h>
#include <Math/Math.h>
#include <Geometry/Face.h>


namespace OpenEngine {
namespace Geometry {

using std::list;
using OpenEngine::Math::Vector;

/**
 * Face list type.
 * Used to ease on the STL syntax and hide the concrete 
 * container type.
 * Should be used instead of containertype<Face*>.
 * @code
 * // use
 * FaceList::iterator itr = myFaceSet.begin();
 * // instead of
 * list<FacePtr>::iterator itr = myFaceSet.begin();
 * @endcode
 */
typedef list<FacePtr> FaceList;

/**
 * Face container.
 *
 * @class FaceSet FaceSet.h Geometry/FaceSet.h
 */
class FaceSet {
private:
    FaceList faces;
public:
    FaceSet();
    FaceSet(FaceSet& faces);
    ~FaceSet();

    FaceList::iterator begin();
    FaceList::iterator end();

    void Add(FacePtr face);
    void Add(FaceSet* fset);
    FaceList::iterator Remove(FaceList::iterator face);
    void Empty();
    int  Size();
    void Split(FacePtr& plane, FaceSet& front, FaceSet& span, FaceSet& back, const float epsilon = EPS);
    void Divide(FacePtr& plane, FaceSet& front, FaceSet& back, const float epsilon = EPS);
    void Divide(FacePtr& plane, FaceSet& front, FaceSet& span, FaceSet& back, FaceSet& split, const float epsilon = EPS);
    void CalcTangentSpace();
};

} // NS Geometry
} // NS OpenEngine

#endif // _FACE_SET_H_
