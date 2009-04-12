ADD_EXECUTABLE        (SearchTool SearchTool.cpp)
TARGET_LINK_LIBRARIES (SearchTool OpenEngine_Scene)
ADD_TEST              (SearchTool SearchTool)

ADD_EXECUTABLE        (PropertyNode PropertyNode.cpp)
TARGET_LINK_LIBRARIES (PropertyNode OpenEngine_Scene)
ADD_TEST              (PropertyNode PropertyNode)

ADD_EXECUTABLE        (TestVisitorStrategies TestVisitorStrategies.cpp)
TARGET_LINK_LIBRARIES (TestVisitorStrategies OpenEngine_Scene)
ADD_TEST              (TestVisitorStrategies TestVisitorStrategies)
