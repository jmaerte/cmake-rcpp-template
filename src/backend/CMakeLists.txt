CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(BACKEND CXX)

# Get the Rcpp minGW/gcc compilers in order to achieve highest degree of uniformity while users only have to install Rtools.
include(cmake/find_toolchain.cmake)

# Include the external library headers in the lib folder
include_directories(
  ${CMAKE_SOURCE_DIR}/lib/OpenCL-Headers
  ${CMAKE_SOURCE_DIR}/lib/OpenCL-CLHPP/include
  ${OpenCL_INCLUDE_DIRS}
)
# find your binaries here
FIND_PACKAGE(OpenCL REQUIRED)


# Make a shared library
file(GLOB_RECURSE SOURCES "src/*.cpp")
ADD_LIBRARY(BACKEND SHARED ${SOURCES})

# The header includes go here
# Leave the two /include and /src/internal ones in here; the rest can be altered.
target_include_directories(BACKEND
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/internal
		${OpenCL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/lib/OpenCL-Headers
    ${CMAKE_SOURCE_DIR}/lib/OpenCL-CLHPP/include
)

# Linkage against your binaries
target_link_libraries(BACKEND
  PRIVATE
    ${OpenCL_LIBRARIES}
    OpenCL::OpenCL
)

# some OS-specific library name conventions here; just leave as is as it would change the way Rcpp's Makefile needs to look.
if(WIN32)
  SET_TARGET_PROPERTIES(BACKEND PROPERTIES
    OUTPUT_NAME "BACKEND"
    PREFIX ""
  )
endif()
