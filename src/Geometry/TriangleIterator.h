//TODO: Tjek form, vha getType på meshNode

#ifndef _TRIANGLE_ITERATOR_H
#define _TRIANGLE_ITERATOR_H

#include <Math\Vector.h>
#include <Scene/MeshNode.h>

#include <iostream>
using namespace std;

namespace OpenEngine {
namespace Geometry {

// Example Usage:
//
// TriangleIterator TI(triangleMesh->GetMesh(x));
// for(TI.first(); TI.isGood(); TI++)
// {
//    triMesh->addTriangle(toBtVec(TI.vec[0]), toBtVec(TI.vec[1]), toBtVec(TI.vec[2]));
// }
//

class TriangleIterator
{
	//---------
	//Functions
	public:
		//Constructors
		TriangleIterator(MeshPtr mesh)
		{
			Vertices = mesh->GetGeometrySet()->GetVertices();
			Indices = mesh->GetIndices();
			index=0;
		}
		TriangleIterator(MeshNode *node)
		{
			Vertices = node->GetMesh()->GetGeometrySet()->GetVertices();
			Indices = node->GetMesh()->GetIndices();
			index=0;
			//TriangleIterator(node->GetMesh());
		}
		~TriangleIterator(){}
	
		//Functionality
        void first()
        {
            index=0;
        }

        bool isGood()
        {
            return index<Indices->GetSize();
        }

        bool isDone()
        {
            return index>=Indices->GetSize();
        }

        void operator++(int)
        {
            next();
        }

    private:
		void next()
		{
			#ifdef OE_SAFE
			if(index>=Indices->GetSize())
				throw IndexOutOfBounds(index, 0, Indices->GetSize());
			#endif
			Vertices->GetElement(Indices->GetElement(index)[0],   vec[0]);
			Vertices->GetElement(Indices->GetElement(index+1)[0], vec[1]);
			Vertices->GetElement(Indices->GetElement(index+2)[0], vec[2]);
			index+=3;
		}
	protected:
	//---------
	//Variables
	public:
		Vector<3,float> vec[3];
	private:
		unsigned int index;
		//These are drawn out of the MeshNode
		Resources::IDataBlockPtr Vertices;
		IndicesPtr Indices;
	protected:
};

} // NS Geometry
} // NS OpenEngine

#endif // _TRIANGLE_ITERATOR_H
