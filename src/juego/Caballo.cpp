
#include "../../include/juego/Caballo.h"

Caballo::Caballo(Palo palo) : Carta(11, palo) {}

string Caballo::jugar() {
    return Carta::jugar();
}
