
#ifndef CONCURRENTES_TP1_JUGADOR_H
#define CONCURRENTES_TP1_JUGADOR_H

#include <vector>
#include "Carta.h"
#include "Mazo.h"

using namespace std;

class Jugador {

private:
    vector<Carta*> cartasEnMano = vector<Carta*> (CANT_CARTAS);

public:
    Jugador();
    ~Jugador();
    Jugador(const Jugador& origen);
    Jugador& operator= (const Jugador& origen);

    vector<Carta> mostrarMano ();
    Carta& jugarCarta ();
    void tomarCarta (Carta& carta);
};


#endif //CONCURRENTES_TP1_JUGADOR_H
