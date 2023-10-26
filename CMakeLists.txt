cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_TAG v0.2.2
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

version_from_git()
project(
  ZSU
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES CXX)

file(GLOB_RECURSE SRC src/*.cpp)
add_library(ZSU STATIC ${SRC})
add_library(ZSU::ZSU ALIAS ZSU)

target_compile_features(ZSU PUBLIC cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(
    ZSU
    INTERFACE include
    PRIVATE include/zsu)
else()
  target_include_directories(
    ZSU SYSTEM
    INTERFACE include
    PRIVATE include/zsu)
endif()

target_common_warnings(ZSU PRIVATE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(BUILD_TESTING
   AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(examples)
  add_subdirectory(tests)
endif()
