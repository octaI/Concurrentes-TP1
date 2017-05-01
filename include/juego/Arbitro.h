#ifndef CONCURRENTES_TP1_ARBITRO_H
#define CONCURRENTES_TP1_ARBITRO_H

#include <vector>
#include "Carta.h"
#include "Jugador.h"

using namespace std;

class Arbitro {

private:
    static const int BUFFSIZE = 2;

    Pipe** canalesConJugadores;
    int cantJugadores;

public:
    Arbitro(Pipe** canalesConJugadores, int cantJugadores);
    ~Arbitro();

    int verCantCartasPilonDeJugador(int nroJugador);

};


#endif //CONCURRENTES_TP1_ARBITRO_H
