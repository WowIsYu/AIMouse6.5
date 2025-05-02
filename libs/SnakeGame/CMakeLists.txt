cmake_minimum_required(VERSION 3.16)

project(SnakeGame LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 设置静态库（.a/.lib）的输出目录为项目根目录下的lib文件夹
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(src include)

add_library(SnakeGame STATIC
  src/rankdialog.cpp
  src/snakegame.cpp
  src/rankdialog.ui
  src/snakegame.ui
  include/rankdialog.h
  include/snakegame.h

)

target_link_libraries(SnakeGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(SnakeGame PRIVATE SNAKEGAME_LIBRARY)
