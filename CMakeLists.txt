cmake_minimum_required(VERSION 3.6)
project(Concurrentes_TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Main.cpp src/Main.h)

add_executable(Concurrentes_TP1 ${SOURCE_FILES} src/Main.cpp src/Main.h)