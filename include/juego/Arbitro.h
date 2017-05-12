#ifndef CONCURRENTES_TP1_ARBITRO_H
#define CONCURRENTES_TP1_ARBITRO_H

#include <vector>
#include "Carta.h"
#include "Jugador.h"

using namespace std;

class Arbitro {

private:

    Semaforo* semaforoArbitro;
    int cantJugadores;

    MemoriaComp<int*> shMemCantCartasJugadores;
    MemoriaComp<int> shMemFinJuego;

    void iniciar();
    void consultarJugadores();
    bool terminoPartida();

public:
    Arbitro( Semaforo* semaforoArbitro, int cantJugadores );
    ~Arbitro();
};


#endif //CONCURRENTES_TP1_ARBITRO_H
