
#include "../../include/juego/Siete.h"

Siete::Siete(Palo palo) : Carta(7, palo) {}

string Siete::accion(int nroJugador) {
    return Carta::accion(nroJugador);
}
