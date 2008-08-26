ADD_LIBRARY(OpenEngine_Renderers
  Renderers.cpp
  IRenderer.h
  IRenderingView.h
  IRenderNode.h
  RenderStateNode.h
  RenderStateNode.cpp
  TextureLoader.h
  TextureLoader.cpp
)

TARGET_LINK_LIBRARIES(OpenEngine_Renderers
  OpenEngine_Scene
)
