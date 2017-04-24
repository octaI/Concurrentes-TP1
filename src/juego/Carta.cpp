
#include "../../include/juego/Carta.h"

Carta::Carta(int numero, Palo palo) {
    this->numero = numero;
    this->palo = palo;
}

Carta::Carta(const Carta &origen) {

}

Carta::~Carta() {

}

int Carta::getNumero(){
    return numero;
}
Palo Carta::getPalo(){
    return palo;
}

string Carta::jugar() {
    return "Carta jugada!";
}
