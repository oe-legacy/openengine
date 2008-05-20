ADD_LIBRARY(OpenEngine_Display
	    Viewport.cpp
	    ViewingVolume.cpp
	    Camera.cpp
	    Frustum.cpp
	    Orthotope.cpp
	    FollowCamera.cpp
	    InterpolatedViewingVolume.cpp
	    )

TARGET_LINK_LIBRARIES(OpenEngine_Display
                      OpenEngine_Core
                      OpenEngine_Math)
