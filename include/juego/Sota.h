
#ifndef CONCURRENTES_TP1_SOTA_H
#define CONCURRENTES_TP1_SOTA_H


#include "Carta.h"

class Sota : public Carta {

public:
    Sota(Palo palo);

    string accion (int nroJugador);

};


#endif //CONCURRENTES_TP1_SOTA_H
