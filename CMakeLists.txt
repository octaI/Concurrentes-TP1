cmake_minimum_required(VERSION 3.6)
project(Concurrentes_TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/Main.cpp src/logger/Logger.cpp include/logger/Logger.h src/ipc/MemoriaCompartida.cpp include/ipc/MemoriaCompartida.h src/juego/Jugador.cpp include/juego/Jugador.h src/juego/Carta.cpp include/juego/Carta.h src/juego/Sota.cpp include/juego/Sota.h src/juego/Caballo.cpp include/juego/Caballo.h src/juego/Rey.cpp include/juego/Rey.h include/juego/Palo.h src/juego/Siete.cpp include/juego/Siete.h src/juego/Mazo.cpp include/juego/Mazo.h src/juego/Arbitro.cpp src/juego/Atrevido.cpp include/juego/Atrevido.h src/juego/RegistroDeAcciones.cpp include/juego/RegistroDeAcciones.h src/juego/Accion.cpp include/juego/Accion.h src/ipc/signal/SignalHandler.cpp include/ipc/signal/SignalHandler.h include/ipc/signal/EventHandler.h include/ipc/signal/impl/SIGINT_Handler.h src/ipc/fifo/Fifo.cpp include/ipc/fifo/Fifo.h src/ipc/fifo/impl/FIfoEscritura.cpp include/ipc/fifo/impl/FIfoEscritura.h src/ipc/fifo/impl/FifoLectura.cpp include/ipc/fifo/impl/FifoLectura.h src/ipc/Pipe.cpp include/ipc/Pipe.h src/ipc/LockFile.cpp include/ipc/LockFile.h src/ipc/Semaforo.cpp include/ipc/Semaforo.h include/juego/RegistroJugadores.h src/juego/RegistroJugadores.cpp include/juego/RegistroJugadores.h src/juego/RegistroJugadores.cpp)

add_executable(Concurrentes_TP1 ${SOURCE_FILES})