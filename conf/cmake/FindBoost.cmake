# - Try to find Boost
# Once done this will define
#
#  Boost_FOUND - system has Boost
#  Boost_INCLUDE_DIR - the Boost include directory
#  Boost_LIBRARIES - Link these to use Boost
#

FIND_PATH(Boost_INCLUDE_DIR NAMES boost/cstdint.hpp
  PATHS
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/libraries/Boost/include
  NO_DEFAULT_PATH
)

FIND_LIBRARY(Boost_LIBRARY NAMES
  boost_filesystem
  PATHS
  ${PROJECT_BINARY_DIR}/lib
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/libraries/Boost/lib
  NO_DEFAULT_PATH
)

IF(Boost_INCLUDE_DIR AND Boost_LIBRARY)
   SET(Boost_FOUND TRUE)
ENDIF(Boost_INCLUDE_DIR AND Boost_LIBRARY)

# show the Boost_INCLUDE_DIR and Boost_LIBRARIES variables only in the advanced view
IF(Boost_FOUND)
  MARK_AS_ADVANCED(Boost_INCLUDE_DIR Boost_LIBRARIES)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ELSE (Boost_FOUND)
	MESSAGE ("WARNING: Could not find Boost - depending targets will be disabled.")
  SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, Boost")
ENDIF(Boost_FOUND)
