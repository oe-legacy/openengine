IF(CMAKE_COMPILER_IS_GNUCXX)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wno-unused-parameter")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpeel-loops") # for OSX
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOE_SAFE=${OE_SAFE}")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOE_DEBUG_GL=${OE_DEBUG_GL}")
  IF (CMAKE_BUILD_TYPE MATCHES debug)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG")
  ENDIF (CMAKE_BUILD_TYPE MATCHES debug)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
