
#ifndef CONCURRENTES_TP1_CARTA_H
#define CONCURRENTES_TP1_CARTA_H


#include "Palo.h"

class Carta {

private:
    char numero;
    Palo palo;

public:
    Carta ( char numero, Palo palo );
    ~Carta ();
    Carta (const Carta& origen);
    Carta& operator= (const Carta& origen);

};


#endif //CONCURRENTES_TP1_CARTA_H
