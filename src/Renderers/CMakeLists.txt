ADD_LIBRARY(OpenEngine_Renderers
  Renderers.cpp
  IRenderer.h
  IBufferedRenderer.h
  IRenderingView.h
  TextureLoader.h
  TextureLoader.cpp
  BufferObjectBinder.h
  BufferObjectBinder.cpp
)

TARGET_LINK_LIBRARIES(OpenEngine_Renderers
  OpenEngine_Core
  OpenEngine_Geometry
  OpenEngine_Resources
  OpenEngine_Scene
)
