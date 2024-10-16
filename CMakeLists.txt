cmake_minimum_required(VERSION 3.29)
project(BaseConverter C)

set(CMAKE_C_STANDARD 11)

add_executable(BaseConverter main.c)

target_link_libraries(BaseConverter m)
