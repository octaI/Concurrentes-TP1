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
    while ( tieneCartas() ) {
        esperarTurno();
        if ( esMiTurno() ) {
            // Jugar
            Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "Tengo " + to_string(cartasEnPilon->size()) + " cartas" );
            jugarCarta();
            Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya hice mi jugada" );
            notificarJugada();

            analizarCarta();

            pasarTurno();
        } else {
            analizarCarta();
        }
    }
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
    semaforosJugadores->eliminar();
    exit(0);
}

void Jugador::pasarTurno() {
    if ( nro >= cantJugadores ) {
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al jugador 1 que ya es su turno" );
        semaforosJugadores->signal(0);
        asignarTurno(1);
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador 1 que es su turno" );
    } else {
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al jugador " + to_string(nro+1) + " que ya es su turno" );
        semaforosJugadores->signal(nro);
        asignarTurno(nro + 1);
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

bool Jugador::esMiTurno() {
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> memoria;
    int estadoMemoria = memoria.crear(archivo, 'T');
    if ( estadoMemoria == SHM_OK ) {
        int nroJugadorTurno = memoria.leer() ;
        cout << "Jugador " << nro << ": Leo desde MEM COMP que es el turno del jugador con nro: " << nroJugadorTurno << endl;
        return nroJugadorTurno == nro;
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
        return false;
    }
}

void Jugador::asignarTurno(int nroJugador) {
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> memoria;
    int estadoMemoria = memoria.crear(archivo, 'T');
    if ( estadoMemoria == SHM_OK ) {
        memoria.escribir(nroJugador) ;
        cout << "Jugador " << nro << ": Escribo en MEM COMP que es el turno del jugador con nro: " << nroJugador << endl;
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
    }
}

void Jugador::notificarJugada() {
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar a todos los jugadores que ya realice mi jugada y pueden analizar la carta" );
    unsigned short nsem [cantJugadores];
    for (unsigned short i = 0; i < cantJugadores; i++) {
        nsem [i] = i;
    }
    short count [cantJugadores];
    for (short j = 0; j < cantJugadores; j++) {
        if ( j == (nro - 1) )
            count [j] = 0;
        else
            count [j] = 1;
    }
    semaforosJugadores->multiple_signal(nsem, count, cantJugadores);
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise a los jugadores que revisen la carta que jugue" );
}
