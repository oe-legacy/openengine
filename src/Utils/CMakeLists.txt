ADD_LIBRARY(OpenEngine_Utils
  Utils.cpp
  Limits.h
  Limits.cpp
  Timer.h
  Timer.cpp
  Convert.h
  Convert.cpp
  DateTime.cpp
  Statistics.h
  Statistics.cpp
  Serialization.h
  EventProfiler.h
  EventProfiler.cpp
  SelectionSet.h
)

SUBDIRS(tests)