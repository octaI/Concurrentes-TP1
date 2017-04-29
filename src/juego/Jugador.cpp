#include "../../include/juego/Jugador.h"


Jugador::Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforosJugadores = semaforosJugadores;
}

stack<Carta> Jugador::mostrarPilon() {
    return cartasEnPilon; //doy el puntero del stack
}

void Jugador::tomarCarta(Carta carta) {
    cartasEnPilon.push(carta);
}

int Jugador::mostrarNumero() {
    return nro;
}

Jugador::~Jugador() {
    while (!cartasEnPilon.empty()){
        Carta cartaTemp = cartasEnPilon.top();
        delete &cartaTemp;
    }

}

Carta Jugador::jugarCarta() {
    return Carta(1, Palo::Oro);
    /*
    Carta& cartaAJugar = this->cartasEnPilon.top();
    this->cartasEnPilon.pop();
    return cartaAJugar;
    */
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

        // Jugar
        cartasEnPilon.pop();
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya hice mi jugada" );

        pasarTurno();
    }
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
    exit(0);
}

void Jugador::pasarTurno() {
    if ( nro >= cantJugadores ) {
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al primer jugador que ya es su turno" );
        semaforosJugadores->signal(0);
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al primer jugador que es su turno" );
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
    return !cartasEnPilon.empty();
}
