
#include "../../include/juego/Arbitro.h"

vector<Carta> Arbitro::verPilonDe(Jugador& jugador) {
    stack<Carta> pilonParaVer = jugador.mostrarPilon();
    //TODO: que hay que hacer con el pilon
}

Arbitro::Arbitro() {

}

Arbitro::~Arbitro() {
    delete this;
}