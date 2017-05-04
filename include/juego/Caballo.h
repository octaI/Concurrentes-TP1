
#ifndef CONCURRENTES_TP1_CABALLO_H
#define CONCURRENTES_TP1_CABALLO_H


#include "Carta.h"

class Caballo : public Carta {

public:
    Caballo(Palo palo);

    string accion (int nroJugador);
};


#endif //CONCURRENTES_TP1_CABALLO_H
