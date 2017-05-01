
#ifndef CONCURRENTES_TP1_MAZO_H
#define CONCURRENTES_TP1_MAZO_H

#define CANT_CARTAS 40

#include <stack>
#include <vector>
#include "Carta.h"
#include "Siete.h"
#include "Sota.h"
#include "Caballo.h"
#include "Rey.h"
#include "Palo.h"
#include "Jugador.h"

using namespace std;

class Mazo {

private:
    //vector<Carta*> cartas = vector<Carta*> (CANT_CARTAS);
    stack<Carta*>* cartas;

    void generar();

public:
    Mazo ();
    ~Mazo ();
    Mazo (const Mazo& origen);
    Mazo& operator= (const Mazo& origen);

    void barajar ();
    Carta* tomarCarta ();
    int cantidadDeCartas ();

};


#endif //CONCURRENTES_TP1_MAZO_H
