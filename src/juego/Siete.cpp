
#include "../../include/juego/Siete.h"

Siete::Siete(Palo palo) : Carta(7, palo) {}

string Siete::jugar() {
    return Carta::jugar();
}
