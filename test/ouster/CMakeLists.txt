# # References
# # - https://github.com/linux-can/can-utils/

# cmake_minimum_required(VERSION 3.3)

# ## use pkg-config support 
# find_package(PkgConfig)                 # load in pkg-config support
# pkg_check_modules(PC_ZeroMQ QUIET zmq)  # use pkg-config to get hints for 0mq locations

# ## use zmq library
# find_path(ZeroMQ_INCLUDE_DIR            # use the hint from above to find where 'zmq.hpp' is located
#         NAMES zmq.hpp
#         PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
# )
# find_library(ZeroMQ_LIBRARY             # use the hint from about to find the location of libzmq
#         NAMES zmq
#         PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
# )

# ## use thread
# find_package( Threads )

# ## SocketCAN
# # find_library(CANUTILS_LIB_PATH NAMES libmscl.so PATHS "/home/diva2/develop/can-utils-2020.12.0" DOC "CAN-utils Library" NO_DEFAULT_PATH)
# # set(CANUTILS_INC_PATH "/home/diva2/develop/can-utils-2020.12.0/include")
# # add_definitions(-std=c++11)
# # include_directories(/home/diva2/develop/can-utils-2020.12.0 /home/diva2/develop/can-utils-2020.12.0/include)
# # link_directories(/home/diva2/develop/can-utils-2020.12.0)

# ## Use Protobuf
# find_package(Protobuf REQUIRED)
# if(PROTOBUF_FOUND)
#     message(STATUS "protobuf library found")
# else()
#     message(FATAL_ERROR "protobuf library is needed but cant be found")
# endif()

# include_directories(${PROTOBUF_INCLUDE_DIRS})
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "../protobuf/sensors.proto" )


# set(SOURCE_OUSTER main.cpp)
# add_executable(ouster ${SOURCE_OUSTER}
#     ${PROTO_SRCS} ${PROTO_HDRS}) # ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC} ${OpenCV_INCLUDE_DIRS})                           # 생성할 실행파일 이름 지정
# target_include_directories(ouster PUBLIC ${ZeroMQ_INCLUDE_DIR})
# target_link_libraries(ouster PUBLIC ${ZeroMQ_LIBRARY}
#     ${PROTOBUF_LIBRARIES}
# )