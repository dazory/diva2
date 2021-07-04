# cmake_minimum_required(VERSION 3.10)

## use pkg-config support 
find_package(PkgConfig)                 # load in pkg-config support
pkg_check_modules(PC_ZeroMQ QUIET zmq)  # use pkg-config to get hints for 0mq locations

## use thread
find_package( Threads )

## Use json
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

## use libpqxx
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

# ADD_EXECUTABLE(storingraw ${CLIENT_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS}  )
SET(CLIENT_SRC_LIST main.cpp LogStoringThread.cpp FrameStoringThread.cpp SceneStoringThread.cpp LidarStoringThread.cpp CamStoringThread.cpp GpsStoringThread.cpp ImuStoringThread.cpp CanStoringThread.cpp)
add_executable(dbstoring ${CLIENT_SRC_LIST})

target_include_directories(dbstoring PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(dbstoring ${PQXX_LIB} ${PQ_LIB}) 