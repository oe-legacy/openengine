IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")

  # TODO: only msdev supports the CMAKE_CXX_WARNING_LEVEL, others rely on CXX flags
  # set C++/C compilation warning level 
  # 4 = highest(pedantic)
  SET(CMAKE_CXX_WARNING_LEVEL 3 CACHE STRING "compiler warning level for CPP" FORCE)
  SET(CMAKE_C_WARNING_LEVEL 3 CACHE STRING "compiler warning level for C" FORCE)
  MARK_AS_ADVANCED(CMAKE_CXX_WARNING_LEVEL CMAKE_C_WARNING_LEVEL)

  # disable warnings that are too pedantic (for us actually)
  # 4305 : cast from double to float posible loss of precision
  # 4996 : deprecated sscanf -> use sscanf_s
  SET(FLAGS_WARN_OFF "/wd4244 /wd4305 /wd4996")
  SET(CMAKE_CXX_FLAGS_DEBUG
      "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS_WARN_OFF}"
      CACHE STRING "Debug builds CMAKE CXX flags " FORCE)

  SET(CMAKE_CXX_FLAGS_RELEASE
      "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS_WARN_OFF}"
      CACHE STRING "Release builds CMAKE CXX flags " FORCE)
      
  # /NODEFAULTLIB:msvcrt.lib : warning LNK4098: defaultlib 'msvcrt.lib' conflicts with use of other libs; use /NODEFAULTLIB:library
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /fixed:no /INCREMENTAL:NO")
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:\"msvcrt.lib\"")
  SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:\"msvcrtd.lib\"")

  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOE_SAFE=${OE_SAFE}")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOE_DEBUG_GL=${OE_DEBUG_GL}")

ENDIF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")    
