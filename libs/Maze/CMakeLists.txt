cmake_minimum_required(VERSION 3.16)

project(Maze LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 设置静态库（.a/.lib）的输出目录为项目根目录下的lib文件夹
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(headers sources)

add_library(Maze STATIC
  sources/cores/framework.cpp
  # sources/main.cpp
  sources/cores/map.cpp
  sources/cores/player.cpp
  sources/cores/points.cpp
  sources/utils/constants.cpp
  sources/utils/resources.cpp
  sources/views/dialogs/successdialog.cpp
  sources/views/dialogs/successdialog.ui
  sources/views/mazeGame.cpp
  sources/views/mazeGame.ui
  sources/views/widgets/scenewidget.cpp
  headers/cores/framework.h
  headers/cores/map.h
  headers/cores/player.h
  headers/cores/points.h
  headers/utils/constants.h
  headers/utils/difficulty.h
  headers/utils/resources.h
  headers/views/dialogs/successdialog.h
  headers/views/mazeGame.h
  headers/views/widgets/scenewidget.h
  resources/maze_res.qrc
)

target_link_libraries(Maze PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Gui)

target_compile_definitions(Maze PRIVATE MAZE_LIBRARY)
