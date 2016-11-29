# Add a "doc" build target with CMake and configure doxy.config.in to doxy.config.
# Target "doc" allows building the documentation with Doxygen on Windows and Linux.
#
# Note that all tools (doxygen, latex, dvips, makeindex, etc.) must be in the path.
#
# Options:
# NO_TARGET_DOC : Set to 1 to suppress "doc" target. Useful if you just want the
#                 Doxygen configuration file. Otherwise a "doc" target is added
#                 to the project that does not belong to the "all" target.
#
# Author: MIP, http://www.mip.informatik.uni-kiel.de

FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)

  # Set format for warnings
  IF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")
    SET(DOXY_WARN_FORMAT "\"$file($line) : $text \"")
  ELSE(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")
    SET(DOXY_WARN_FORMAT "\"$file:$line: $text \"")
  ENDIF(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv)")
  
  # Latex is needed by Doxygen to generate formulas
  FIND_PACKAGE(LATEX)
  IF(NOT LATEX_COMPILER)
    MESSAGE(STATUS "Latex compiler not found, but usually required by Doxygen.")
  ENDIF(NOT LATEX_COMPILER)
  IF(NOT MAKEINDEX_COMPILER)
    MESSAGE(STATUS "Makeindex command not found, but usually required by Doxygen.")
  ENDIF(NOT MAKEINDEX_COMPILER)
  IF(NOT DVIPS_CONVERTER)
    MESSAGE(STATUS "DVIPS command not found, but usually required by Doxygen.")
  ENDIF(NOT DVIPS_CONVERTER)
  
  # Create configuration file or use existing file
  IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in")
    MESSAGE(STATUS "Configured ${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in to ${CMAKE_CURRENT_BINARY_DIR}/doxy.config")
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in 
                   ${CMAKE_CURRENT_BINARY_DIR}/doxy.config
                   @ONLY )
    SET(DOXY_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/doxy.config")
  ELSE(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in")
    SET(DOXY_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config")
    IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config")
      MESSAGE(STATUS "Using existing ${CMAKE_CURRENT_SOURCE_DIR}/doxy.config instead of configuring from doxy.config.in")
    ELSE(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config")
      IF(EXISTS "${CMAKE_MODULE_PATH}/doxy.config.in")
        MESSAGE(STATUS "Configured ${CMAKE_CMAKE_MODULE_PATH}/doxy.config.in to ${CMAKE_CURRENT_BINARY_DIR}/doxy.config")
        CONFIGURE_FILE(${CMAKE_MODULE_PATH}/doxy.config.in 
                       ${CMAKE_CURRENT_BINARY_DIR}/doxy.config
                       @ONLY )
        SET(DOXY_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/doxy.config")
      ELSE (EXISTS "${CMAKE_MODULE_PATH}/doxy.config.in")
        MESSAGE(SEND_ERROR "File ${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in is needed (or doxy.config as fallback)!")
      ENDIF(EXISTS "${CMAKE_MODULE_PATH}/doxy.config.in")
    ENDIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config")
  ENDIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/doxy.config.in")
  
  # Add "doc" target
  IF(NOT NO_TARGET_DOC)
    ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN_EXECUTABLE} ${DOXY_CONFIG})
  ENDIF(NOT NO_TARGET_DOC)
  
ENDIF(DOXYGEN_FOUND)
