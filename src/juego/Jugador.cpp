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
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "Escribo la carta con nro " + to_string(cartaAJugar->getNumero()) );
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
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "Leo la carta con nro " + to_string(resultado) );
        // TODO: Falta liberar memoria
        //memoria . liberar () ;
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
    }
    semaforosJugadores->signal(nro-1);
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
            notificarJugada();

            analizarCarta();
            esperarAnalisisDeTodosLosJugadores();

            pasarTurno();
        } else {
            analizarCarta();
            semaforosJugadores->signal(nro - 1);
        }
    }
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
    semaforosJugadores->eliminar();
    exit(0);
}

void Jugador::pasarTurno() {
    if ( nro >= cantJugadores ) {
        semaforosJugadores->signal(0);
        asignarTurno(1);
    } else {
        semaforosJugadores->signal(nro);
        asignarTurno(nro + 1);
    }
}

void Jugador::esperarTurno() {
    this->semaforosJugadores->wait(nro - 1);
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
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Es el turno del jugador " + to_string(nroJugadorTurno) );
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
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le asigno el siguiente turno al jugador " + to_string(nroJugador) );
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
    }
}

void Jugador::notificarJugada() {
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar a todos los jugadores que ya realice mi jugada y pueden analizar la carta" );
    unsigned short nsem [cantJugadores - 1];
    int k = 0;
    for (unsigned short i = 0; i < cantJugadores; i++) {
        if ( i != (nro - 1) )
            nsem [i - k] = i;
        else
            k++;
    }
    short count [cantJugadores - 1];
    int h = 0;
    for (short j = 0; j < cantJugadores; j++) {
        if ( j != (nro - 1) )
            count [j - h] = 1;
        else
            h++;
    }
    semaforosJugadores->multiple_signal(nsem, count, cantJugadores - 1);
}

void Jugador::esperarAnalisisDeTodosLosJugadores() {
    unsigned short nsem [cantJugadores - 1];
    int k = 0;
    for (unsigned short i = 0; i < cantJugadores; i++) {
        if ( i != (nro - 1) )
            nsem [i - k] = i;
        else
            k++;
    }
    short count [cantJugadores - 1];
    int h = 0;
    for (short j = 0; j < cantJugadores; j++) {
        if ( j != (nro - 1) )
            count [j - h] = 1;
        else
            h++;
    }
    semaforosJugadores->multiple_wait(nsem, count, cantJugadores - 1);
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Todos los jugadores analizaron mi carta jugada" );
}
