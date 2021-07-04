# cmake_minimum_required(VERSION 3.10)

## use pkg-config support 
find_package(PkgConfig)                 # load in pkg-config support
# pkg_check_modules(PC_ZeroMQ QUIET zmq)  # use pkg-config to get hints for 0mq locations

## use thread
find_package( Threads )

## Use json
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

# ADD_EXECUTABLE(storingraw ${CLIENT_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS}  )
SET(CLIENT_SRC_LIST main.cpp readfiles.cpp indexandtimes.cpp makejson.cpp makejsonThread.cpp)
add_executable(timesynchronization ${CLIENT_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS}  )

target_include_directories(timesynchronization PUBLIC)  # add the include directory to our compile directives
target_link_libraries(timesynchronization) 