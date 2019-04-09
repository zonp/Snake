# 运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required(VERSION 3.12)
# 项目的名称是 snake
project(snake C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)


# 添加编译选项
add_compile_options(-lcurses)
#set(CMAKE_C_FLAGS  "-lcurses")
#add_definitions(-lcurses)
### 可执行文件的路径
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# 查找src目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
aux_source_directory(src DIR_SRCS)

set(CMAKE_C_FLAGS "-lcurses")

# 添加 map 子目录
#add_subdirectory(src/map)

# 将源文件编译成一个名称为 snake 的可执行文件
#add_executable(snake src/snake.c src/Map.c src/Food.c)
add_executable(snake ${DIR_SRCS})
