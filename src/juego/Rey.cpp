
#include "../../include/juego/Rey.h"

Rey::Rey(Palo palo) : Carta(12, palo) {}

string Rey::jugar() {
    return Carta::jugar();
}
