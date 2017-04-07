
#ifndef CONCURRENTES_TP1_JUGADOR_H
#define CONCURRENTES_TP1_JUGADOR_H

#include <vector>
#include "Carta.h"

using namespace std;

class Jugador {

private:
    vector<Carta&> cartasEnMano;

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
