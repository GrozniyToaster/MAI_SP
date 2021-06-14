cmake_minimum_required(VERSION 3.16)
project(kp2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(kp2
        Mlispsem.cpp)
