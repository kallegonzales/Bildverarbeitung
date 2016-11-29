OPTION(USE_OPENGL "Build with OpenGL" ON)
IF(USE_OPENGL)
  IF(WIN32)
    SET(OPENGL_INCLUDE_DIR ""
        CACHE PATH "Include directory for OpenGL headers")
    SET(OPENGL_LIB "opengl32.lib"
        CACHE FILEPATH "Location of OpenGL library")
    SET(GLUT_INCLUDE_DIR ""
        CACHE PATH "Include directory for GLUT headers")
    SET(GLUT_LIB "glut32.lib"
        CACHE FILEPATH "Location of GLUT library")
  ELSE()
    SET(OPENGL_INCLUDE_DIR /usr/include
        CACHE PATH "Include directory for OpenGL headers")
    SET(OPENGL_LIB /usr/lib/x86_64-linux-gnu/libGL.so
        #/usr/lib/nvidia-340-updates/libGL.so
        CACHE FILEPATH "Location of OpenGL library")
    SET(GLUT_INCLUDE_DIR /usr/include
        CACHE PATH "Include directory for GLUT headers")
    SET(GLUT_LIB /usr/lib/x86_64-linux-gnu/libglut.so
        CACHE FILEPATH "Location of GLUT library")
  ENDIF()
  ADD_DEFINITIONS(-DBUILD_WITH_OPENGL)
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
  SET(OPENGL_LIBRARIES ${OPENGL_LIB} ${GLUT_LIB})
ENDIF()
