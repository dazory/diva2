
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


## Use Protobuf
# find_package(Protobuf REQUIRED)
# if(PROTOBUF_FOUND)
#     message(STATUS "protobuf library found")
# else()
#     message(FATAL_ERROR "protobuf library is needed but cant be found")
# endif()

# include_directories(${PROTOBUF_INCLUDE_DIRS})
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "../../protobuf/sensors.proto" )

## Use json
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

## Use Boost Library
# find_package( Boost REQUIRED COMPONENTS) # program_options regex )
# set(Boost_USE_STATIC_LIBS OFF) 
# set(Boost_USE_MULTITHREADED ON)  
# set(Boost_USE_STATIC_RUNTIME OFF) 
# find_package(Boost 1.45.0 COMPONENTS) #*boost libraries here*) 
# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS}) 
#     add_executable(progname file1.cxx file2.cxx) 
#     target_link_libraries(progname ${Boost_LIBRARIES})
# # endif()
# # Boost
# set(Boost_USE_MULTITHREADED ON)
# find_package(Boost 1.47.0 COMPONENTS system filesystem thread REQUIRED )
# set(INCLUDES ${INCLUDES} ${Boost_INCLUDE_DIRS} )
# set(LIBS ${LIBS} ${Boost_LIBRARIES} )

# ## Use PCL
# find_package(Eigen3 REQUIRED)
# find_package(PCL 1.11.1 REQUIRED)
# include_directories(${PCL_INCLUDE_DIRS} ${PCL_LIBRARIES}) #헤더 디렉토리 지정(-I)
# link_directories(${PCL_LIBRARY_DIRS}) #라이브러리 디렉토리 지정 (-L)
# add_definitions(${PCL_DEFINITIONS}) #전처리기 메크로 추가 (-D)

# json cpp
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

# ## ouster-LiDAR
# add_library(ouster_helper STATIC ../../service/ouster/client.cpp 
#                           ../../service/ouster/os1_util.cpp 
#                           ../../service/ouster/impl/netcompat.cpp 
#                           ../../service/ouster/types.cpp)
# set_target_properties(ouster_helper PROPERTIES POSITION_INDEPENDENT_CODE ON)
# target_link_libraries(ouster_helper jsoncpp)
# target_include_directories(ouster_helper PUBLIC include)
# target_include_directories(ouster_helper SYSTEM PRIVATE ${jsoncpp_INCLUDE_DIRS})

# ## Use VTK
# set( VTK_DIR "$ENV{PCL_ROOT}/3rdParty/VTK" )
# find_package(VTK REQUIRED COMPONENTS vtkCommonCore NO_MODULE)
# include_directories( ${VTK_INCLUDE_DIRS})
# # Load additional vtk components; prefer newer vtk opengl module
# set(VIZ_VTK_COMPONENTS vtkCommonCore vtkCommonDataModel vtkCommonMath
#   vtkCommonTransforms vtkFiltersSources vtkImagingCore vtkInteractionStyle
#   vtkRenderingCore
#   )
# if(TARGET vtkRenderingOpenGL2)
#   list(APPEND VIZ_VTK_COMPONENTS vtkRenderingOpenGL2)
# else()
#   list(APPEND VIZ_VTK_COMPONENTS vtkRenderingOpenGL)
# endif()
# find_package(VTK REQUIRED COMPONENTS ${VIZ_VTK_COMPONENTS} NO_MODULE)
# include(${VTK_USE_FILE})

# 실행파일 만들기
# 실행파일 만들기
set(SOURCE_TEST 
    main.cpp
)
add_executable(test_ex ${SOURCE_TEST} 
    # ${PROTO_SRCS} ${PROTO_HDRS}                 # Google Protocol Buffer
    # ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC}    # MSCL
    ${OpenCV_INCLUDE_DIRS}                      # OpenCV
    )
target_include_directories(test_ex PUBLIC 
    ${ZeroMQ_INCLUDE_DIR}   # ZeroMQ
    # ${Boost_INCLUDE_DIRS}   # Boost libarary
    ) # add the include directory to our compile directives
target_link_libraries(test_ex PUBLIC 
    ${ZeroMQ_LIBRARY}               # ZeroMQ
    ${OpenCV_LIBS}                  # OpenCV
    # ${PROTOBUF_LIBRARIES}           # Google Protocol Buffer
    # ${PCL_LIBRARIES}                # PCL
    # ${VTK_LIBRARIES}                # VTk  
    ${JSONCPP_LIBRARIES}            # json cpp
    /usr/share/c++-mscl/libmscl.so  # MSCL
    # ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY}     # Boost library
    # ouster_helper                   # LiDAR - ouster exmaple
    ) # at the 0mq library to our link directive


