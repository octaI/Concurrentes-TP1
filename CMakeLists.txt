cmake_minimum_required(VERSION 3.6)
project(Concurrentes_TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Main.cpp src/logger/Logger.cpp include/logger/Logger.h src/ipc/MemoriaCompartida.cpp include/ipc/MemoriaCompartida.h src/juego/Jugador.cpp include/juego/Jugador.h)

add_executable(Concurrentes_TP1 ${SOURCE_FILES})