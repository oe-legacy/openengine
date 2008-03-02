// Test Obj loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>
#include "testDisplay.h"

#include <Core/GameEngine.h>
#include <Core/IModule.h>
#include <Resources/IModelResource.h>
#include <Resources/ResourceManager.h>
#include <Geometry/FaceSet.h>
#include "GameTestFactory.h"
#include <Logging/Logger.h>

// include display system
#include <Display/IFrame.h>


namespace OpenEngine {
namespace Tests {

using namespace std;
using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Resources;
using OpenEngine::Geometry::FaceSet;
using OpenEngine::Geometry::FaceList;
using OpenEngine::Geometry::FacePtr;

float faceArray[] = {
    -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5,
    -0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5,
    -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 0.5,
    -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5,
    0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5,
    -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5
};

float normArray[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 1,
    0, 0, 1, 0, 0, 1, 0, 0, 1,
    0, 1, 0, 0, 1, 0, 0, 1, 0,
    0, 1, 0, 0, 1, 0, 0, 1, 0,
    0, 0, -1, 0, 0, -1, 0, 0, -1,
    0, 0, -1, 0, 0, -1, 0, 0, -1,
    0, -1, 0, 0, -1, 0, 0, -1, 0,
    0, -1, 0, 0, -1, 0, 0, -1, 0,
    1, 0, 0, 1, 0, 0, 1, 0, 0,
    1, 0, 0, 1, 0, 0, 1, 0, 0,
    -1, 0, 0, -1, 0, 0, -1, 0, 0,
    -1, 0, 0, -1, 0, 0, -1, 0, 0,
};


float texcArray[] = {
    0.375, 0, 0.625, 0,0.375, 0.25,
    0.375, 0.25, 0.625, 0,0.625, 0.25,
    0.375, 0.25, 0.625, 0.25,0.375, 0.5,
    0.375, 0.5, 0.625, 0.25,0.625, 0.5,
    0.375, 0.5, 0.625, 0.5,0.375, 0.75,
    0.375, 0.75, 0.625, 0.5,0.625, 0.75,
    0.375, 0.75, 0.625, 0.75,0.375, 1,
    0.375, 1, 0.625, 0.75,0.625, 1,
    0.625, 0, 0.875, 0,0.625, 0.25,
    0.625, 0.25, 0.875, 0,0.875, 0.25,
    0.125, 0, 0.375, 0,0.125, 0.25,
    0.125, 0.25, 0.375, 0,0.375, 0.25,
};

float colrArray[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

float hardNormArray[] = {
    0, 0, 1,
    -0, 0, 1,
    -0, 1, 0,
    0, 1, 0,
    0, 0, -1,
    0, 0, -1,
    0, -1, 0,
    0, -1, 0,
    1, -0, 0,
    1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
};

void testOBJModelResource() {

    // module to test frame after engine start
    class TestModule : public IModule {
        IGameEngine& engine;
    public:
        TestModule(IGameEngine& engine) : engine(engine) {}
        void Initialize() {}

        void Process(const float dt, const float p) {
            // Set the path to our resources
            ResourceManager::AppendPath("tests/");

            // Pointer to model resource.
            IModelResourcePtr mod_res;
            mod_res = ResourceManager::CreateModel("box.obj");
            mod_res->Load();
    
            // Get a pointer to the loaded face set.
            FaceSet* fset = mod_res->GetFaceSet(); 
            // Test if the loader has created a face set.
            BOOST_CHECK(fset != NULL);
            // Test of the number of faces is right
            BOOST_CHECK(fset->Size() == 12);

            // Check all faces.
            int fc = 0;
            int faceCount = 0;
            FaceList::iterator itr = fset->begin();
            for( ; itr!=fset->end(); itr++ ){
                FacePtr f = *itr; faceCount++;
                Vector<3,float> v0(faceArray[fc],faceArray[fc+1],faceArray[fc+2]);  fc += 3;
                Vector<3,float> v1(faceArray[fc],faceArray[fc+1],faceArray[fc+2]);  fc += 3;
                Vector<3,float> v2(faceArray[fc],faceArray[fc+1],faceArray[fc+2]);  fc += 3;
                BOOST_CHECK( f->vert[0] == v0 && f->vert[1] == v1 && f->vert[2] == v2 );

                // Check that face number 6 has no material
                if (faceCount == 8)
                    BOOST_CHECK(f->texr == NULL);

                // Check that face number 9 has a material assigned
                if (faceCount == 9)
                    BOOST_CHECK(f->texr != NULL);
            }

            // Check all normals.
            fc = 0;
            for( itr = fset->begin(); itr!=fset->end(); itr++ ){
                FacePtr f = *itr;
                Vector<3,float> n0(normArray[fc],normArray[fc+1],normArray[fc+2]); fc += 3;
                Vector<3,float> n1(normArray[fc],normArray[fc+1],normArray[fc+2]); fc += 3;
                Vector<3,float> n2(normArray[fc],normArray[fc+1],normArray[fc+2]); fc += 3;
                BOOST_CHECK( f->norm[0] == n0 && f->norm[1] == n1 && f->norm[2] == n2 );
            }

            // Check all texture coordinates.
            fc = 0;
            for( itr = fset->begin(); itr!=fset->end(); itr++ ){
                FacePtr f = *itr;
                Vector<2,float> t0(texcArray[fc],texcArray[fc+1]); fc += 2;
                Vector<2,float> t1(texcArray[fc],texcArray[fc+1]); fc += 2;
                Vector<2,float> t2(texcArray[fc],texcArray[fc+1]); fc += 2;
                BOOST_CHECK( f->texc[0] == t0 && f->texc[1] == t1 && f->texc[2] == t2 );
            }
       
            // Check all colors coordinates.
            fc = 0;
            for( itr = fset->begin(); itr!=fset->end(); itr++ ){
                FacePtr f = *itr;
                Vector<4,float> c0(colrArray[fc],colrArray[fc+1],colrArray[fc+2],colrArray[fc+3]); fc += 4;
                Vector<4,float> c1(colrArray[fc],colrArray[fc+1],colrArray[fc+2],colrArray[fc+3]); fc += 4;
                Vector<4,float> c2(colrArray[fc],colrArray[fc+1],colrArray[fc+2],colrArray[fc+3]); fc += 4;
                BOOST_CHECK( f->colr[0] == c0 && f->colr[1] == c1 && f->colr[2] == c2 );
            }

            // Check all colors coordinates.
            fc = 0;
            for( itr = fset->begin(); itr!=fset->end(); itr++ ){
                FacePtr f = *itr;
                Vector<3,float> hard(hardNormArray[fc],hardNormArray[fc+1],hardNormArray[fc+2]); fc += 3;
                BOOST_CHECK( f->hardNorm == hard );
            }

            GameEngine::Instance().Stop();
            
        }
        void Deinitialize() {}
        bool IsTypeOf(const type_info& inf) { return false; }
 
    };
    // Create and start engine
    IGameEngine& engine = GameEngine::Instance();
    TestModule mod(engine);
    engine.AddModule(mod);
    engine.Start(GetTestFactory());

}

} // NS Tests
} // NS OpenEngine
