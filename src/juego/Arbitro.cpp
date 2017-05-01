
#include "../../include/juego/Arbitro.h"

int Arbitro::verPilonDe(Jugador& jugador) {
    stack<Carta*> pilonParaVer = jugador.mostrarPilon();
    return pilonParaVer.size();
    //TODO: que hay que hacer con el pilon
}

Arbitro::Arbitro() {

}

Arbitro::~Arbitro() {
    delete this;
}