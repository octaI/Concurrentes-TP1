
#ifndef CONCURRENTES_TP1_JUGADOR_H
#define CONCURRENTES_TP1_JUGADOR_H

#include <stack>
#include <string>
#include <iostream>
#include "Carta.h"
#include "Mazo.h"
#include "../ipc/Pipe.h"
#include "../ipc/Semaforo.h"
#include "../../include/logger/Logger.h"

using namespace std;

class Jugador {

private:
    int nro;
    int cantJugadores;
    Semaforo* semaforosJugadores;
    stack<Carta*> cartasEnPilon;

    void pasarTurno();
    void esperarTurno();

public:
    Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores);
    ~Jugador();
    Jugador& operator= (const Jugador& origen);

    void jugar ();

    stack<Carta*> mostrarPilon();
    Carta* jugarCarta ();
    int mostrarNumero();
    void tomarCarta (Carta* carta);

    bool tieneCartas();
};


#endif //CONCURRENTES_TP1_JUGADOR_H
