
cmake_minimum_required(VERSION 3.6)

project(GS_Visualization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

#pragma warning(push) #pragma warning(disable : 4345) #pragma warning(pop) 


# init_qt: Let's do the CMake job for us
set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
set(CMAKE_AUTOUIC ON) # UI files

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
#set( QTDIR $ENV{QTDIR} )
#set( CMAKE_PREFIX_PATH ${QTDIR} )
find_package(Qt5 REQUIRED Widgets Gui)
ADD_DEFINITIONS (${QT_DEFINITIONS})
find_package(Qt5 REQUIRED COMPONENTS Core Gui Sql X11Extras OpenGL Network PrintSupport WebEngineWidgets SerialPort SerialBus Charts)
find_package(Protobuf REQUIRED)

find_package(Threads)
find_package(Eigen3 REQUIRED)
set( VTK_DIR "$ENV{PCL_ROOT}/3rdParty/VTK" )
find_package(VTK REQUIRED COMPONENTS vtkCommonCore NO_MODULE)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )
        find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )


find_package(PCL 1.11.1 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

## Use Protobuf
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "../../protobuf/sensors.proto" )

# Load additional vtk components; prefer newer vtk opengl module
set(VIZ_VTK_COMPONENTS vtkCommonCore vtkCommonDataModel vtkCommonMath
  vtkCommonTransforms vtkFiltersSources vtkImagingCore vtkInteractionStyle
  vtkRenderingCore
  )
if(TARGET vtkRenderingOpenGL2)
  list(APPEND VIZ_VTK_COMPONENTS vtkRenderingOpenGL2)
else()
  list(APPEND VIZ_VTK_COMPONENTS vtkRenderingOpenGL)
endif()
find_package(VTK REQUIRED COMPONENTS ${VIZ_VTK_COMPONENTS} NO_MODULE)
include(${VTK_USE_FILE})


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 
 
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_definitions (${GTK2_CFLAGS_OTHER})

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

include_directories(include)
include_directories(SYSTEM
  ${EIGEN3_INCLUDE_DIR}
  ${VTK_INCLUDE_DIRS}
   ${PCL_LIBRARIES}
)

add_library(ouster_viz STATIC src/viz.cpp src/os1.cpp src/os1_util.cpp)
set_target_properties(ouster_viz PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(ouster_viz jsoncpp ${ZeroMQ_LIBRARY})
target_include_directories(ouster_viz PUBLIC ${ZeroMQ_INCLUDE_DIR} include)
target_include_directories(ouster_viz SYSTEM PRIVATE)

#set(project_SOURCES main.cpp mainwindow.cpp camthread.cpp glwidget.cpp gpsthread.cpp lidarthread.cpp lidarvtkwidget.cpp)
set(project_SOURCES main.cpp  canthread.cpp imuwidget.cpp  mainwindow.cpp camthread.cpp gpsthread.cpp 
  lidarthread.cpp lidarvtkwidget.cpp  imuthread.cpp qcgaugewidget.cpp qcustomplot.cpp)
#
add_executable(${PROJECT_NAME} ${project_SOURCES} ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${JSONCPP_LIBRARIES} ${OpenCV_LIBS} ${GTK2_LIBRARIES}
${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${PROTOBUF_LIBRARIES} 
	Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::PrintSupport
      	Qt5::Network
        Qt5::WebEngineWidgets
        Qt5::SerialBus
	     Qt5::OpenGL
		Qt5::Charts
	/usr/share/c++-mscl/libmscl.so
	GL
	GLU
	glut
	ouster_viz
)
