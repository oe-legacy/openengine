#include <Testing/Testing.h>

#include <Scene/PropertyNode.h>
#include <Core/Exceptions.h>

using namespace std;
using namespace OpenEngine;
using namespace OpenEngine::Scene;

int test_main(int argc, char* argv[]) {

    // creating
    PropertyNode p1, p2, p3;
    p1.SetProperty("id", 42);
    p2.SetProperty("name", "p2");
    p3.SetProperty("length", 1.5); // double is cast to a float

    // testing for (non) existence
    OE_CHECK( p1.HasProperty("id"));
    OE_CHECK(!p2.HasProperty("id"));
    OE_CHECK( p1.GetProperty("id").IsSome() );
    OE_CHECK( p2.GetProperty("id").IsNone() );

    // testing for equality
    OE_CHECK( p1.GetProperty("id").Match(42) ); 
    OE_CHECK(!p1.GetProperty("id").Match("42") );
    OE_CHECK( p2.GetProperty("name").Match("p2") ); 
    OE_CHECK( p3.GetProperty("length").Match(1.5) );

    // type conversions
    OE_CHECK( "42" == p1.GetProperty("id").AsString() );
    OE_CHECK( "1.5" == p3.GetProperty("length").AsString() );
    OE_CHECK_THROW( p2.GetProperty("name").AsInt(), Core::Exception );
    OE_CHECK_THROW( p1.GetProperty("name").AsString(), Core::Exception );

    return 0;
}
