cmake_minimum_required(VERSION 2.8)

project(bullseye-fiducials)

set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

add_definitions(-std=c++11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

add_subdirectory(chilitags)

# include chilitags src
include_directories(chilitags/include)

# add bullseye executable
add_executable( bullseye-fiducials src/bullseye-fiducials.cpp )
target_link_libraries( bullseye-fiducials chilitags_static )
target_link_libraries( bullseye-fiducials ${OpenCV_LIBS} )