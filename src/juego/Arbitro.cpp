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

Arbitro::Arbitro(Pipe **canalesConJugadores, Semaforo* semaforoConsulta, int cantJugadores) {
    this->canalesConJugadores = canalesConJugadores;
    this->semaforoConsulta = semaforoConsulta;
    this->cantJugadores = cantJugadores;
}

void Arbitro::consultar() {
    semaforoConsulta->wait();

    for (int i = 0; i < cantJugadores; i++) {
        int cantCartas = verCantCartasPilonDeJugador(i);
        Logger :: getInstance() -> info ( "Arbitro", "El jugador " + to_string(i + 1) + " tiene " + to_string(cantCartas) + " cartas" );
    }
}
