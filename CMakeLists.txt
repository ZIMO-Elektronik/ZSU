cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY "https://github.com/ZIMO-Elektronik/CMakeModules"
  GIT_TAG v0.9.3
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

if(PROJECT_IS_TOP_LEVEL)
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

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
  add_subdirectory(examples)
  file(
    DOWNLOAD
    "https://github.com/ZIMO-Elektronik/.github/raw/master/data/.clang-format"
    ${CMAKE_CURRENT_LIST_DIR}/.clang-format)
  file(GLOB_RECURSE SRC examples/*.[ch]pp include/*.[ch]pp src/*.[ch]pp
       tests/*.[ch]pp)
  add_clang_format_target(ZSUFormat OPTIONS -i FILES ${SRC})
endif()

if(BUILD_TESTING
   AND PROJECT_IS_TOP_LEVEL
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(tests)
endif()
