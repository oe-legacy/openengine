ADD_LIBRARY(OpenEngine_Utils
	    Timer.cpp
	    Convert.cpp
	    Statistics.cpp
	    )

TARGET_LINK_LIBRARIES(OpenEngine_Utils
		      OpenEngine_Devices)