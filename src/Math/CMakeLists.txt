ADD_LIBRARY(OpenEngine_Math
  Math.h
  Math.cpp
  Exceptions.h
  Exceptions.cpp
  Matrix.h
  Quaternion.h
  RandomGenerator.h
  RandomGenerator.cpp
  Vector.h
#  VectorList.h
#  VectorIterator.h
  Tensor.h
  Color.h
  HSLColor.h
  HSLColor.cpp
  RGBColor.h
  RGBColor.cpp   
  RGBAColor.h
  RGBAColor.cpp   
)

TARGET_LINK_LIBRARIES(OpenEngine_Math
  OpenEngine_Core
  OpenEngine_Utils
)

IF(OE_BUILD_TESTS)
  SUBDIRS(tests)
ENDIF(OE_BUILD_TESTS)

