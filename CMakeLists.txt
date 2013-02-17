if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

project(esmodel)
cmake_minimum_required(VERSION 2.8)

find_path(CVD_INCLUDE_DIRS NAMES cvd/image_ref.h DOC "libcvd header files")
find_library(CVD_LIBRARIES NAMES cvd  DOC "libcvd library")
include_directories(${CVD_INCLUDE_DIRS})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries (${PROJECT_NAME} ${CVD_LIBRARIES})
