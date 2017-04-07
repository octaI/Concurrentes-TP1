
#include "../../include/juego/Sota.h"

Sota::Sota(Palo palo) : Carta(10, palo) {}

string Sota::jugar() {
    return Carta::jugar();
}
