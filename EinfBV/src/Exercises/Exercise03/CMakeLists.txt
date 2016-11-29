## Build applications for exercise 3

ADD_EXECUTABLE(TestPrimitives TestPrimitives.cpp)
TARGET_LINK_LIBRARIES(TestPrimitives Graphics2D)

ADD_EXECUTABLE(TestAffineTransform TestAffineTransform.cpp)
TARGET_LINK_LIBRARIES(TestAffineTransform Graphics2D)
