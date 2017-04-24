
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
    vector<Carta*> cartas = vector<Carta*> (CANT_CARTAS);

public:
    Mazo ();
    ~Mazo ();
    Mazo (const Mazo& origen);
    Mazo& operator= (const Mazo& origen);

    void generar();
    Carta* agarrar(int i); // TODO: Metodo de prueba, despues borrar.
    void barajar ();
    Carta tomarCarta ();
    void repartirEntre (/*vector<Jugador*> jugadores*/);    // TODO: Fijarse como pasar la referencia a los jugadores de manera correcta.

};


#endif //CONCURRENTES_TP1_MAZO_H
