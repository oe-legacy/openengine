
ADD_LIBRARY(OpenEngine_Scene
  SceneNode.cpp
  ISceneNodeVisitor.cpp
  GeometryNode.cpp
  CollectedGeometryTransformer.cpp
  TransformationNode.cpp
  DotVisitor.cpp
  LightNode.cpp
  DirectionalLightNode.cpp
  PointLightNode.cpp
)

TARGET_LINK_LIBRARIES(OpenEngine_Scene)
