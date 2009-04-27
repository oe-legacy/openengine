ADD_LIBRARY(OpenEngine_Utils
  Utils.cpp
  Limits.h
  Limits.cpp
  Timer.h
  Timer.cpp
  Convert.h
  Convert.cpp
  Statistics.h
  Statistics.cpp
  Serialization.h
  EventProfiler.h
  EventProfiler.cpp
  SelectionList.h
)

SUBDIRS(tests)