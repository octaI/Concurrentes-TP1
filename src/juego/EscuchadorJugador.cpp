#include "../../include/juego/EscuchadorJugador.h"
#include "../../include/ipc/MemoriaComp.h"

EscuchadorJugador::EscuchadorJugador(int nro, int cantJugadores, Semaforo *semaforoEscuchador) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforoEscuchador = semaforoEscuchador;
}

void EscuchadorJugador::analizarCarta(){
    semaforoEscuchador->wait(nro-1); //espero hasta que me indiquen que debo escuchar
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> memoria;
    int estadoMemoria = memoria.crear(archivo, 'J');
    if ( estadoMemoria == SHM_OK ) {
        int resultado = memoria.leer() ;
        cout << "Jugador " << nro << ": Leo la carta desde MEM COMP con Nro: " << resultado << endl;
        // TODO: Falta liberar memoria
        //memoria . liberar () ;
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
    }
}
