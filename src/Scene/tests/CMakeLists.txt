ADD_EXECUTABLE        (SearchTool SearchTool.cpp)
TARGET_LINK_LIBRARIES (SearchTool
  OpenEngine_Scene
  # How do we fix this?
  Extensions_AccelerationStructures
  Extensions_OpenGLRenderer
)
ADD_TEST              (SearchTool SearchTool)
