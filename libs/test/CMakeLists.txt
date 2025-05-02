cmake_minimum_required(VERSION 3.16)

project(test LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# 设置静态库（.a/.lib）的输出目录为项目根目录下的lib文件夹
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(src include)

add_library(test STATIC
  src/test.cpp
  include/test.h
)

target_link_libraries(test PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(test PRIVATE TEST_LIBRARY)
