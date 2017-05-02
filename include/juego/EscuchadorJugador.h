
#ifndef CONCURRENTES_TP1_ESCUCHADORJUGADOR_H
#define CONCURRENTES_TP1_ESCUCHADORJUGADOR_H

#include <stdio.h>
#include <iostream>
#include <string>
#include "../ipc/Semaforo.h"

using namespace std;

class EscuchadorJugador {

private:
    int nro;
    int cantJugadores;
    Semaforo* semaforoEscuchador;

public:
    EscuchadorJugador(int nro, int cantJugadores, Semaforo* semaforoEscuchador);
    void analizarCarta();
};




#endif //CONCURRENTES_TP1_ESCUCHADORJUGADOR_H
