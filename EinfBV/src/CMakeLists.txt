# CMake file for image processing exercises
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(ImageProcessing)
SET(ImageProcessing_VERSION "0.5")

IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
  CMAKE_POLICY(SET CMP0005 NEW)
ENDIF()

# Locate custom CMake modules
SET(ImageProcessing_CMAKE_DIR "${ImageProcessing_SOURCE_DIR}/CMake")
SET(CMAKE_MODULE_PATH "${ImageProcessing_CMAKE_DIR}")

# Set output paths
SET(LIBRARY_OUTPUT_PATH "${ImageProcessing_BINARY_DIR}/lib/"
    CACHE PATH "Single output directory for all libraries")
SET(RUNTIME_OUTPUT_DIRECTORY "${ImageProcessing_BINARY_DIR}/bin/"
    CACHE PATH "Single output directory for all DLLs")
SET(EXECUTABLE_OUTPUT_PATH "${ImageProcessing_BINARY_DIR}/bin/"
    CACHE PATH "Single output directory for all executables")

# Set base include directories
INCLUDE_DIRECTORIES(${ImageProcessing_SOURCE_DIR}
                    ${ImageProcessing_BINARY_DIR})

# Set base library directories
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

# Fix some common problems in Visual Studio build
IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake|MSBuild)")
  ADD_DEFINITIONS(/W3 /wd4251 /wd4996 /wd4250 /wd4267)
  ADD_DEFINITIONS(-D_USE_MATH_DEFINES -DNOMINMAX)
ENDIF()

# Get rid of GTK warnings
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_BUILD_SETTING_CXX_FLAGS}")

# Set build type
SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type for project" FORCE)

# Create Doxygen target
OPTION(TARGET_DOC "Create doc target for Doxygen documentation?" OFF)
IF(TARGET_DOC)
  INCLUDE(${ImageProcessing_CMAKE_DIR}/TargetDoc.cmake OPTIONAL)
ENDIF()

# Include OpenGL
INCLUDE(${ImageProcessing_CMAKE_DIR}/IncludeOpenGL.cmake)

# Include FreeImage library
INCLUDE(${ImageProcessing_CMAKE_DIR}/IncludeFreeImage.cmake)

# Add subdirectories
ADD_SUBDIRECTORY(Graphics2D)

OPTION(BUILD_Examples "Build basic tools and examples" ON)
IF(BUILD_Examples)
  ADD_SUBDIRECTORY(Examples)
ENDIF()

OPTION(BUILD_Exercises "Build exercises" ON)
IF(BUILD_Exercises)
  ADD_SUBDIRECTORY(Exercises)
ENDIF()
