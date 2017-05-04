
#ifndef CONCURRENTES_TP1_SIETE_H
#define CONCURRENTES_TP1_SIETE_H


#include "Carta.h"

class Siete : public Carta {

public:
    Siete(Palo palo);

    string accion (int nroJugador);
};


#endif //CONCURRENTES_TP1_SIETE_H
