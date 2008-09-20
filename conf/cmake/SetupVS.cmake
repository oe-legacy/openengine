IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")

  # only msdev supports the CMAKE_CXX_WARNING_LEVEL, others rely on CXX flags
  # set C++/C compilation warning level, 4 = highest(pedantic)
  SET(CMAKE_CXX_WARNING_LEVEL 3 CACHE STRING "compiler warning level for CPP" FORCE)
  SET(CMAKE_C_WARNING_LEVEL 3 CACHE STRING "compiler warning level for C" FORCE)
  MARK_AS_ADVANCED(CMAKE_CXX_WARNING_LEVEL CMAKE_C_WARNING_LEVEL)

  # disable warnings that are too pedantic (for us actually)
  # 4305 : cast from double to float posible loss of precision
  # 4996 : deprecated sscanf -> use sscanf_s
  SET(FLAGS_WARN_OFF "/wd4244 /wd4305 /wd4996")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_WARN_OFF}")

  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /fixed:no /INCREMENTAL:NO")

  # visual studie compile only takes integer values!
  IF(OE_SAFE)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOE_SAFE=1")
  ELSEIF(NOT OE_SAFE)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOE_SAFE=0")
  ENDIF(OE_SAFE)

  # visual studie compile only takes integer values!
  IF(OE_DEBUG_GL)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOE_DEBUG_GL=1")
  ELSEIF(NOT OE_DEBUG_GL)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOE_DEBUG_GL=0")
  ENDIF(OE_DEBUG_GL)

ENDIF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")    
