
#include "../../include/juego/Atrevido.h"


Atrevido::~Atrevido() {
    for (Jugador* jugador : this->jugadores) {
        delete jugador;
    }
}

void Atrevido::jugarPartida() {
    while (!hayGanador()) {
        jugarRonda();
    }
    terminarPartida();
}

void Atrevido::jugarRonda() {

}

void Atrevido::terminarPartida() {

}

bool Atrevido::hayGanador() {
    return false;
}

Atrevido::Atrevido(int nroJugadores) {
    crearJugadores (nroJugadores);
}

void Atrevido::crearJugadores(int nroJugadores) {
    // TODO: Crear los semaforos necesarios para el turno de los jugadores.

    Mazo mazo;
    mazo.barajar();

    // TODO: forkear y crear jugadores, y repartir el mazo entre ellos.
}
