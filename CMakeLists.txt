cmake_minimum_required(VERSION 3.12)
project(test C)
set(CMAKE_C_STANDARD 99)

set(pwd "./")
message("pwd: ${pwd}")
include_directories(${pwd})

add_executable(test main.c)