#include <Testing/Testing.h>

#include <Scene/SearchTool.h>
#include <Scene/SceneNode.h>
#include <Scene/PropertyNode.h>

using namespace std;
using namespace OpenEngine;
using namespace OpenEngine::Scene;

int test_main(int argc, char* argv[]) {

    // Create a search tool
    SearchTool tool;

    // Build a scene. The tree:
    //           s1
    //         /  | \.
    //       p1  r1  p4
    //            |
    //           p2
    //            |
    //           r2
    //          /  \.
    //         p3  r3
    SceneNode*    s1 = new SceneNode();
    PropertyNode* p1 = new PropertyNode();
    PropertyNode* p2 = new PropertyNode();
    PropertyNode* p3 = new PropertyNode();
    PropertyNode* p4 = new PropertyNode();
    SceneNode*    r1 = new SceneNode();
    SceneNode*    r2 = new SceneNode();
    SceneNode*    r3 = new SceneNode();
    p1->SetProperty("id", "1");
    p2->SetProperty("id", "2");
    p3->SetProperty("id", "3");
    p4->SetProperty("id", "4");
    s1->AddNode(p1); s1->AddNode(r1); s1->AddNode(p4);
    r1->AddNode(p2);
    p2->AddNode(r2);
    r2->AddNode(p3); r2->AddNode(r3);

    // Result vars
    SceneNode* rnode;
    list<SceneNode*> rnodes;

    // Get first r child of s1 (r1)
    rnode = tool.ChildSceneNode(s1);
    OE_CHECK(r1 == rnode);

    // Get first r child of r1 (NULL)
    rnode = tool.ChildSceneNode(r1);
    OE_CHECK(rnode == NULL);

    // Get all r children of r2 (r3)
    rnodes = tool.ChildSceneNodes(r2);
    OE_CHECK(rnodes.size() == 1);
    OE_CHECK(r3 == rnodes.front());

    // Get first descendant r of r1 (r2)
    rnode = tool.DescendantSceneNode(r1);
    OE_CHECK(r2 == rnode);

    // Get all descendants r of r1 (r2 & r3)
    rnodes = tool.DescendantSceneNodes(r1);
    OE_CHECK(rnodes.size() == 2);
    OE_CHECK(r2 == rnodes.front());
    OE_CHECK(r3 == rnodes.back());

    // Get first r ancestor of r2 (r1)
    rnode = tool.AncestorSceneNode(r2);
    OE_CHECK(rnode == r1);

    // Get all r ancestors of r2 (r1 & s1)
    rnodes = tool.AncestorSceneNodes(r2);
    OE_CHECK(rnodes.size() == 2);
    OE_CHECK(r1 == rnodes.front());
    OE_CHECK(s1 == rnodes.back());

    // Chains with NULL as intermediate results
    rnode  = tool.ChildSceneNode(NULL);       OE_CHECK(rnode == NULL);
    rnode  = tool.DescendantSceneNode(NULL);  OE_CHECK(rnode == NULL);
    rnode  = tool.AncestorSceneNode(NULL);    OE_CHECK(rnode == NULL);
    rnodes = tool.ChildSceneNodes(NULL);      OE_CHECK(rnodes.size() == 0);
    rnodes = tool.DescendantSceneNodes(NULL); OE_CHECK(rnodes.size() == 0);
    rnodes = tool.AncestorSceneNodes(NULL);   OE_CHECK(rnodes.size() == 0);

    // Chains with empty lists as intermediate results
    // We need to do something about casting list<SomeNode*> to list<ISceneNode*>
    // for this to work...
    // rnode = tool.DescendantSceneNode(list<SceneNode*>());
    // OE_CHECK(rnode == NULL);
    // rnodes = tool.DescendantSceneNodes(list<SceneNode*>());
    // OE_CHECK(rnodes.size() == 0);

    // Testing of property nodes
    OE_CHECK(p2 == tool.DescendantPropertyNodeWith("id", "2", s1));
    OE_CHECK(r2 == tool.ChildSceneNode(tool.DescendantPropertyNodeWith("id", "2", s1)));
    OE_CHECK(p1 == tool.ChildPropertyNodeWith("id", "1", s1));
    OE_CHECK(p4 == tool.ChildPropertyNodeWith("id", "4", s1));
    OE_CHECK(p2 == tool.AncestorPropertyNodeWith("id","2",p3));

    return 0;
}
