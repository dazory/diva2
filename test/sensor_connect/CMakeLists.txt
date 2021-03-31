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

## use thread
find_package( Threads )

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

# 실행파일 만들기
set(SOURCE_SENSOR_CONNECT main.cpp)
add_executable(sensing ${SOURCE_SENSOR_CONNECT} ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC})                           # 생성할 실행파일 이름 지정
target_include_directories(sensing PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(sensing PUBLIC ${ZeroMQ_LIBRARY} 
        /usr/share/c++-mscl/libmscl.so
        )           # at the 0mq library to our link directive

# target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${JSONCPP_LIBRARIES} ${OpenCV_LIBS} ${GTK2_LIBRARIES}
# ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT}
# 	/usr/share/c++-mscl/libmscl.so
# )

