
#include "../../include/juego/Arbitro.h"

int Arbitro::verCantCartasPilonDeJugador(int nroJugador) {
    char buffer[BUFFSIZE];
    ssize_t bytesLeidos = canalesConJugadores [nroJugador - 1] -> leer ( static_cast<void*>(buffer), BUFFSIZE );
    std::string mensaje = buffer;
    mensaje.resize ( bytesLeidos );
    return atoi(mensaje.c_str());
}

Arbitro::~Arbitro() {
    for (int i =0; i < cantJugadores; i++) {
        canalesConJugadores [i] -> cerrar();
    }
}

Arbitro::Arbitro(Pipe** canalesConJugadores, int cantJugadores) {
    this->canalesConJugadores = canalesConJugadores;
    this->cantJugadores = cantJugadores;
}
