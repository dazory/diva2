### diva2/test/zmq

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

# 실행파일 만들기
set(SOURCE_SENSOR_PARSING gps_parsing.cpp)
add_executable(sensor_parsing ${SOURCE_SENSOR_PARSING})                           # 생성할 실행파일 이름 지정
target_include_directories(sensor_parsing PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(sensor_parsing PUBLIC ${ZeroMQ_LIBRARY} pthread)           # at the 0mq library to our link directive

