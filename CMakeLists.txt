### diva2/test/zmq
#참고: https://www.kudryavka.me/?p=758

cmake_minimum_required(VERSION 3.8)     #cmake 최소 버전 요구 사양
project(diva2 VERSION 1.0.0)            #프로젝트명 버전
set(CMAKE_CXX_STANDARD 11)              # use this to globally use C++11 with in our project

## Use pkg-config support 
find_package(PkgConfig)                 # load in pkg-config support
pkg_check_modules(PC_ZeroMQ QUIET zmq)  # use pkg-config to get hints for 0mq locations

## Use zmq library
if(NOT PKG_CONFIG_FOUND)
    INCLUDE(FindPkgConfig)
endif()
PKG_CHECK_MODULES(PC_ZEROMQ "libzmq")
# find_path(ZeroMQ_INCLUDE_DIR            # use the hint from above to find where 'zmq.hpp' is located
#         NAMES zmq.hpp
#         PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
# )
# find_library(ZeroMQ_LIBRARY             # use the hint from about to find the location of libzmq
#         NAMES zmq
#         PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
# )
FIND_PATH(ZEROMQ_INCLUDE_DIRS
    NAMES zmq.hpp
    HINTS ${PC_ZEROMQ_INCLUDE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
    PATHS
    /usr/local/include
    /usr/include
)

FIND_LIBRARY(ZEROMQ_LIBRARIES
    NAMES zmq libzmq ${ZEROMQ_LIBRARY_NAME}
    HINTS ${PC_ZEROMQ_LIBDIR}
    ${CMAKE_INSTALL_PREFIX}/lib
    ${CMAKE_INSTALL_PREFIX}/lib64
    PATHS
    ${ZEROMQ_INCLUDE_DIRS}/../lib
    /usr/local/lib
    /usr/lib
)
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ZeroMQ DEFAULT_MSG ZEROMQ_LIBRARIES ZEROMQ_INCLUDE_DIRS)
MARK_AS_ADVANCED(ZEROMQ_LIBRARIES ZEROMQ_INCLUDE_DIRS)

if (ZEROMQ_FOUND AND NOT TARGET ZEROMQ::ZEROMQ)
  add_library(ZeroMQ::ZeroMQ INTERFACE IMPORTED)
  set_target_properties(ZeroMQ::ZeroMQ PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${ZEROMQ_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${ZEROMQ_LIBRARIES}"
  )
endif()

## Use Czmq
if (NOT MSVC)
    find_package(PkgConfig)
    pkg_check_modules(PC_LIBCURL "libcurl")
    if (PC_LIBCURL_FOUND)
        # add CFLAGS from pkg-config file, e.g. draft api.
        add_definitions(${PC_LIBCURL_CFLAGS} ${PC_LIBCURL_CFLAGS_OTHER})
        # some libraries install the headers is a subdirectory of the include dir
        # returned by pkg-config, so use a wildcard match to improve chances of finding
        # headers and SOs.
        set(PC_LIBCURL_INCLUDE_HINTS ${PC_LIBCURL_INCLUDE_DIRS} ${PC_LIBCURL_INCLUDE_DIRS}/*)
        set(PC_LIBCURL_LIBRARY_HINTS ${PC_LIBCURL_LIBRARY_DIRS} ${PC_LIBCURL_LIBRARY_DIRS}/*)
    endif(PC_LIBCURL_FOUND)
endif (NOT MSVC)

find_path (
    ${CMAKE_FIND_PACKAGE_NAME}_INCLUDE_DIRS
    NAMES curl/curl.h
    HINTS ${PC_LIBCURL_INCLUDE_HINTS}
)

find_library (
    ${CMAKE_FIND_PACKAGE_NAME}_LIBRARIES
    NAMES libcurl curl
    HINTS ${PC_LIBCURL_LIBRARY_HINTS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    ${CMAKE_FIND_PACKAGE_NAME}
    REQUIRED_VARS ${CMAKE_FIND_PACKAGE_NAME}_LIBRARIES ${CMAKE_FIND_PACKAGE_NAME}_INCLUDE_DIRS
)
mark_as_advanced(
    ${CMAKE_FIND_PACKAGE_NAME}_FOUND
    ${CMAKE_FIND_PACKAGE_NAME}_LIBRARIES ${CMAKE_FIND_PACKAGE_NAME}_INCLUDE_DIRS
)

# ## use mscl
# find_library(MSCL_LIB_PATH NAMES libmscl.so PATHS "/usr/share/c++-mscl" DOC "MSCL Library" NO_DEFAULT_PATH)
# find_library(BOOST_LIB_PATH NAMES libboost_chrono.so PATHS "/usr/share/c++-mscl/Boost/lib" NO_DEFAULT_PATH)
# set(MSCL_INC_PATH "/usr/share/c++-mscl/source")
# set(BOOST_INC_PATH "/usr/share/c++-mscl/Boost/include")
# set(MSCL_LIB "/usr/share/c++-mscl")
# add_definitions(-std=c++11)
# include_directories(/usr/share/c++-mscl/source /usr/share/c++-mscl/Boost/include /usr/include)
# link_directories(/usr/share/c++-mscl)
# link_libraries(mscl pthread GL GLU glut GLEW glfw X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor m)
# add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

## Use OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)




# 실행파일 만들기
set(SOURCE_MAIN main.cpp)
add_executable(diva2 ${SOURCE_MAIN}
    ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC} 
    )# 생성할 실행파일 이름 지정

target_include_directories(diva2 PUBLIC 
    ${ZeroMQ_INCLUDE_DIR}
    )  # add the include directory to our compile directives
target_link_libraries(diva2 PUBLIC 
    ${ZeroMQ_LIBRARY} 
    # /usr/share/c++-mscl/libmscl.so
    )

# 서브 디렉토리에 있는 cmakeFiles을 실행시켜줌
add_subdirectory(MobilePlatform/Sensing)
# add_subdirectory(MobilePlatform/Visualization)

# add_subdirectory(GroundStation/Playback)

# add_subdirectory(test/zmq)
# add_subdirectory(test/ouster)
# add_subdirectory(test/protobuf)
# add_subdirectory(test/receiver_fromMobile)
# add_subdirectory(test/receiver_fromMobile_proto)
# add_subdirectory(test/sender_toCloud)
# add_subdirectory(test/sender_toCloud_protobuf)

# add_subdirectory(test/sensing_proto)
# add_subdirectory(test/sensor_connect)
# add_subdirectory(test/sensor_parsing)

# add_subdirectory(test/zmq_filetransfer)
# add_subdirectory(test/socketCan)
# add_subdirectory(test/zmq_protobuf/client)
# add_subdirectory(test/zmq_protobuf/server)

# add_subdirectory(test/openCv)
# add_subdirectory(test/openCv2)
#add_subdirectory(test/zmq_imgtransfer)
# add_subdirectory(test/can_dbcparser)

# add_subdirectory(test_GroundStation/AlgorithmTesting)
# add_subdirectory(test_GroundStation/ReceiverFromMobile)