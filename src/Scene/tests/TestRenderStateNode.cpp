
#include <Testing/Testing.h>
#include <iostream>

#include <Scene/RenderStateNode.h>

using namespace OpenEngine::Scene;
using namespace std;

int test_main(int argc, char* argv[]) {

    RenderStateNode *current = new RenderStateNode();

    current->EnableOption(RenderStateNode::TEXTURE);
    current->EnableOption(RenderStateNode::SHADER);


    RenderStateNode* r1 = new RenderStateNode();
    r1->EnableOption(RenderStateNode::TEXTURE);
    r1->EnableOption(RenderStateNode::BACKFACE);

    RenderStateNode* difference = r1->GetDifference(*current);
    // should be only lighing
    cout << "Options: " <<difference->GetEnabled() << endl;

    OE_CHECK(true == difference->IsOptionEnabled(RenderStateNode::BACKFACE));
    OE_CHECK(false == difference->IsOptionEnabled(RenderStateNode::SHADER));
    OE_CHECK(false == difference->IsOptionEnabled(RenderStateNode::TEXTURE));
    

    return 0;
}

