
#ifndef CONCURRENTES_TP1_CABALLO_H
#define CONCURRENTES_TP1_CABALLO_H


#include "Carta.h"

class Caballo : Carta {

public:
    Caballo();
    ~Caballo();
    Caballo(const Caballo& origen);
    Caballo& operator= (const Caballo& origen);

};


#endif //CONCURRENTES_TP1_CABALLO_H
