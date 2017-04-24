
#ifndef CONCURRENTES_TP1_REY_H
#define CONCURRENTES_TP1_REY_H


#include "Carta.h"

class Rey : public Carta {

public:
    Rey(Palo palo);

    string jugar ();
};


#endif //CONCURRENTES_TP1_REY_H
