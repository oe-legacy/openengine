# Find all sub directories in the dependencies directory
FILE(GLOB DEPS_SUB_DIRS RELATIVE
  ${OE_DEPS_DIR} "${OE_DEPS_DIR}/*")

# If any dependencies are found include them
FOREACH(DEPS_SUB_DIR ${DEPS_SUB_DIRS})
  SET(FULL_DEPS_SUB_DIR "${OE_DEPS_DIR}/${DEPS_SUB_DIR}")
  
  # Invoke setup file if present - this should reveal dependency search paths in global variables.
  # Variable naming scheme: "<DEP NAME>_DEPS_INCLUDE_DIR" and "<DEP NAME>_DEPS_LIB_DIR".
  SET(SETUP_FILE "${FULL_DEPS_SUB_DIR}/Setup.cmake")
  IF(EXISTS ${SETUP_FILE})
    SET(OE_CURRENT_DEPS_DIR "${FULL_DEPS_SUB_DIR}")
    SET(OE_CURRENT_DEPS_BUILD_DIR "${OE_DEPS_BUILD_DIR}/${DEPS_SUB_DIR}")
    INCLUDE(${SETUP_FILE})
    SET(OE_CURRENT_DEPS_DIR "")
  ENDIF(EXISTS ${SETUP_FILE})
  
  # Include the dependency if the DEPS flag is set
  IF(DEPS)
    IF(IS_DIRECTORY ${FULL_DEPS_SUB_DIR})
      SUBDIRS(${FULL_DEPS_SUB_DIR})
    ENDIF(IS_DIRECTORY ${FULL_DEPS_SUB_DIR})
  ENDIF(DEPS)
ENDFOREACH(DEPS_SUB_DIR)
