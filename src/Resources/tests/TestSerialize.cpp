#include <Testing/Testing.h>

#include <list>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>
#include <iostream>
#include <sstream>

#include <Resources/StreamArchive.h>
#include <Resources/BinaryStreamArchive.h>
#include <Scene/SceneNode.h>
#include <Scene/TransformationNode.h>
#include <Scene/RenderStateNode.h>
#include <boost/shared_ptr.hpp>

using namespace OpenEngine::Resources;
using namespace std;
using namespace boost;

using namespace OpenEngine::Math;
using namespace OpenEngine::Scene;



void test_primitives_write(IArchiveWriter& w) {
    w.WriteInt("douglas",42);
    w.WriteFloat("douglas",42.01f);

}
void test_primitives_read(IArchiveReader& r) {
    int in = r.ReadInt("douglas");
    OE_CHECK(in == 42);
    float inf = r.ReadFloat("douglas");   
    OE_CHECK(inf == 42.01f);

    // w.WriteDouble("douglas",42.02);
    // double ind = r.ReadDouble("douglas");
    // OE_CHECK(ind == 42.02);

}


void test_collection_write(IArchiveWriter& w) {

    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    // Serialize it
    
    w.WriteCollection<list<int>, int>("list1",list1);
}
void test_collection_read(IArchiveReader& r) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    // Deserialize
    
    list<int> list2 = r.ReadCollection<list<int>, int>("list1");

    OE_CHECK(list1.size() == list2.size());

    list<int>::iterator itr1, itr2;

    for (itr1 = list1.begin(), itr2 = list2.begin();
         itr1 != list1.end();
         itr1++, itr2++ ) {
        OE_CHECK(*itr1 == *itr2);
    }

}

void test_Matrix_write(IArchiveWriter& w) {
    Matrix<2,2,float> m(1.1f, 2.2f, 3.3f, 4.4f);
    

    w.WriteMatrix<2,2,float>("matrix",m);

}
void test_Matrix_read(IArchiveReader& r) {
    Matrix<2,2,float> m2 = r.ReadMatrix<2,2,float>("matrix");

    //cout << m2.ToString() << endl;

    OE_CHECK(m2(0,0) == 1.1f);
    OE_CHECK(m2(0,1) == 2.2f);
    OE_CHECK(m2(1,0) == 3.3f);
    OE_CHECK(m2(1,1) == 4.4f);
    
}



void test_Vector_write( IArchiveWriter& w) {
    Vector<3,float> v1(1.0,2.0,3.0);
    w.WriteVector<3,float>("v1",v1);

}
void test_Vector_read(IArchiveReader& r) {
    Vector<3,float> v1(1.0,2.0,3.0);
    Vector<3,float>  v2 = r.ReadVector<3,float>("v1");

    OE_CHECK(v2 == v1);    
}

void test_Quaternion_write( IArchiveWriter& w) {
    Quaternion<float> q1(1,2,3,4);    
    w.WriteQuaternion<float>("q1",q1);

}
void test_Quaternion_read(IArchiveReader& r) {
    Quaternion<float> q1(1,2,3,4);    
    Quaternion<float> q2 = r.ReadQuaternion<float>("q1");


    OE_CHECK(q2 == q1);    
}


void test_scene_write(IArchiveWriter& w) {
    SceneNode* node = new SceneNode();
    SceneNode* n1 = new SceneNode();
    SceneNode* n2 = new SceneNode();
    SceneNode* n3 = new SceneNode();

    TransformationNode* tn = new TransformationNode();
    
    tn->SetPosition(Vector<3,float>(1,2,3));

    node->AddNode(n1);
    node->AddNode(n2);
    n1->AddNode(n3);
    n3->AddNode(tn);

    w.WriteScene("root", node);

    delete node;
}

void test_scene_read(IArchiveReader& r) {

    ISceneNode* node =
        r.ReadScene("root");

    OE_CHECK(node->GetNumberOfNodes() == 2);
    ISceneNode *n1 = node->GetNode(0);
    OE_CHECK(n1->GetNumberOfNodes() == 1);
    ISceneNode *n3 = n1->GetNode(0);
    
    ISceneNode *tn = n3->GetNode(0);
    
    OE_CHECK( typeid(*tn) == typeid(TransformationNode));
    
    TransformationNode* tn1 = dynamic_cast<TransformationNode*>(tn);
    
    OE_CHECK((tn1->GetPosition() == Vector<3,float>(1,2,3)));
}

void test_RenderStateNode_write(IArchiveWriter& w) {
    RenderStateNode* rsn = new RenderStateNode();
    rsn->EnableOption(RenderStateNode::LIGHTING);
    w.WriteScene("rsn",rsn);
}

void test_RenderStateNode_read(IArchiveReader& r) {
    RenderStateNode* node = dynamic_cast<RenderStateNode*>(r.ReadScene("rsn"));
    OE_CHECK(node != NULL);

    OE_CHECK(node->IsOptionEnabled(RenderStateNode::LIGHTING));
}

void test_WriteArray(IArchiveWriter& w) {
    Vector<3,float> vec[3];
    vec[0] = Vector<3,float>(1,1,1);
    vec[1] = Vector<3,float>(2,2,2);
    vec[2] = Vector<3,float>(3,3,3);

    w.WriteArray<Vector<3,float> >("vector",vec,3);
}

void test_ReadArray(IArchiveReader& r) {
    Vector<3,float> vec[3];
    r.ReadArray<Vector<3,float> >("vector",vec,3);

    OE_CHECK(vec[0][2] == 1);
    OE_CHECK(vec[1][2] == 2);
    OE_CHECK(vec[2][2] == 3);
}

class Object {
public:
    int data;
    Object() : data(0) {}
    Object(int data) : data(data) {}
    void Deserialize(IArchiveReader& r) {
        data = r.ReadInt("data");
    }
    void Serialize(IArchiveWriter& w) {
        w.WriteInt("data", data);
    }

};
/*
void test_WriteObject(IArchiveWriter& w) {
    Object *o1 = new Object(1);
    Object *o2 = new Object(2);

    w.WriteObject("o1",o1);
    w.WriteObject("o2",o2);
    w.WriteObject("o3",o1);
    w.WriteObject("o4",o2);
}

void test_ReadObject(IArchiveReader& r) {
    Object* o1 = r.ReadObject<Object>("o1");
    Object* o2 = r.ReadObject<Object>("o2");

    Object* o3 = r.ReadObject<Object>("o3");
    Object* o4 = r.ReadObject<Object>("o4");

    OE_CHECK(o1->data == 1);
    OE_CHECK(o2->data == 2);

    OE_CHECK(o1 == o3);
    OE_CHECK(o2 == o4);
}


void test_WriteObjectPtr(IArchiveWriter& w) {
    shared_ptr<Object> o1 = shared_ptr<Object>(new Object(1));
    shared_ptr<Object> o2 = shared_ptr<Object>(new Object(2));


    

    w.WriteObjectPtr("o1",o1);
    w.WriteObjectPtr("o2",o2);
    w.WriteObjectPtr("o3",o1);
    w.WriteObjectPtr("o4",o2);
}

void test_ReadObjectPtr(IArchiveReader& r) {
    shared_ptr<Object> o1 = r.ReadObjectPtr<Object>("o1");
    shared_ptr<Object> o2 = r.ReadObjectPtr<Object>("o2");

    shared_ptr<Object> o3 = r.ReadObjectPtr<Object>("o3");
    shared_ptr<Object> o4 = r.ReadObjectPtr<Object>("o4");

    OE_CHECK(o1->data == 1);
    OE_CHECK(o2->data == 2);

    OE_CHECK(o1 == o3);
    OE_CHECK(o2 == o4);

    OE_CHECK(o1.use_count() == 3); // +1 for the archiver ;)
    OE_CHECK(o2.use_count() == 3);
}
*/

int test_main(int argc, char* argv[]) {

    stringstream ss (stringstream::in | stringstream::out);

    
    // StreamArchiveWriter w = StreamArchiveWriter(ss);
    // StreamArchiveReader r = StreamArchiveReader(ss);
        
    BinaryStreamArchiveWriter w = BinaryStreamArchiveWriter(ss);
    BinaryStreamArchiveReader r = BinaryStreamArchiveReader(ss);
        
    test_primitives_write(w);
    test_Vector_write(w);
    test_collection_write(w);          
    test_Matrix_write(w);
    test_Quaternion_write(w);

    test_scene_write(w);
    
    test_WriteArray(w);


    // test_WriteObject(w);
    // test_WriteObjectPtr(w);

    cout << ss.str() << endl;
    
    test_primitives_read(r);
    test_Vector_read(r);
    test_collection_read(r);          
    test_Matrix_read(r);
    test_Quaternion_read(r);

    test_scene_read(r);

    test_ReadArray(r);


    // test_ReadObject(r);
    // test_ReadObjectPtr(r);

    //cout << ss.str() << endl;

    return 0;
}
