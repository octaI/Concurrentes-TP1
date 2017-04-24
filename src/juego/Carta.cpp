
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

string Carta::serializar(Carta carta) {
    // TODO: Serializar en serio, esto sirve para testear nomas.
    return to_string(carta.numero);
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
