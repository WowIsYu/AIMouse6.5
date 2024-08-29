QT       += core gui network concurrent xml serialport bluetooth printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 6): QT += core5compat


CONFIG += c++17
TEMPLATE = app

CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attentionshow.cpp \
    blinkcalibration.cpp \
    choosedevice.cpp \
    colorswitching.cpp \
    initdatasystemprotocol.cpp \
    login.cpp \
    main.cpp \
    markingtester.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    setinfowidget.cpp \
    setup.cpp \
    vmousemainwindow.cpp \
    waveform.cpp


HEADERS += \
    attentionshow.h \
    blinkcalibration.h \
    choosedevice.h \
    colorswitching.h \
    initdatasystemprotocol.h \
    login.h \
    mainwindow.h \
    markingtester.h \
    qcustomplot.h \
    setinfowidget.h \
    setup.h \
    vmousemainwindow.h \
    waveform.h \


FORMS += \
    attentionshow.ui \
    blinkcalibration.ui \
    choosedevice.ui \
    initdatasystemprotocol.ui \
    login.ui \
    mainwindow.ui \
    markingtester.ui \
    setinfowidget.ui \
    setup.ui \
    vmousemainwindow.ui \
    waveform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc

INCLUDEPATH += $$PWD/HDataSystem_lib/include
greaterThan(QT_MAJOR_VERSION, 5){
        win32: LIBS += -L$$PWD/HDataSystem_lib/libs/ -lHDataSystem6d
    }
else{
        win32: LIBS += -L$$PWD/HDataSystem_lib/libs/ -lHDataSystem5d
    }

INCLUDEPATH += $$PWD/blinkdetection_lib/include
CONFIG += debug_and_release
CONFIG(debug, debug|release){
    win32: LIBS += -L$$PWD/blinkdetection_lib/libs/win/debug/ -lHBlinkDetection6d -lHDataSystem6d -lHCloudClient6d
        win32: LIBS += -L$$PWD/blinkdetection_lib/libs/thirdparty/onnxruntime  -lonnxruntimed -lonnxruntime_providers_sharedd
        win32: LIBS += -L$$PWD/blinkdetection_lib/libs/thirdparty/fftw3  -lfftw3

}else{
    win32: LIBS += -L$$PWD/blinkdetection_lib/libs/win/release/ -lHBlinkDetection -lHDataSystem6 -lHCloudClient
        win32: LIBS += -L$$PWD/blinkdetection_lib/libs/thirdparty/onnxruntime  -lonnxruntime -lonnxruntime_providers_shared

}


INCLUDEPATH += $$PWD/include
LIBS += $$PWD/libs/win/debug/HDataSystem6d.lib
LIBS += $$PWD/libs/win/debug/HCloudClient6d.lib
LIBS += $$PWD/libs/win/debug/HMultiControlSDKd.lib

INCLUDEPATH += $$PWD/thirdparty_libs
LIBS += $$PWD/thirdparty_libs/onnxruntime/onnxruntime.lib
LIBS += $$PWD/thirdparty_libs/onnxruntime/onnxruntimed.lib
LIBS += $$PWD/thirdparty_libs/onnxruntime/onnxruntime_providers_shared.lib
LIBS += $$PWD/thirdparty_libs/onnxruntime/onnxruntime_providers_sharedd.lib
LIBS += $$PWD/thirdparty_libs/fftw3/libfftw3-3.lib

LIBS += -lUser32

