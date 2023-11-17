cmake_minimum_required(VERSION 3.13.5...3.18 FATAL_ERROR)
project(vslab CXX)

include(GNUInstallDirs)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT CAF_ROOT)
  FetchContent_Declare(
    actor_framework
    GIT_REPOSITORY https://github.com/actor-framework/actor-framework.git
    GIT_TAG        3fa129d
  )
  FetchContent_Populate(actor_framework)
  set(CAF_ENABLE_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(CAF_ENABLE_IO_MODULE ON CACHE BOOL "" FORCE)
  set(CAF_ENABLE_NET_MODULE OFF CACHE BOOL "" FORCE)
  set(CAF_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
  set(CAF_ENABLE_TOOLS OFF CACHE BOOL "" FORCE)
  set(CAF_ENABLE_OPENSSL_MODULE OFF CACHE BOOL "" FORCE)
  set(CAF_SANITIZERS "${CAF_INC_SANITIZERS}" CACHE STRING "" FORCE)
  add_subdirectory(${actor_framework_SOURCE_DIR} ${actor_framework_BINARY_DIR})
else()
  find_package(CAF COMPONENTS core io test REQUIRED)
  message(STATUS "Found CAF version ${CAF_VERSION}: ${CAF_DIR}")
endif()

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH
# from qmake)
include_directories(. include  ${CMAKE_CURRENT_SOURCE_DIR}/third_party ${CAF_INCLUDE_DIRS})

set(SOURCES
    src/int512_serialization.cpp
    src/main.cpp)

file(GLOB HEADERS "include/*.hpp")

add_executable(vslab ${SOURCES} ${HEADERS})
target_link_libraries(vslab ${CMAKE_DL_LIBS} CAF::core CAF::io)

# Disable deprecation warnings (for GCC or clang)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(vslab PRIVATE -Wno-deprecated-declarations)
endif()

# Disable deprecation warnings (for MSVC)
if(MSVC)
    target_compile_definitions(vslab PRIVATE /wd4996)
    # target_compile_definitions(vslab PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
