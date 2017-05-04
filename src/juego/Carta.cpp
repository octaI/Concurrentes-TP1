
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

void Carta::accion(int nroJugador, int nroAnteultimaCarta) {
    string jugadorMsg = "Jugador " + to_string(nroJugador) + ": ";

    if (nroAnteultimaCarta == this->numero) {
        cout << jugadorMsg << "Coloco la mano en el centro de la mesa" << endl;
    }

    switch ( this->numero ) {
        case 7:
            cout << jugadorMsg << "'¡Atrevido!' / Coloco la mano en el centro de la mesa" << endl;
            break;
        case 10:
            cout << jugadorMsg << "'Buenos días, señorita'" << endl;
            break;
        case 11:
            cout << jugadorMsg << "'Buenas noches, caballero'" << endl;
            break;
        case 12:
            cout << jugadorMsg << "Hago la venia" << endl;
            break;
        default:
            break;
    }
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
