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

INCLUDEPATH += $$PWD/HMultiControlSDK/include
LIBS += $$PWD/HMultiControlSDK/libs/win/debug/HDataSystem6d.lib
LIBS += $$PWD/HMultiControlSDK/libs/win/debug/HCloudClient6d.lib
LIBS += $$PWD/HMultiControlSDK/libs/win/debug/HMultiControlSDKd.lib
LIBS += -L$$PWD/HMultiControlSDK/libs/win/debug -lHDataSystem6d

INCLUDEPATH += $$PWD/HMultiControlSDK/thirdparty_libs
LIBS += $$PWD/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntime.lib
LIBS += $$PWD/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntimed.lib
LIBS += $$PWD/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntime_providers_shared.lib
LIBS += $$PWD/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntime_providers_sharedd.lib
LIBS += $$PWD/HMultiControlSDK/thirdparty_libs/fftw3/libfftw3-3.lib
LIBS += -L$$PWD/HMultiControlSDK/thirdparty_libs/fftw3  -lfftw3

LIBS += -lUser32

