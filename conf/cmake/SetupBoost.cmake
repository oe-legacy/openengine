SET(CMAKE_INCLUDE_PATH ${OE_LIB_DIR}/boost)
FIND_PACKAGE(Boost)
IF (Boost_FOUND) 

   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

   # Debug mode libraries
   IF(CMAKE_CXX_FLAGS_DEBUG)
     FIND_LIBRARY(BOOST_FILESYSTEM_LIB NAMES
                  boost_filesystem
                  libboost_filesystem-vc80-mt-gd-1_33_1
                  libboost_filesystem-vc80-mt-gd-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
     FIND_LIBRARY(BOOST_SERIALIZATION_LIB NAMES
                  boost_serialization
                  libboost_serialization-vc80-mt-gd-1_33_1
                  libboost_serialization-vc80-mt-gd-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )

   # Release mode libraries
   ELSE(CMAKE_CXX_FLAGS_DEBUG)
     FIND_LIBRARY(BOOST_FILESYSTEM_LIB NAMES
                  boost_filesystem
                  libboost_filesystem-vc80-mt-1_33_1
                  libboost_filesystem-vc80-mt-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
     FIND_LIBRARY(BOOST_SERIALIZATION_LIB NAMES
                  boost_serialization
                  libboost_serialization-vc80-mt-1_33_1
                  libboost_serialization-vc80-mt-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
   ENDIF(CMAKE_CXX_FLAGS_DEBUG)

   IF(NOT BOOST_FILESYSTEM_LIB OR NOT BOOST_SERIALIZATION_LIB)
      SET(Boost_FOUND 0)
   ENDIF(NOT BOOST_FILESYSTEM_LIB OR NOT BOOST_SERIALIZATION_LIB)

ENDIF (Boost_FOUND)

IF (NOT Boost_FOUND)
MESSAGE ("WARNING: Could not find Boost - depending targets will be disabled.")
SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, boost")
ENDIF (NOT Boost_FOUND)
