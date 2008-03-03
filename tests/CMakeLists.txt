IF(Boost_FOUND)

    SET(test_SOURCES
                   test_suite.cpp
                   GameTestFactory.cpp
                   # test files should be listed here
                   testExample.cpp
                   testMath.cpp
                   testGeometry.cpp
                   testGameEngine.cpp
                   testEventSystem.cpp
                   testDisplay.cpp
                   testDevices.cpp
                   testResources.cpp
		   testOBJModelResource.cpp
		   testScene.cpp
                   )

    IF(APPLE)
        SET(test_SOURCES ${test_SOURCES} ../conf/mac/SDLMain.m)
    ENDIF(APPLE)

    ADD_EXECUTABLE(testsuite
                   EXCLUDE_FROM_ALL
                   ${test_SOURCES})



    # depending libraries
    TARGET_LINK_LIBRARIES(testsuite
                          ${BOOST_TEST_LIB}
                          OpenEngine_Core
                          OpenEngine_Math
                          OpenEngine_Display
                          OpenEngine_EventSystem
                          OpenEngine_Geometry
                          OpenEngine_Devices
                          OpenEngine_Logging
                          OpenEngine_Renderers_OpenGL
                          OpenEngine_Resources
                          OpenEngine_Scene
                          OpenEngine_Utils
                          )

    # testing targets
    SET(test_executable ${OpenEngine_BINARY_DIR}/tests/testsuite)
        IF(WIN32)
    SET(test_executable ${OpenEngine_BINARY_DIR}/tests/debug/testsuite.exe)
        ENDIF(WIN32)
    ADD_CUSTOM_TARGET(test ${test_executable} DEPENDS testsuite WORKING_DIRECTORY ${OpenEngine_SOURCE_DIR})
    ADD_CUSTOM_TARGET(test-auto ${test_executable} auto DEPENDS testsuite WORKING_DIRECTORY ${OpenEngine_SOURCE_DIR})
    ADD_CUSTOM_TARGET(test-manual ${test_executable} manual DEPENDS testsuite WORKING_DIRECTORY ${OpenEngine_SOURCE_DIR})

ENDIF(Boost_FOUND)
