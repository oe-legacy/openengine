# - Try to find pThread
# Once done this will define
#
#  PTHREAD_FOUND - system has pThread
#  PTHREAD_INCLUDE_DIR - the pThread include directory
#  PTHREAD_LIBRARIES - Link these to use pThread
#

FIND_PATH(PTHREAD_INCLUDE_DIR NAMES pthread.h
  PATHS
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/libraries/pthread/include
  NO_DEFAULT_PATH
)

FIND_LIBRARY(PTHREAD_LIBRARY NAMES
  pthreadGC2
  PATHS
  ${PROJECT_BINARY_DIR}/lib
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/libraries/pthread/lib
  NO_DEFAULT_PATH
)

IF(PTHREAD_INCLUDE_DIR AND PTHREAD_LIBRARY)
   SET(PTHREAD_FOUND TRUE)
ENDIF(PTHREAD_INCLUDE_DIR AND PTHREAD_LIBRARY)

# show the GLEW_INCLUDE_DIR and GLEW_LIBRARIES variables only in the advanced view
IF(PTHREAD_FOUND)
  MARK_AS_ADVANCED(PTHREAD_INCLUDE_DIR PTHREAD_LIBRARIES)
  INCLUDE_DIRECTORIES(${PTHREAD_INCLUDE_DIR})
ELSE (PTHREAD_FOUND)
	MESSAGE ("WARNING: Could not find pThread - depending targets will be disabled.")
  SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, pThread")
ENDIF(PTHREAD_FOUND)
