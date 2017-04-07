
#include "../../include/juego/Carta.h"

Carta::Carta(char numero, Palo palo) {
    this->numero = numero;
    this->palo = palo;
}

Carta::Carta(const Carta &origen) {

}

Carta::~Carta() {

}

string Carta::jugar() {
    return "Carta jugada!";
}
