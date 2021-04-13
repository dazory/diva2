# cmake_minimum_required(VERSION 3.10)
# PROJECT (cppTest)
SET(SRC_LIST main.cpp)

# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(client)
add_subdirectory(server)