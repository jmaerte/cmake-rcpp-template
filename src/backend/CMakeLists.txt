CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(BACKEND CXX)

include(cmake/find_toolchain.cmake)

include_directories(
  ${CMAKE_SOURCE_DIR}/lib/OpenCL-Headers
  ${CMAKE_SOURCE_DIR}/lib/OpenCL-CLHPP/include
  ${OpenCL_INCLUDE_DIRS}
)
FIND_PACKAGE(OpenCL REQUIRED)


file(GLOB_RECURSE SOURCES "src/*.cpp")

ADD_LIBRARY(BACKEND SHARED ${SOURCES})

target_include_directories(BACKEND
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/internal
		${OpenCL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/lib/OpenCL-Headers
    ${CMAKE_SOURCE_DIR}/lib/OpenCL-CLHPP/include
)

target_link_libraries(BACKEND
  PRIVATE
    ${OpenCL_LIBRARIES}
    OpenCL::OpenCL
)

if(WIN32)
  SET_TARGET_PROPERTIES(BACKEND PROPERTIES
    OUTPUT_NAME "BACKEND"
    PREFIX ""
  )
endif()
