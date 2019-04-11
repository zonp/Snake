# 运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required(VERSION 3.12)
# 项目的名称是 snake
project(snake C)

# 项目版本号。
set(SNAKE_VERSION_MAJOR 1)
set(SNAKE_VERSION_MINOR 0)

set(PROJECT_NAME snake)
set(PROJECT_SOURCE_DIR "src")
set(PROJECT_BINARY_DIR "bin")

#配置头文件以传递一些CMake设置
#源代码
configure_file(
        "${PROJECT_SOURCE_DIR}/Config.h.in"
        "${PROJECT_BINARY_DIR}/Config.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

#install (TARGETS MathFunctions DESTINATION bin)
# install (FILES MathFunctions.h DESTINATION include)
# add the install targets
#install (TARGETS Tutorial DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#        DESTINATION include)


set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)


# 添加编译选项
add_compile_options(-lcurses)
#set(CMAKE_C_FLAGS  "-lcurses")
#add_definitions(-lcurses)
### 可执行文件的路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# 查找src目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SRCS)

set(CMAKE_C_FLAGS "-lcurses")

# 添加 map 子目录
#add_subdirectory(src/map)

# 将源文件编译成一个名称为 snake 的可执行文件
#add_executable(snake src/snake.c src/Map.c src/Food.c)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
