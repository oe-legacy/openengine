ADD_LIBRARY(OpenEngine_Math
  Math.h
  Math.cpp
  Exceptions.h
  Exceptions.cpp
  Matrix.h
  Quaternion.h
  Vector.h
)

TARGET_LINK_LIBRARIES(OpenEngine_Math
  OpenEngine_Core
  OpenEngine_Utils
)
