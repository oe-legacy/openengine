FIND_PACKAGE(Boost)
IF (Boost_FOUND) 

   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

   FIND_LIBRARY(BOOST_FILESYSTEM_LIB NAMES
               boost_filesystem
               libboost_filesystem-vc80-mt-1_33_1
               libboost_filesystem-vc80-mt-1_34_1
               PATHS
               ${Boost_INCLUDE_DIRS}
               ${Boost_INCLUDE_DIRS}/lib
               )
   IF (NOT BOOST_FILESYSTEM_LIB)
      SET(Boost_FOUND 0)
   ENDIF(NOT BOOST_FILESYSTEM_LIB)

   FIND_LIBRARY(BOOST_FILESYSTEM_LIB_gd NAMES
               boost_filesystem
               libboost_filesystem-vc80-mt-gd-1_33_1
               libboost_filesystem-vc80-mt-gd-1_34_1
               PATHS
               ${Boost_INCLUDE_DIRS}
               ${Boost_INCLUDE_DIRS}/lib
               )
   IF (NOT BOOST_FILESYSTEM_LIB_gd)
      SET(Boost_FOUND 0)
   ENDIF(NOT BOOST_FILESYSTEM_LIB_gd)

   FIND_LIBRARY(BOOST_TEST_LIB NAMES
               boost_unit_test_framework
               libboost_unit_test_framework-vc80-mt-1_33_1
               libboost_unit_test_framework-vc80-mt-1_34_1
               libboost_unit_test_framework-vc80-mt-gd-1_33_1
               libboost_unit_test_framework-vc80-mt-gd-1_34_1
               PATHS
               ${Boost_INCLUDE_DIRS}
               ${Boost_INCLUDE_DIRS}/lib
               )
   IF (NOT BOOST_TEST_LIB)
      SET(Boost_FOUND 0) 
   ENDIF(NOT BOOST_TEST_LIB)

   FIND_LIBRARY(BOOST_SERIALIZATION_LIB NAMES
               boost_serialization
               # WINDOWS
               libboost_serialization-vc80-mt-1_33_1
               libboost_serialization-vc80-mt-1_34_1
               libboost_serialization-vc80-mt-gd-1_33_1
               libboost_serialization-vc80-mt-gd-1_34_1
               PATHS
               ${Boost_INCLUDE_DIRS}
               ${Boost_INCLUDE_DIRS}/lib
               )
   IF (NOT BOOST_SERIALIZATION_LIB)
      SET(Boost_FOUND 0)
   ENDIF(NOT BOOST_SERIALIZATION_LIB)

ENDIF (Boost_FOUND)

IF (NOT Boost_FOUND)
MESSAGE ("WARNING: Could not find Boost - depending targets will be disabled.")
SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, boost")
ENDIF (NOT Boost_FOUND)
