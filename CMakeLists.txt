CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# set linking method to support 2.4
IF(COMMAND cmake_policy)
    CMAKE_POLICY(SET CMP0003 OLD)
ENDIF(COMMAND cmake_policy)


PROJECT(OpenEngine)

SET(CMAKE_BUILD_TYPE debug)

SET(CMAKE_VERBOSE_MAKEFILE 0)

SET (OE_BUILD_TESTS false)

ENABLE_TESTING()

# Define OpenEngine special directories
SET(OE_SOURCE_DIR     "${OpenEngine_SOURCE_DIR}/src")
SET(OE_BUILD_DIR      "${OpenEngine_SOURCE_DIR}/build")
SET(OE_CONF_DIR       "${OpenEngine_SOURCE_DIR}/conf")
SET(OE_LIB_DIR        "${OpenEngine_SOURCE_DIR}/libraries")
#SET(OE_TESTS_DIR      "${OpenEngine_SOURCE_DIR}/tests")
SET(OE_PROJECTS_DIR   "${OpenEngine_SOURCE_DIR}/projects")
SET(OE_EXTENSIONS_DIR "${OpenEngine_SOURCE_DIR}/extensions")
SET(OE_EXTERNALS_DIR "${OpenEngine_SOURCE_DIR}/dependencies")

# Include paths
INCLUDE_DIRECTORIES(
  ${OE_SOURCE_DIR}
)

# Sub directories
SUBDIRS(
  ${OE_SOURCE_DIR}
#  ${OE_TESTS_DIR}
)

# Include configuration files
SET(CMAKE_CONF_DIR ${OE_CONF_DIR}/cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupDebug.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupGCC.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupVS.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupDoxygen.cmake)

IF(MINGW)
	INCLUDE(${CMAKE_CONF_DIR}/FindPthread.cmake)
	INCLUDE(${CMAKE_CONF_DIR}/FindBoost.cmake)
ELSE(MINGW)
	INCLUDE(${CMAKE_CONF_DIR}/SetupBoost.cmake)
ENDIF(MINGW)

INCLUDE(${CMAKE_CONF_DIR}/SetupExternals.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupExtensionsAndProjects.cmake)

# some debug info
IF(OE_DEBUG_CMAKE)
  MESSAGE("CXX Flags: ${CMAKE_CXX_FLAGS}")
ENDIF(OE_DEBUG_CMAKE)

# If the missing libs is set exit the build process
IF(OE_MISSING_LIBS)
  MESSAGE(FATAL_ERROR "The following libraries are required but missing${OE_MISSING_LIBS}.")
ENDIF(OE_MISSING_LIBS)
