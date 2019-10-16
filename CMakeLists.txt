cmake_minimum_required(VERSION 3.1)
project(vslab CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(CAF COMPONENTS core io)

if (NOT CAF_FOUND AND NOT CAF_ROOT_DIR)
  message(STATUS "CAF not installed, try finding it in parent directory")
  set(CAF_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../actor-framework/build")
  find_package(CAF COMPONENTS core io REQUIRED)
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
target_link_libraries(vslab ${CMAKE_DL_LIBS} ${CAF_LIBRARIES})
