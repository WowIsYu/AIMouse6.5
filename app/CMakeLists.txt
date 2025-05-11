cmake_minimum_required(VERSION 3.16)

project(app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:/develop_software/Qt-6.5.3/6.5.3/msvc2019_64")

# 设置调试/发布输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/MyDebug")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/MyRelease")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets
            Network Concurrent Xml SerialPort Bluetooth PrintSupport Core5Compat REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql Charts WebEngineWidgets)
# target_link_libraries(mytarget PRIVATE Qt6::Sql)
# 第三方库路径
set(THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/third_party")

set(PROJECT_SOURCES
  ${THIRD_PARTY_DIR}/colorswitching/colorswitching.cpp
  ${THIRD_PARTY_DIR}/qcustomplot/qcustomplot.cpp
  ${THIRD_PARTY_DIR}/tchartview/tchartview.cpp
  ${THIRD_PARTY_DIR}/QHotkey/qhotkey.cpp
  ${THIRD_PARTY_DIR}/QHotkey/qhotkey_win.cpp
  ui/datawidget.cpp
  ui/blinkcaliwidget.cpp
  ui/gamewidget.cpp
  ui/loginwidget.cpp
  ui/mainwindow.cpp
  ui/setupwidget.cpp
  ui/waveformwidget.cpp
  toolui/choosedevice.cpp
  toolui/initdatasystemprotocol.cpp
  toolui/markingtester.cpp
  toolui/setinfowidget.cpp
  toolui/vmousemainwindow.cpp
  main.cpp

  ${THIRD_PARTY_DIR}/colorswitching/colorswitching.h
  ${THIRD_PARTY_DIR}/qcustomplot/qcustomplot.h
  ${THIRD_PARTY_DIR}/tchartview/tchartview.h
  ${THIRD_PARTY_DIR}/QHotkey/qhotkey.h
  ui/datawidget.h
  ui/blinkcaliwidget.h
  ui/gamewidget.h
  ui/loginwidget.h
  ui/mainwindow.h
  ui/setupwidget.h
  ui/waveformwidget.h
  toolui/choosedevice.h
  toolui/initdatasystemprotocol.h
  toolui/markingtester.h
  toolui/setinfowidget.h
  toolui/vmousemainwindow.h

  ui/datawidget.ui
  ui/blinkcaliwidget.ui
  ui/gamewidget.ui
  ui/loginwidget.ui
  ui/mainwindow.ui
  ui/setupwidget.ui
  ui/waveformwidget.ui
  toolui/choosedevice.ui
  toolui/initdatasystemprotocol.ui
  toolui/markingtester.ui
  toolui/setinfowidget.ui
  toolui/vmousemainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
        core/databasemanager.cpp core/databasemanager.h
        core/hmulticontrolwrapper.h core/hmulticontrolwrapper.cpp
        toolui/datadetail.h toolui/datadetail.cpp toolui/datadetail.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(app SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(app
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 对应INCLUDEPATH
# target_include_directories(app PRIVATE
#   ${CMAKE_SOURCE_DIR}/libs/Nagano/include
#   ${CMAKE_SOURCE_DIR}/libs/SnakeGame/include
#   ${CMAKE_SOURCE_DIR}/libs/Maze/headers
# )

#--------------------------------------------------
# 配置第三方库包含路径
#--------------------------------------------------
target_include_directories(app PRIVATE
    # 内部库头文件
    "${CMAKE_SOURCE_DIR}/libs/Nagano/include"
    "${CMAKE_SOURCE_DIR}/libs/SnakeGame/include"
    "${CMAKE_SOURCE_DIR}/libs/Maze/headers"
    ui
    toolUi
    core

    # 第三方库头文件
    "${THIRD_PARTY_DIR}/HMultiControlSDK/include"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/include/HDataSystem"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/include/HCloudClient"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/thirdparty_libs"
    "${THIRD_PARTY_DIR}/colorswitching"
    "${THIRD_PARTY_DIR}/qcustomplot"
    "${THIRD_PARTY_DIR}/tchartview"
    "${THIRD_PARTY_DIR}/QHotkey"
)


#--------------------------------------------------
# 配置第三方库链接
#--------------------------------------------------
# HMultiControlSDK库
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(HMC_LIB_DIR "${THIRD_PARTY_DIR}/HMultiControlSDK/libs/win/debug")
    set(HMC_LIBS
        "${HMC_LIB_DIR}/HDataSystem6d.lib"
        "${HMC_LIB_DIR}/HCloudClient6d.lib"
        "${HMC_LIB_DIR}/blinkd.lib"
        "${HMC_LIB_DIR}/HMultiControl6d.lib"
    )
else()
    set(HMC_LIB_DIR "${THIRD_PARTY_DIR}/HMultiControlSDK/libs/win/release")
    set(HMC_LIBS
        "${HMC_LIB_DIR}/HDataSystem6.lib"
        "${HMC_LIB_DIR}/HCloudClient6.lib"
        "${HMC_LIB_DIR}/blink.lib"
        "${HMC_LIB_DIR}/HMultiControl6.lib"
    )
endif()

# ONNX Runtime库
list(APPEND HMC_LIBS
    "${THIRD_PARTY_DIR}/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntime.lib"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntimed.lib"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntime_providers_shared.lib"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/thirdparty_libs/onnxruntime/onnxruntime_providers_sharedd.lib"
    "${THIRD_PARTY_DIR}/HMultiControlSDK/thirdparty_libs/fftw3/libfftw3-3.lib"
)



message(STATUS "Library path: ${CMAKE_SOURCE_DIR}/libs/Nagano/lib")
link_directories(
  ${CMAKE_SOURCE_DIR}/libs/Nagano/lib
  ${CMAKE_SOURCE_DIR}/libs/SnakeGame/lib
  ${CMAKE_SOURCE_DIR}/libs/Maze/lib
)

# target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
#   Nagano
#   SnakeGame
#   Maze
#   HMultiControl
#   )

#--------------------------------------------------
# 链接库配置
#--------------------------------------------------
target_link_libraries(app PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    # Qt${QT_VERSION_MAJOR}::Network
    # Qt${QT_VERSION_MAJOR}::Concurrent
    # Qt${QT_VERSION_MAJOR}::Xml
    # Qt${QT_VERSION_MAJOR}::SerialPort
    # Qt${QT_VERSION_MAJOR}::Bluetooth
    # Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt6::WebEngineWidgets
    Qt6::Charts
    Qt6::Sql
    # Qt${QT_VERSION_MAJOR}::Core5Compat

    # 内部库
    Nagano
    SnakeGame
    Maze

    # 第三方库
    ${HMC_LIBS}

    # Windows系统库
    winmm
    User32
)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app)
endif()
set_target_properties(app PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(app)
endif()
