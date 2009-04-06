SET(CMAKE_INCLUDE_PATH ${OE_LIB_DIR}/boost)
FIND_PACKAGE(Boost)
IF (Boost_FOUND) 

   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
   # Debug mode libraries
   IF(CMAKE_BUILD_TYPE MATCHES debug)
     FIND_LIBRARY(BOOST_FILESYSTEM_LIB NAMES
                  boost_filesystem
                  boost_filesystem-mt
                  libboost_filesystem-vc80-mt-gd-1_33_1
                  libboost_filesystem-vc80-mt-gd-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
     FIND_LIBRARY(BOOST_SERIALIZATION_LIB NAMES
                  boost_serialization
                  boost_serialization-mt
                  libboost_serialization-vc80-mt-gd-1_33_1
                  libboost_serialization-vc80-mt-gd-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
    # Boost 1.37, boost::system is required
    FIND_LIBRARY(BOOST_SYSTEM_LIB NAMES
                 boost_system
                 boost_system-mt
                 )
    IF (BOOST_SYSTEM_LIB)
    SET(BOOST_SERIALIZATION_LIB ${BOOST_SERIALIZATION_LIB} ${BOOST_SYSTEM_LIB})
    ENDIF (BOOST_SYSTEM_LIB)

   # Release mode libraries
   ELSE(CMAKE_BUILD_TYPE MATCHES debug)
     FIND_LIBRARY(BOOST_FILESYSTEM_LIB NAMES
                  boost_filesystem
                  boost_filesystem-mt
                  libboost_filesystem-vc80-mt-1_33_1
                  libboost_filesystem-vc80-mt-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
     FIND_LIBRARY(BOOST_SERIALIZATION_LIB NAMES
                  boost_serialization
                  boost_serialization-mt
                  libboost_serialization-vc80-mt-1_33_1
                  libboost_serialization-vc80-mt-1_34_1
                  PATHS
                  ${Boost_INCLUDE_DIRS}
                  ${Boost_INCLUDE_DIRS}/lib
                  )
    # Boost 1.37, boost::system is required
    FIND_LIBRARY(BOOST_SYSTEM_LIB NAMES
                 boost_system
                 boost_system-mt
                 )
    IF (BOOST_SYSTEM_LIB)
    SET(BOOST_SERIALIZATION_LIB ${BOOST_SERIALIZATION_LIB} ${BOOST_SYSTEM_LIB})
    ENDIF (BOOST_SYSTEM_LIB)


   ENDIF(CMAKE_BUILD_TYPE MATCHES debug)

   IF(NOT BOOST_FILESYSTEM_LIB OR NOT BOOST_SERIALIZATION_LIB)
      SET(Boost_FOUND 0)
   ENDIF(NOT BOOST_FILESYSTEM_LIB OR NOT BOOST_SERIALIZATION_LIB)

ENDIF (Boost_FOUND)

IF (NOT Boost_FOUND)
MESSAGE ("WARNING: Could not find Boost - depending targets will be disabled.")
SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, boost")
ENDIF (NOT Boost_FOUND)
