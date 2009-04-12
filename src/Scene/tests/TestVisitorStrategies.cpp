#include <Testing/Testing.h>

#include <Scene/StrategyVisitor.h>
#include <Scene/SceneNode.h>
#include <Scene/TransformationNode.h>

using namespace OpenEngine::Scene;

int test_main(int argc, char* argv[]) {

    // Create a strategy to handle visiting of type SceneNode
    class OnSceneNode
        : public StrategyVisitor::Strategy<SceneNode> {
    public:
        int* test;
        ISceneNodeVisitor& visit;

        OnSceneNode(int* test, ISceneNodeVisitor& visit)
            : test(test), visit(visit) {}

        void Visit(SceneNode* node) {
            // inc test on each scene node we visit
            (*test)++;
            node->VisitSubNodes(visit);
        }
    };

    // Create a scene
    SceneNode* s1 = new SceneNode();
    SceneNode* s2 = new SceneNode();
    TransformationNode* t1 = new TransformationNode();
    TransformationNode* t2 = new TransformationNode();
    s1->AddNode(t1);
    t1->AddNode(s2);
    s2->AddNode(t2);

    // Create a visitor with a single strategy
    int test = 0;
    StrategyVisitor visit;
    visit.SetSceneNodeStrategy(new OnSceneNode(&test, visit));

    // test that visiting hits two scene nodes
    OE_CHECK(test == 0);
    s1->Accept(visit);
    OE_CHECK(test == 2);

    // Cleanup
    delete s1;
    return 0;
}
