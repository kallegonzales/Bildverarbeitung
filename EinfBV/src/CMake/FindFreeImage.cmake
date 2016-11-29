## Find FreeImage library and include directories

IF(FreeImage_LIBRARIES AND FreeImage_INCLUDE_DIRS)
  SET(FreeImage_FIND_QUIETLY TRUE)
ELSE()
  MESSAGE(STATUS "Looking for FreeImage")
ENDIF()

SET(FreeImage_INCLUDE_SEARCH_DIRS
  ${FreeImage_LIBRARY_SEARCH_DIRS}
  ${CMAKE_LIBRARY_PATH}
  /usr/include
  /usr/local/include
  /opt/include
  /opt/freeimage/include
  ../lib/freeimage
)

SET(FreeImage_LIBRARY_SEARCH_DIRS
  ${FreeImage_LIBRARY_SEARCH_DIRS}
  ${CMAKE_LIBRARY_PATH}
  /usr/lib64
  /usr/local/lib64
  /usr/lib
  /usr/local/lib
  /opt/lib
  /opt/freeimage/lib
  ../lib/freeimage
)

FIND_PATH(FreeImage_INCLUDE_DIRS FreeImage.h
  ${FreeImage_INCLUDE_SEARCH_DIRS})

FIND_LIBRARY(FreeImage_LIBRARIES freeimage PATHS
  ${FreeImage_LIBRARY_SEARCH_DIRS})

SEPARATE_ARGUMENTS(FreeImage_INCLUDE_DIRS)
SEPARATE_ARGUMENTS(FreeImage_LIBRARIES)

#MARK_AS_ADVANCED(FreeImage_INCLUDE_DIRS FreeImage_LIBRARIES FreeImage_LIBRARY_DIRS)

IF(FreeImage_INCLUDE_DIRS AND FreeImage_LIBRARIES)
  SET(FreeImage_FOUND TRUE)
ENDIF()
IF(FreeImage_FOUND)
  IF(NOT FreeImage_FIND_QUIETLY)
    MESSAGE(STATUS "FreeImage libraries : ${FreeImage_LIBRARIES}")
    MESSAGE(STATUS "FreeImage includes  : ${FreeImage_INCLUDE_DIRS}")
  ENDIF()
ELSE()
  IF(FreeImage_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find FreeImage!")
  ENDIF()
ENDIF()
