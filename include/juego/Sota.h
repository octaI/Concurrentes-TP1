
#ifndef CONCURRENTES_TP1_SOTA_H
#define CONCURRENTES_TP1_SOTA_H


#include "Carta.h"

class Sota : Carta {

public:
    Sota();
    ~Sota();
    Sota(const Sota& origen);
    Sota& operator= (const Sota& origen);

};


#endif //CONCURRENTES_TP1_SOTA_H
