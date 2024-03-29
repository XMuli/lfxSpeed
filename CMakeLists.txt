# cmake 运行最低版本
cmake_minimum_required(VERSION 3.2)

# 使用 set 命令设置一个变量
set(PLUGIN_NAME "lfxSpeed")

# 设置项目名称
project(${PLUGIN_NAME})

# 启用 qt moc 的支持
set(CMAKE_AUTOMOC ON)
# 启用 qrc 资源文件的支持
set(CMAKE_AUTORCC ON)

# 指定所有源码文件
# 使用了 cmake 的 file 命令，递归查找项目目录下所有头文件和源码文件，
# 并将结果放入 SRCS 变量中，SRCS 变量可用于后续使用
file(GLOB_RECURSE SRCS "*.h" "*.cpp" "*.json")

# 指定要用到的库
# 使用了 cmake 的 find_package 命令，查找库 Qt5Widgets 等，
# REQUIRED 参数表示如果没有找到则报错
# find_package 命令在找到并加载指定的库之后会设置一些变量，
# 常用的有：
# <库名>_FOUND          是否找到（Qt5Widgets_FOUND）
# <库名>_DIR            在哪个目录下找到的（Qt5Widgets_DIR）
# <库名>_INCLUDE_DIRS   有哪些头文件目录（Qt5Widgets_INCLUDE_DIRS）
# <库名>_LIBRARIES      有哪些库文件（Qt5Widgets_LIBRARIES）
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Network REQUIRED)
#find_package(DtkWidget REQUIRED)

find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
#find_package(Qt5Svg REQUIRED)
#find_package(Qt5DBus REQUIRED)
find_package(DtkWidget REQUIRED)
#pkg_check_modules(DFrameworkDBus REQUIRED dframeworkdbus)

#pkg_check_modules(DFrameworkDBus REQUIRED dframeworkdbus)
#pkg_check_modules(QGSettings REQUIRED gsettings-qt)

# find_package 命令还可以用来加载 cmake 的功能模块
# 并不是所有的库都直接支持 cmake 查找的，但大部分都支持了 pkg-config 这个标准，
# 因此 cmake 提供了间接加载库的模块：FindPkgConfig， 下面这行命令表示加载 FindPkgConfig 模块，
# 这个 cmake 模块提供了额外的基于 “pkg-config” 加载库的能力
# 执行下面的命令后后会设置如下变量，不过一般用不到：
# PKG_CONFIG_FOUND            pkg-config 可执行文件是否找到了
# PKG_CONFIG_EXECUTABLE       pkg-config 可执行文件的路径
# PKG_CONFIG_VERSION_STRING   pkg-config 的版本信息
#find_package(PkgConfig REQUIRED)

# 加载 FindPkgConfig 模块后就可以使用 pkg_check_modules 命令加载需要的库
# pkg_check_modules 命令是由 FindPkgConfig 模块提供的，因此要使用这个命令必须先加载 FindPkgConfig 模块。
# 执行 pkg_check_modules 命令加载库也会设置一些类似执行 find_package 加载库后设置的变量：
# DdeDockInterface_FOUND
# DdeDockInterface_INCLUDE_DIRS
# DdeDockInterface_LIBRARIES
# 还有有另外的一些变量以及更灵活的用法，比如一次性查找多个库，这些请自行查找 cmake 文档学习。
#pkg_check_modules(DFrameworkDBus REQUIRED dframeworkdbus)

# add_definitions 命令用于声明/定义一些编译/预处理参数
# 根据 cmake 文档描述此命令已经有另外几个功能划分的更为细致的命令所取代，具体请查阅文档
# 在我们这里的例子应该使用较新的 add_compile_definitions 命令，不过为了保持与 dock 已有插件一致，
# 暂时仍然使用 add_definitions，add_definitions 的语法很简单就是直接写要定义的 flag 并在前面加上 "-D" 即可
# 括号中的 ${QT_DEFINITIONS} 变量会在执行 cmake 时展开为它的值，这个变量属于历史遗留，应该是在 qt3/qt4 时有用，
# 基于 qt5 或更高版本的新插件不必使用此变量。要查看 qt5 的库定义了哪些变量应该查看变量：${Qt5Widgets_DEFINITIONS}
add_definitions("${QT_DEFINITIONS} -DQT_PLUGIN")

# 新增一个编译目标
# add_library: 表示本项目要生成一个库文件，SHARED 表示生成的库应该是动态库，
# add_executable: 生成一个可执行二进制目标文件，甚至 add_custom_target(使用较少) 添加自定义目标
# 变量 ${PLUGIN_NAME} 和 ${SRCS} 都是前面处理好的，
# 另外 qrc 资源文件也应该追加在后面以编译进目标中。
add_library(${PLUGIN_NAME} SHARED ${SRCS} resources.qrc)

# 表示生成二进制文件(不等价于动态库 add_library), 一个项目不能够同时生成为 动态库,又同时生成为一个二进制应用程序
# 简单来说 add_library / add_library 只能够二选一
# add_executable(${PROJECT_NAME} "main.cpp")

# 设置目标的生成位置，这里表示生成在执行 make 的目录,
# 另外还有很多可用于设置的属性，可查阅 cmake 文档。
set_target_properties(${PLUGIN_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ./)


# 设置目标要使用的 include 目录，即头文件目录
# 变量 ${DtkWidget_INCLUDE_DIRS} 是在前面执行 find_package 命令时引入的
# 当出现编译失败提示找不到某些库的头文件时应该检查此处是否将所有需要的头文件都包含了
target_include_directories(${PLUGIN_NAME} PUBLIC
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${DtkWidget_INCLUDE_DIRS}
    ${DdeDockInterface_INCLUDE_DIRS}
)

# 设置目标要使用的链接库
# 变量 ${DtkWidget_LIBRARIES} 和 ${Qt5Widgets_LIBRARIES} 是在前面执行 find_package 命令时引入的
# 当出现运行时错误提示某些符号没有定义时应该检查此处是否将所有用的库都写在了这里
target_link_libraries(${PLUGIN_NAME} PRIVATE
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Network_LIBRARIES}
    ${DtkWidget_LIBRARIES}
    ${DdeDockInterface_LIBRARIES}
)

# 设置安装路径的前缀(默认为"/usr/local")
set(CMAKE_INSTALL_PREFIX "/usr")

# 设置执行 make install 时哪个目标应该被 install 到哪个位置
install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION lib/dde-dock/plugins)

#Translation
# set(TS_FILES /translations/lfxSpeed-en.ts /translations/lfxSpeed_es.ts)
# set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "l10n")
# qt5_add_translation(qmFiles ${TS_FILES})

set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")

set(TS_FILES
    "${TS_DIR}/${PROJECT_NAME}_es_ES.ts"
    "${TS_DIR}/${PROJECT_NAME}_en_EN.ts"
)

find_program(LUPDATE_EXECUTABLE lupdate)
find_program(LRELEASE_EXECUTABLE lrelease)

foreach(_ts_file ${TS_FILES})

    execute_process(
        COMMAND ${LUPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${_ts_file})
    execute_process(
        COMMAND ${LRELEASE_EXECUTABLE} ${_ts_file})

endforeach()
