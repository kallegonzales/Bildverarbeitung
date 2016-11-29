## Build applications for exercise 4

IF(USE_OPENGL)
  ADD_EXECUTABLE(DrawCanvasGui DrawCanvasGui.cpp)
  TARGET_LINK_LIBRARIES(DrawCanvasGui Graphics2D)
ENDIF()
