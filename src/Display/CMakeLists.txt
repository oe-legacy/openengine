ADD_LIBRARY(OpenEngine_Display
	    SDLFrame.cpp
	    Viewport.cpp
	    ViewingVolume.cpp
	    Camera.cpp
	    Frustum.cpp
	    FollowCamera.cpp
	    InterpolatedViewingVolume.cpp
	    )

TARGET_LINK_LIBRARIES(OpenEngine_Display
                      OpenEngine_Core
                      OpenEngine_Math
                      ${SDL_LIBRARY})