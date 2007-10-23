# documentation with doxygen 
INCLUDE(${CMAKE_ROOT}/Modules/FindDoxygen.cmake)
IF(DOXYGEN_FOUND)
  SET(DX_GENERATE_HTML YES)
  SET(DX_DOCDIR ${OpenEngine_BINARY_DIR}/doc)
  CONFIGURE_FILE(${OpenEngine_SOURCE_DIR}/conf/doxygen/doxygen.cfg
                 ${OpenEngine_BINARY_DIR}/Doxyfile
                 @ONLY)
  ADD_CUSTOM_TARGET(doc "${DOXYGEN_EXECUTABLE}")
ELSE (DOXYGEN_FOUND)
  MESSAGE ("WARNING: Could not find Doxygen - depending targets will be disabled.")
ENDIF(DOXYGEN_FOUND)
