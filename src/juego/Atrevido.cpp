
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

void Atrevido::crearJugadores(const int nroJugadores) {
    int valoresIniciales [nroJugadores];
    valoresIniciales[0] = 1;
    Semaforo semaforos ( "Atrevido.cpp", 'j', valoresIniciales, nroJugadores );

    Mazo mazo;
    mazo.barajar();

    // TODO: forkear y crear jugadores, y repartir el mazo entre ellos.
}
