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
    Semaforo* semaforoConsulta;
    int cantJugadores;

    int verCantCartasPilonDeJugador(int nroJugador);

public:
    Arbitro(Pipe** canalesConJugadores, Semaforo* semaforoConsulta, int cantJugadores);
    ~Arbitro();

    void consultar ();
};


#endif //CONCURRENTES_TP1_ARBITRO_H
