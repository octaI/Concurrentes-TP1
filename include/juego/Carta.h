
#ifndef CONCURRENTES_TP1_CARTA_H
#define CONCURRENTES_TP1_CARTA_H

#include <iostream>
#include "Palo.h"
#include "../../include/logger/Logger.h"


using namespace std;

class Carta {

private:
    int numero;
    Palo palo;

public:
    Carta ( int numero, Palo palo );
    ~Carta ();
    Carta (const Carta& origen);
    Carta& operator= (const Carta& origen);

    static string serializar (Carta carta);
    static Carta* deserializar (string serial);

    int getNumero();
    Palo getPalo();

    void accion (int nroJugador);

};


#endif //CONCURRENTES_TP1_CARTA_H
