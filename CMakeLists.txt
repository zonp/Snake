cmake_minimum_required(VERSION 3.12)
project(snake C)

set(CMAKE_C_STANDARD 11)

### 可执行文件的路径
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(snake src/snake.c src/Map.c)
