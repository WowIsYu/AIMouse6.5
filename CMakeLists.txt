# CMake要求工程主目录和所有存放源代码子目录都要编写CMakeLists.txt

# 变量：
# CMake变量使用${}方式取值， 但是IF控制语句中直接使用变量名
# 环境变量使用$ENV{}方式取值， 使用SET(ENV{VAR} VALUE)赋值
#   参数使用括弧括起， 参数之间使用空格或 ; 分来
#eg: ADD_EXECUTABLE(hello main.c func.c)
####指令是大小写无关的,参数和变量是大小写相关的


# 规定cmake软件的最低版本。这行命令是可选的，可以不写这句话，但在有些情况下，
# 如果CMakeLists.txt文件中使用了一些高版本cmake特有的一些命令时，
# 就需要加上这一行，提醒用户升级到该版本之后再执行cmake。
cmake_minimum_required(VERSION 3.20)


# 设置项目名称, 在VS中叫做解决方案名称
# 不一定使用最后的应用名称，应用名称使用ADD_EXECUTABLE()定义
# 语法：project(projectname [cxx] [c] [java])
# 可以指定工程采用的语言，选项分别表示：C++, C, java， 如不指定默认支持所有语言。
project(NetroLink VERSION 1.0)
# 默认都为上面设置的main, 如果下面两个目录路径不同，则称为外部构建
# PROJECT_SOURCE_DIR : 项目源代码目录
# PROJECT_BINARY_DIR : 项目构建目录

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# 告诉CMake去子目录中查看可用的CMakeLists.txt文件
# 语法：ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
add_subdirectory(libs)
add_subdirectory(app)
# 热键
# add_subdirectory(QHotkey)

# ADD_EXECUTABLE命令
# 告诉工程生成一个可执行文件

# ADD_LIBRARY命令
# 告诉工程生成一个库文件
