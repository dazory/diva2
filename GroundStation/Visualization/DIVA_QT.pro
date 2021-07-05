QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += webenginewidgets
QT += network
QT += opengl
QT += 3dcore 3drender 3dinput 3dextras
QT += charts

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bmpfuncs.cpp \
    camthread.cpp \
    canthread.cpp \
    displaythread.cpp \
    glwidget.cpp \
    gpsthread.cpp \
    imuthread.cpp \
    imuwidget.cpp \
    lidarthread.cpp \
    lidarvtkwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qcgaugewidget.cpp

HEADERS += \
    ObjParser.h \
    Timestamp.h \
    bmpfuncs.h \
    camthread.h \
    canthread.h \
    displaythread.h \
    glwidget.h \
    gps_packet.h \
    gpsthread.h \
    imuthread.h \
    imuwidget.h \
    lidarthread.h \
    lidarvtkwidget.h \
    mainwindow.h \
    qcgaugewidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: LIBS += -L$$PWD/../../../usr/share/c++-mscl/ -lmscl

INCLUDEPATH += $$PWD/../../../usr/share/c++-mscl
DEPENDPATH += $$PWD/../../../usr/share/c++-mscl

LIBS += -ljsoncpp \
    -lglut \
    -lGLU

INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_gapi -lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_highgui -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_videoio  -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core



INCLUDEPATH += /usr/include/eigen3

INCLUDEPATH += /usr/include/vtk-6.3

INCLUDEPATH += /usr/include/boost

INCLUDEPATH += /usr/include/pcl-1.8

RESOURCES += \
    formap.qrc

DISTFILES += \
    leftarrowbefore.png
