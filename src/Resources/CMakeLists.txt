IF(BOOST_FILESYSTEM_FOUND)

  ADD_LIBRARY(OpenEngine_Resources
	      File.cpp
	      DirectoryManager.cpp
	      )

  TARGET_LINK_LIBRARIES(OpenEngine_Resources
			OpenEngine_Utils
			${BOOST_FILESYSTEM_LIB})

ENDIF(BOOST_FILESYSTEM_FOUND)
