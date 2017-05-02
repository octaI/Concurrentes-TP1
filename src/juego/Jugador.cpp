#include "../../include/juego/Jugador.h"



Jugador::Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores, Semaforo* semaforosEscuchadores) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforosJugadores = semaforosJugadores;
    this->semaforosEscuchadores = semaforosEscuchadores;
}

stack<Carta*>* Jugador::mostrarPilon() {
    return cartasEnPilon; //doy el puntero del stack
}

void Jugador::tomarCarta(Carta* carta) {
    cartasEnPilon->push(carta);
}

void Jugador::obtenerPilon(stack<Carta*>* pilon){
    cartasEnPilon = pilon;
}

int Jugador::mostrarNumero() {
    return nro;
}

Jugador::~Jugador() {
    while (!cartasEnPilon->empty()){
        Carta* cartaTemp = cartasEnPilon->top();
        delete cartaTemp;
    }

}

Carta* Jugador::jugarCarta() {
    Carta* cartaAJugar = this->cartasEnPilon->top();
    this->cartasEnPilon->pop();

    //Memoria compartida:
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> memoria;
    int estadoMemoria = memoria.crear(archivo, 'J');

    if (estadoMemoria == SHM_OK) {
        cout << "Jugador " << nro << ": Escribo la carta en MEM COMP con Nro: " << cartaAJugar->getNumero()
             << " y Palo: " << cartaAJugar->getPalo() << endl;
        memoria.escribir(cartaAJugar->getNumero());
        // TODO: Falta liberar memoria.
        //memoria.liberar ();
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
    }

    return cartaAJugar;
}

void Jugador::analizarCarta(){
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

Jugador &Jugador::operator=(const Jugador &origen) {
    this->nro = origen.nro;
    this->cantJugadores = origen.cantJugadores;
    this->cartasEnPilon = origen.cartasEnPilon;
    this->semaforosJugadores = origen.semaforosJugadores;
    return *this;
}

void Jugador::jugar() {
    //TODO: Ver donde poner el analizarCarta para que realicen la accion.
    while ( tieneCartas() ) {
        esperarTurno();

        // Jugar
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "Tengo " + to_string(cartasEnPilon->size()) + " cartas" );
        jugarCarta();
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya hice mi jugada" );

        pasarTurno();
    }
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
    semaforosJugadores->eliminar();
    exit(0);
}

void Jugador::pasarTurno() {
    if ( nro >= cantJugadores ) {
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al jugador 1 que ya es su turno" );
        semaforosJugadores->signal(0);
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador 1 que es su turno" );
    } else {
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al jugador " + to_string(nro+1) + " que ya es su turno" );
        semaforosJugadores->signal(nro);
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador " + to_string(nro+1) + " que es su turno" );
    }
}

void Jugador::esperarTurno() {
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Voy a esperar a que sea mi turno para jugar" );
    this->semaforosJugadores->wait(nro - 1);
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya es mi turno" );
}

bool Jugador::tieneCartas() {
    return !cartasEnPilon->empty();
}
