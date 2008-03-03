INCLUDE(${CMAKE_CONF_DIR}/FindBoost.cmake)
IF (Boost_FOUND) 

    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

    # look for boost filesystem lib
    FIND_FILE(BOOST_FILESYSTEM_FOUND "filesystem/operations.hpp" ${Boost_INCLUDE_DIRS}/boost)

    IF(NOT BOOST_FILESYSTEM_FOUND)
       MESSAGE("WARNING: Could not find boost filesystem library - depending targets will be disabled.")
       SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, boost-filesystem")
    ENDIF(NOT BOOST_FILESYSTEM_FOUND)

    SET (BOOST_FILESYSTEM_LIB "boost_filesystem")
    SET (BOOST_TEST_LIB       "boost_unit_test_framework")
    SET (BOOST_SERIALIZATION_LIB "boost_serialization")

    IF (WIN32)
	SET(Boost_LIBRARY_DIRS ${Boost_INCLUDE_DIRS}/lib)
	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

	# look for the test lib binary file 
    FIND_FILE(BOOST_TEST_LIB_FILE "libboost_unit_test_framework-vc80-mt-gd-1_33_1.lib" ${Boost_LIBRARY_DIRS})
	IF (BOOST_TEST_LIB_FILE)
		SET (BOOST_TEST_LIB ${BOOST_TEST_LIB_FILE})
	ENDIF (BOOST_TEST_LIB_FILE)
    FIND_FILE(BOOST_TEST_LIB_FILE "libboost_unit_test_framework-vc80-mt-gd-1_34_1.lib" ${Boost_LIBRARY_DIRS})
	IF (BOOST_TEST_LIB_FILE)
		SET (BOOST_TEST_LIB ${BOOST_TEST_LIB_FILE})
	ENDIF (BOOST_TEST_LIB_FILE)

	# look for the filesystem lib binary file 
    FIND_FILE(BOOST_FILESYSTEM_LIB_FILE "libboost_filesystem-vc80-mt-gd-1_33_1.lib" ${Boost_LIBRARY_DIRS})
	IF (BOOST_FILESYSTEM_LIB_FILE)
		SET (BOOST_FILESYSTEM_LIB ${BOOST_FILESYSTEM_LIB_FILE})
	ENDIF (BOOST_FILESYSTEM_LIB_FILE)
    FIND_FILE(BOOST_FILESYSTEM_LIB_FILE "libboost_filesystem-vc80-mt-gd-1_34_1.lib" ${Boost_LIBRARY_DIRS})
	IF (BOOST_FILESYSTEM_LIB_FILE)
		SET (BOOST_FILESYSTEM_LIB ${BOOST_FILESYSTEM_LIB_FILE})
	ENDIF (BOOST_FILESYSTEM_LIB_FILE)

	IF (NOT BOOST_TEST_LIB_FILE AND NOT BOOST_FILESYSTEM_LIB_FILE)
		SET(Boost_FOUND 0)
	ENDIF(NOT BOOST_TEST_LIB_FILE AND NOT BOOST_FILESYSTEM_LIB_FILE)

    ENDIF (WIN32)

ENDIF (Boost_FOUND)

IF (NOT Boost_FOUND)
  MESSAGE ("WARNING: Could not find Boost - depending targets will be disabled.")
  SET(OE_MISSING_LIBS "${OE_MISSING_LIBS}, boost")
ENDIF (NOT Boost_FOUND)
