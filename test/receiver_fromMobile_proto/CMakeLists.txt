# cmake_minimum_required(VERSION 3.10)

## use pkg-config support 
find_package(PkgConfig)                 # load in pkg-config support
pkg_check_modules(PC_ZeroMQ QUIET zmq)  # use pkg-config to get hints for 0mq locations

## use zmq library
find_path(ZeroMQ_INCLUDE_DIR            # use the hint from above to find where 'zmq.hpp' is located
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
)
find_library(ZeroMQ_LIBRARY             # use the hint from about to find the location of libzmq
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
)


## use thread
find_package( Threads )

##use opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 

## use mscl
find_library(MSCL_LIB_PATH NAMES libmscl.so PATHS "/usr/share/c++-mscl" DOC "MSCL Library" NO_DEFAULT_PATH)
find_library(BOOST_LIB_PATH NAMES libboost_chrono.so PATHS "/usr/share/c++-mscl/Boost/lib" NO_DEFAULT_PATH)
set(MSCL_INC_PATH "/usr/share/c++-mscl/source")
set(BOOST_INC_PATH "/usr/share/c++-mscl/Boost/include")
set(MSCL_LIB "/usr/share/c++-mscl")
add_definitions(-std=c++11)
include_directories(/usr/share/c++-mscl/source /usr/share/c++-mscl/Boost/include /usr/include)
link_directories(/usr/share/c++-mscl)
link_libraries(mscl pthread GL GLU glut GLEW glfw X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor m)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)





# PROJECT (cppTest)
SET(CLIENT_SRC_LIST main.cpp sensors.pb.cc GpsReceiverThread.cpp)



# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()


include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS sensors.proto)

# ADD_EXECUTABLE(receiverFromMobile ${CLIENT_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS}  ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC} ${OpenCV_INCLUDE_DIRS})
add_executable(receiverFromMobile ${CLIENT_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS}  ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC} ${OpenCV_INCLUDE_DIRS})

target_include_directories(receiverFromMobile PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(receiverFromMobile ${PROTOBUF_LIBRARIES} ${ZeroMQ_LIBRARY} ${OpenCV_LIBS}
        /usr/share/c++-mscl/libmscl.so) 
