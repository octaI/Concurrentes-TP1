#include "../../include/juego/Jugador.h"

Jugador::~Jugador() {

}

Jugador::Jugador(const Jugador &origen) {

}

Jugador::Jugador(int nro) {
    this->nro = nro;
    this->cartasEnPilon = vector<Carta*> (CANT_CARTAS);
}
