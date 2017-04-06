
#ifndef CONCURRENTES_TP1_REY_H
#define CONCURRENTES_TP1_REY_H


#include "Carta.h"

class Rey : Carta {

public:
    Rey();
    ~Rey();
    Rey(const Rey& origen);
    Rey& operator= (const Rey& origen);

};


#endif //CONCURRENTES_TP1_REY_H
