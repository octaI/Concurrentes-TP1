
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
#include "../../include/ipc/MemoriaCompartida.h"
#include "../../include/ipc/MemoriaComp.h"

using namespace std;

class Jugador {

private:
    int nro;
    int cantJugadores;
    Semaforo* semaforosJugadores;
    Semaforo* semaforoArbitro;
    string archivo;
    MemoriaComp<int> turnoActual;
    MemoriaComp<int> nroVuelta;
    MemoriaComp<int> finJuego;
    unsigned short arregloOtrosJugadores[];

    stack<Carta*>* cartasEnPilon;
    stack<Carta*>* pilonAuxiliar;
    void pasarTurno();
    void esperarTurno();
    void analizarCarta();
    bool esRondaEspecial(int nroUltimaCarta, int nroAnteultimaCarta);
    bool esRondaEscuchar(int nroUltimaCarta);
    bool esRondaVer(int nroUltimaCarta);
    void levantarPilonCentral();
    void escribirNroJugador();

    void limpiarPilon(stack<Carta*>* pilon);
public:
    Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores, Semaforo* semaforoArbitro);
    ~Jugador();

    Jugador& operator= (const Jugador& origen);

    void jugar ();
    stack<Carta*>* mostrarPilon();
    Carta* jugarCarta ();
    int mostrarNumero();
    void tomarCarta (Carta* carta);

    void obtenerPilon(stack<Carta*>* pilon);

    bool tieneCartas();
};


#endif //CONCURRENTES_TP1_JUGADOR_H
