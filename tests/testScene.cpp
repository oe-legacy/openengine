// Test of scene capabilities.
// -------------------------------------------------------------------
// Copyright (C) 2007 daimi.au.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>

// include test header
#include "testScene.h"

#include <Scene/SceneNode.h>
#include <Scene/Exceptions.h>

#include <iostream>

using namespace OpenEngine::Scene;

class Node : public SceneNode {
public:
    int id;
    Node(int id) : id(id) { }
    ISceneNode* CloneSelf() {
        return new Node(id+10);
    }
};

void OpenEngine::Tests::testSceneAdd() {
    // test adding nodes to multiple places
    ISceneNode* node0 = new Node(0);
    ISceneNode* node1 = new Node(1);
    ISceneNode* node2 = new Node(2);
    node0->AddNode(node2);
    try { node1->AddNode(node2); BOOST_CHECK(false); }
    catch (InvalidSceneOperation &e) { }
}

void OpenEngine::Tests::testSceneDelete() {

    /*
    // build a tree
    //     0
    //    / \
    //   1   4
    //  / \ 
    // 2   3
    */

    ISceneNode* node0 = new Node(0);
    ISceneNode* node1 = new Node(1);
    ISceneNode* node2 = new Node(2);
    ISceneNode* node3 = new Node(3);
    ISceneNode* node4 = new Node(4);
    node0->AddNode(node1);
    node0->AddNode(node4);
    node1->AddNode(node2);
    node1->AddNode(node3);

    class Visit : public ISceneNodeVisitor {
    public:
        bool first;
        int i;
        int visited[10];
        Visit() : first(true), i(0) {}
        void VisitSceneNode(SceneNode* sn) {
            Node* node = (Node*)sn;
            visited[i++] = node->id;
            if (node->id == 1 && first) {
                first = false;
                // crawl up the tree and start a new visit traversal
                node->GetParent()->DeleteNode(node);
                node->GetParent()->Accept(*this);
            } else {
                node->VisitSubNodes(*this);
            }
        }
    };

    Visit v;
    node0->Accept(v);
    BOOST_CHECK( v.visited[0] == 0 ); // out
    BOOST_CHECK( v.visited[1] == 1 ); // out - we mark 1 for removal
    BOOST_CHECK( v.visited[2] == 0 ); // in
    BOOST_CHECK( v.visited[3] == 1 ); // in
    BOOST_CHECK( v.visited[4] == 2 ); // in
    BOOST_CHECK( v.visited[5] == 3 ); // in
    BOOST_CHECK( v.visited[6] == 4 ); // in
    BOOST_CHECK( v.visited[7] == 4 ); // out - completes and 1 is removed
    BOOST_CHECK( v.i == 8 ); // we visited only 8 nodes under traversal

    // @todo:
    // node 1, 2 and 3 should not exist any more... can we test this?
    // BOOST_CHECK( node1,2,3->GetParent() == free memory? );
    
    // test that we can remove nodes without traversing
    node0->DeleteNode(node4);
    BOOST_CHECK( node0->subNodes.size() == 0 );

    delete node0;
}

void OpenEngine::Tests::testSceneClone() {
    
    /*
    // build a tree
    //
    //     0    cloned   10   
    //    / \    ===>   /  \  
    //   1   4         11   14 
    //  / \           /  \    
    // 2   3         12  13   
    */

    ISceneNode* node0 = new Node(0);
    ISceneNode* node1 = new Node(1);
    ISceneNode* node2 = new Node(2);
    ISceneNode* node3 = new Node(3);
    ISceneNode* node4 = new Node(4);
    node0->AddNode(node1);
    node0->AddNode(node4);
    node1->AddNode(node2);
    node1->AddNode(node3);
    
    class Visit : public ISceneNodeVisitor {
    public:
        int i;
        int visited[10];
        Visit() : i(0) {}
        void VisitSceneNode(SceneNode* sn) {
            Node* node = (Node*)sn;
            visited[i++] = node->id;
            // check that cloned children have a parent
            if (node->id != 10)
                BOOST_CHECK(node->GetParent() != NULL);
            node->VisitSubNodes(*this);
        }
    };

    ISceneNode* copy0 = node0->Clone();
    Visit v;
    copy0->Accept(v);
    
    BOOST_CHECK( v.visited[0] == 10 );
    BOOST_CHECK( v.visited[1] == 11 );
    BOOST_CHECK( v.visited[2] == 12 );
    BOOST_CHECK( v.visited[3] == 13 );
    BOOST_CHECK( v.visited[4] == 14 );
    BOOST_CHECK( v.i == 5 );
}

void OpenEngine::Tests::testSceneReplace() {

    /*
    // build trees
    //
    //     0     5    7
    //    / \    |
    //   1   4   6
    //  / \ 
    // 2   3
    */

    ISceneNode* node0 = new Node(0);
    ISceneNode* node1 = new Node(1);
    ISceneNode* node2 = new Node(2);
    ISceneNode* node3 = new Node(3);
    ISceneNode* node4 = new Node(4);
    ISceneNode* node5 = new Node(5);
    ISceneNode* node6 = new Node(6);
    ISceneNode* node7 = new Node(7);
    node0->AddNode(node1);
    node0->AddNode(node4);
    node1->AddNode(node2);
    node1->AddNode(node3);
    node5->AddNode(node6);

    class Visit : public ISceneNodeVisitor {
    public:
        int i;
        int visited[10];
        ISceneNode* replace;
        Visit(ISceneNode* replace) : i(0), replace(replace) {}
        void VisitSceneNode(SceneNode* sn) {
            Node* node = (Node*)sn;
            visited[i++] = node->id;
            if (node->id == 1) {
                node->GetParent()->ReplaceNode(node, replace);
                node->GetParent()->VisitSubNodes(*this);
            } else {
                node->VisitSubNodes(*this);
            }
        }
    };

    Visit v(node5);
    node0->Accept(v);
    BOOST_CHECK( v.visited[0] == 0 );
    BOOST_CHECK( v.visited[1] == 1 ); // replace tree
    BOOST_CHECK( v.visited[2] == 5 );
    BOOST_CHECK( v.visited[3] == 6 );
    BOOST_CHECK( v.visited[4] == 4 );
    BOOST_CHECK( v.visited[5] == 4 ); // replace deletion performed
    BOOST_CHECK( v.i == 6 ); // we visited only 6 nodes under traversal

    // test that replace works outside a traversal
    node5->ReplaceNode(node6, node7);
    if (node7 != *(node5->subNodes.begin()))
        BOOST_CHECK(false);
}

void OpenEngine::Tests::testSceneRemove() {

    /*
    // build a tree
    //     0
    //    / \
    //   1   4
    //  / \ 
    // 2   3
    */

    ISceneNode* node0 = new Node(0);
    ISceneNode* node1 = new Node(1);
    ISceneNode* node2 = new Node(2);
    ISceneNode* node3 = new Node(3);
    ISceneNode* node4 = new Node(4);
    node0->AddNode(node1);
    node0->AddNode(node4);
    node1->AddNode(node2);
    node1->AddNode(node3);

    class Visit : public ISceneNodeVisitor {
    public:
        bool first;
        int i;
        int visited[10];
        Visit() : first(true), i(0) {}
        void VisitSceneNode(SceneNode* sn) {
            Node* node = (Node*)sn;
            visited[i++] = node->id;
            if (node->id == 1 && first) {
                    first = false;
                    // crawl up the tree and start a new visit traversal
                    node->GetParent()->RemoveNode(node);
                    node->GetParent()->Accept(*this);
            } else {
                node->VisitSubNodes(*this);
            }
        }
    };

    Visit v;
    node0->Accept(v);
    BOOST_CHECK( v.visited[0] == 0 ); // out
    BOOST_CHECK( v.visited[1] == 1 ); // out - we mark 1 for removal
    BOOST_CHECK( v.visited[2] == 0 ); // in
    BOOST_CHECK( v.visited[3] == 1 ); // in
    BOOST_CHECK( v.visited[4] == 2 ); // in
    BOOST_CHECK( v.visited[5] == 3 ); // in
    BOOST_CHECK( v.visited[6] == 4 ); // in
    BOOST_CHECK( v.visited[7] == 4 ); // out - completes and 1 is removed
    BOOST_CHECK( v.i == 8 ); // we visited only 8 nodes under traversal
    // node1 should not have a parent anymore
    BOOST_CHECK( node1->GetParent() == NULL );
    
    // test that we can remove nodes without traversing
    node0->RemoveNode(node4);
    BOOST_CHECK( node0->subNodes.size() == 0 );
    BOOST_CHECK( node4->GetParent() == NULL );

    // clean up
    delete node0;

    // check for a different traversal
    class Visit2 : public ISceneNodeVisitor {
    public:
        bool first;
        int i;
        int visited[10];
        Visit2() : first(true), i(0) {}
        void VisitSceneNode(SceneNode* sn) {
            Node* node = (Node*)sn;
            visited[i++] = node->id;
            if (node->id == 1) {
                if (first) {
                    first = false;
                    // crawl up the tree and start a new visit traversal
                    node->GetParent()->Accept(*this);
                } else {
                    node->GetParent()->RemoveNode(node);                    
                }
            } else {
                node->VisitSubNodes(*this);
            }
        }
    };
    
    node0 = new Node(0);
    node1 = new Node(1);
    node2 = new Node(2);
    node3 = new Node(3);
    node4 = new Node(4);
    node0->AddNode(node1);
    node0->AddNode(node4);
    node1->AddNode(node2);
    node1->AddNode(node3);

    Visit2 v2;
    node0->Accept(v2);
    BOOST_CHECK( v2.visited[0] == 0 ); // out
    BOOST_CHECK( v2.visited[1] == 1 ); // out 
    BOOST_CHECK( v2.visited[2] == 0 ); // in
    BOOST_CHECK( v2.visited[3] == 1 ); // in  - we mark 1 for removal
    BOOST_CHECK( v2.visited[4] == 4 ); // in  - completes and 1 is removed
    BOOST_CHECK( v2.visited[5] == 4 ); // out 
    BOOST_CHECK( v2.i == 6 ); // we visited only 6 nodes under traversal
    // node1 should not have a parent anymore
    BOOST_CHECK( node1->GetParent() == NULL );

    // clean up
    delete node0;
    delete node1;
}
