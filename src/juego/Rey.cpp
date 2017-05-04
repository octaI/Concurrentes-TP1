
#include "../../include/juego/Rey.h"

Rey::Rey(Palo palo) : Carta(12, palo) {}

string Rey::accion(int nroJugador) {
    return Carta::accion(nroJugador);
}
