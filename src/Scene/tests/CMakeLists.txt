ADD_EXECUTABLE        (SearchTool SearchTool.cpp)
TARGET_LINK_LIBRARIES (SearchTool OpenEngine_Scene)
ADD_TEST              (SearchTool SearchTool)

ADD_EXECUTABLE        (PropertyNode PropertyNode.cpp)
TARGET_LINK_LIBRARIES (PropertyNode OpenEngine_Scene)
ADD_TEST              (PropertyNode PropertyNode)
