
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

string Carta::serializar(Carta carta) {
    // TODO: Serializar en serio, esto sirve para testear nomas.
    return "carta";
}

Carta* Carta::deserializar(string serial) {
    // TODO: Deserializar en serio, esto sirve para testear nomas.
    return new Carta(1, Palo::Espada);
}

Carta &Carta::operator=(const Carta &origen) {
    this->numero = origen.numero;
    this->palo = origen.palo;
    return *this;
}
