cmake_minimum_required(VERSION 3.6)
project(Concurrentes_TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Main.cpp src/logger/Logger.cpp include/logger/Logger.h src/ipc/MemoriaCompartida.cpp include/ipc/MemoriaCompartida.h src/juego/Jugador.cpp include/juego/Jugador.h src/juego/Carta.cpp include/juego/Carta.h src/juego/Sota.cpp include/juego/Sota.h src/juego/Caballo.cpp include/juego/Caballo.h src/juego/Rey.cpp include/juego/Rey.h include/juego/Palo.h src/juego/Siete.cpp include/juego/Siete.h src/juego/Mazo.cpp include/juego/Mazo.h)

add_executable(Concurrentes_TP1 ${SOURCE_FILES})