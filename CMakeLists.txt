cmake_minimum_required(VERSION 3.6)
project(Concurrentes_TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Main.cpp src/logger/Logger.cpp include/logger/Logger.h include/ipc/MemoriaCompartida.h src/juego/Jugador.cpp include/juego/Jugador.h src/juego/Carta.cpp include/juego/Carta.h include/juego/Palo.h src/juego/Mazo.cpp include/juego/Mazo.h src/juego/Arbitro.cpp src/juego/Atrevido.cpp include/juego/Atrevido.h src/juego/Accion.cpp include/juego/Accion.h src/ipc/signal/SignalHandler.cpp include/ipc/signal/SignalHandler.h include/ipc/signal/EventHandler.h include/ipc/signal/impl/SIGINT_Handler.h src/ipc/fifo/Fifo.cpp include/ipc/fifo/Fifo.h src/ipc/fifo/impl/FIfoEscritura.cpp include/ipc/fifo/impl/FIfoEscritura.h src/ipc/fifo/impl/FifoLectura.cpp include/ipc/fifo/impl/FifoLectura.h src/ipc/Pipe.cpp include/ipc/Pipe.h src/ipc/LockFile.cpp include/ipc/LockFile.h src/ipc/Semaforo.cpp include/ipc/Semaforo.h include/ipc/MemoriaComp.h)

add_executable(Concurrentes_TP1 ${SOURCE_FILES})