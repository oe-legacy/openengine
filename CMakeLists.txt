PROJECT(OpenEngine)

SET(OE_DEBUG_CMAKE false)

SET(CMAKE_BUILD_TYPE debug)

SET(CMAKE_VERBOSE_MAKEFILE 0)

# Define OpenEngine special directories
SET(OE_SOURCE_DIR     "${OpenEngine_SOURCE_DIR}/src")
SET(OE_BUILD_DIR      "${OpenEngine_SOURCE_DIR}/build")
SET(OE_CONF_DIR       "${OpenEngine_SOURCE_DIR}/conf")
SET(OE_TESTS_DIR      "${OpenEngine_SOURCE_DIR}/tests")
SET(OE_PROJECTS_DIR   "${OpenEngine_SOURCE_DIR}/projects")
SET(OE_EXTENSIONS_DIR "${OpenEngine_SOURCE_DIR}/extensions")

# Include paths
INCLUDE_DIRECTORIES(
  ${OE_SOURCE_DIR}
)

# Sub directories
SUBDIRS(
  ${OE_SOURCE_DIR}
  ${OE_TESTS_DIR}
)

# Include configuration files
SET(CMAKE_CONF_DIR ${OE_CONF_DIR}/cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupGCC.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupVS.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupBoost.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupOpenGL.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupSDL.cmake)
INCLUDE(${CMAKE_CONF_DIR}/SetupDoxygen.cmake)

INCLUDE(${CMAKE_CONF_DIR}/SetupExtensionsAndProjects.cmake)

# If the missing libs is set exit the build process
IF(OE_MISSING_LIBS)
  MESSAGE(FATAL_ERROR "The following libraries are required but missing${OE_MISSING_LIBS}.")
ENDIF(OE_MISSING_LIBS)
