
ADD_LIBRARY(OpenEngine_Scene
  SceneNode.cpp
  ISceneNodeVisitor.cpp
  GeometryNode.cpp
  CollectedGeometryTransformer.cpp
  TransformationNode.cpp
  DotVisitor.cpp
)

TARGET_LINK_LIBRARIES(OpenEngine_Scene)
