cmake_minimum_required(VERSION 3.16)

project(Nagano LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Gui)

# 设置静态库（.a/.lib）的输出目录为项目根目录下的lib文件夹
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(src include)

add_library(Nagano STATIC
  src/nagano.cpp
  include/nagano.h
  nagano_res.qrc
)


# 即使你已经通过 find_package 找到了 Qt 的模块，CMake 不会自动把这些库链接到你的目标（比如你的 app 或 test），
# 这需要你显式地通过 target_link_libraries 进行链接。
target_link_libraries(Nagano PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Gui
)

target_compile_definitions(Nagano PRIVATE NAGANO_LIBRARY)
