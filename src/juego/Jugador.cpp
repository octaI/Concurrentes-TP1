#include "../../include/juego/Jugador.h"

Jugador::Jugador(const Jugador &origen) {

}

Jugador::Jugador(int nro) {
    this->nro = nro;
}

stack<Carta> Jugador::mostrarPilon() {
    return cartasEnPilon; //doy el puntero del stack
}

void Jugador::tomarCarta(Carta& carta) {
    cartasEnPilon.push(carta);
}

int Jugador::mostrarNumero() {
    return nro;
}

Jugador::~Jugador() {
    while (!cartasEnPilon.empty()){
        Carta cartaTemp = cartasEnPilon.top();
        delete &cartaTemp;
    }

}

Carta Jugador::jugarCarta() {
    return Carta(1, Palo::Oro);
    /*
    Carta& cartaAJugar = this->cartasEnPilon.top();
    this->cartasEnPilon.pop();
    return cartaAJugar;
    */
}
