
#include "../../include/juego/Sota.h"

Sota::Sota(Palo palo) : Carta(10, palo) {}

string Sota::accion(int nroJugador) {
    return Carta::accion(nroJugador);
}
