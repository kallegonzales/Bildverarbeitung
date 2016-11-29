## Build applications for exercise 1

ADD_EXECUTABLE(HelloWorld HelloWorld.cpp)

ADD_EXECUTABLE(TestImage TestImage.cpp)
TARGET_LINK_LIBRARIES(TestImage Graphics2D)
