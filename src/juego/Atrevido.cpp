
#include "../../include/juego/Atrevido.h"

Atrevido::Atrevido(vector<Jugador *> jugadores) {
    this->jugadores = jugadores;
}

Atrevido::~Atrevido() {
    for (Jugador* jugador : this->jugadores) {
        delete jugador;
    }
}

void Atrevido::jugarPartida() {
    repartirCartas();
    while (!hayGanador()) {
        jugarRonda();
    }
    terminarPartida();
}

void Atrevido::repartirCartas() {

}

void Atrevido::jugarRonda() {

}

void Atrevido::terminarPartida() {

}

bool Atrevido::hayGanador() {
    return false;
}
