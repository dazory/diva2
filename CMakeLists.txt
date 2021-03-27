### diva2/test/zmq
#참고: https://www.kudryavka.me/?p=758

cmake_minimum_required(VERSION 3.8)     #cmake 최소 버전 요구 사양
project(diva2 VERSION 1.0.0)            #프로젝트명 버전
set(CMAKE_CXX_STANDARD 11)              # use this to globally use C++11 with in our project

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
set(SOURCE_FILES main.cpp)
add_executable(diva2 ${SOURCE_FILES})                           # 생성할 실행파일 이름 지정
target_include_directories(diva2 PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(diva2 PUBLIC ${ZeroMQ_LIBRARY})           # at the 0mq library to our link directive

# 서브 디렉토리에 있는 cmakeFiles을 실행시켜줌
add_subdirectory(test/zmq)
