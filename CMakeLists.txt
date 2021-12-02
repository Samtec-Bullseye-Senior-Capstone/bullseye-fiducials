cmake_minimum_required(VERSION 2.8)

project(bullseye-fiducials)

#####################################
# START from chilitags CMakeLists
#####################################
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

add_definitions(-std=c++11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV version: ${OpenCV_VERSION}")

if(UNIX)
    option(WITH_PTHREADS                "Multithreading support with pthreads" ON)
    option(WITH_TOOLS                   "provides the marker generation tool" ON)
else()
    option(WITH_PTHREADS                "Multithreading support with pthreads" OFF)
    option(WITH_TOOLS                   "provides the marker generation tool" ON)
endif()
if(WITH_PTHREADS)
    add_definitions(-DHAS_MULTITHREADING)
endif()

if(WITH_INVERTED_TAGS)
    add_definitions(-DHAS_INVERTED_TAGS)
endif()

if(${OpenCV_VERSION} VERSION_GREATER 2.9.0)
    add_definitions(-DOPENCV3)
endif()

# include chilitags src
include_directories(chilitags/include)
add_subdirectory(chilitags/src)

#####################################
# END from chilitags CMakeLists
#####################################

# add bullseye executable
add_executable( bullseye-fiducials src/bullseye-fiducials.cpp )
target_link_libraries( bullseye-fiducials chilitags_static )
target_link_libraries( bullseye-fiducials ${OpenCV_LIBS} )