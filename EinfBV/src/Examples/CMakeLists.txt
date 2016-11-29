## Build examples for Image and ImageIO classes

ADD_EXECUTABLE(ExampleImageIO ExampleImageIO.cpp)
TARGET_LINK_LIBRARIES(ExampleImageIO Graphics2D)

## Build examples for Linear Algebra classes

ADD_EXECUTABLE(ExampleLinearAlgebra ExampleLinearAlgebra.cpp)
TARGET_LINK_LIBRARIES(ExampleLinearAlgebra Graphics2D)

## Build example for GuiBase class

IF(USE_OPENGL)
  ADD_EXECUTABLE(ExampleGui ExampleGui.cpp)
  TARGET_LINK_LIBRARIES(ExampleGui Graphics2D)
ENDIF()
