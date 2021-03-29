### diva2/test/zmq_filetransfer

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
add_executable(pub pub.cpp )                           # 생성할 실행파일 이름 지정
target_include_directories(pub PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(pub PUBLIC ${ZeroMQ_LIBRARY})           # at the 0mq library to our link directive

# 실행파일 만들기
add_executable(sub sub.cpp )                           # 생성할 실행파일 이름 지정
target_include_directories(sub PUBLIC ${ZeroMQ_INCLUDE_DIR})  # add the include directory to our compile directives
target_link_libraries(sub PUBLIC ${ZeroMQ_LIBRARY})           # at the 0mq library to our link directive

# target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${JSONCPP_LIBRARIES} ${OpenCV_LIBS} ${GTK2_LIBRARIES}
# ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT}
# 	/usr/share/c++-mscl/libmscl.so
# )
