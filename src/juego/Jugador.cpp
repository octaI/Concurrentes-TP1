#include "../../include/juego/Jugador.h"



Jugador::Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforosJugadores = semaforosJugadores;
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
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> turnoActual;
    int estadoTurno = turnoActual.crear(archivo,'T');
    int turno = turnoActual.leer(); // que jugador debe jugar
    cout << "Soy el jugador : " << this->nro << "y es el turno de " << turno << endl;
    MemoriaComp<int> memoria;
    int estadoMemoria = memoria.crear(archivo, 'J');

    Carta* cartaAJugar = this->cartasEnPilon->top();
    this->cartasEnPilon->pop();

    //Memoria compartida:
    if (estadoMemoria == SHM_OK) {
        cout << "Jugador " << nro << ": Escribo la carta en MEM COMP con Nro: " << cartaAJugar->getNumero()
             << " y Palo: " << cartaAJugar->getPalo() << endl;
        memoria.escribir(cartaAJugar->getNumero());
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "ESCRIBO la carta a MEM COMP con Nro: " + to_string(cartaAJugar->getNumero()) + " del Palo " + to_string(cartaAJugar->getPalo()) + " del JUGADOR " + to_string(turnoActual.leer()));
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
    MemoriaComp<int> turnoActual;
    int estadoTurno = turnoActual.crear(archivo,'T');
    int estadoMemoria = memoria.crear(archivo, 'J');
    if ( estadoMemoria == SHM_OK ) {
        int resultado = memoria.leer() ;
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "Leo la carta desde MEM COMP con Nro: " + to_string(resultado) + " del JUGADOR " + to_string(turnoActual.leer()));
        this->semaforosJugadores->signal(cantJugadores);
        cout << "Jugador " << nro << ": Le subi al semaforo de turno" << endl;
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
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> turnoActual;
    int estadoTurno = turnoActual.crear(archivo,'T');
    int turno = turnoActual.leer(); // que jugador debe jugar
    //TODO: Ver donde poner el analizarCarta para que realicen la accion.
    while ( tieneCartas() ) {
        turno = turnoActual.leer(); // que jugador debe jugar
        if (this->nro != turno){
            esperarTurno();
            cout << "Voy a analizar la carta porque soy el jugador : " << this->nro << " es el turno de jugar de " << turno << "\n";
            analizarCarta();
        }else {

            // Jugar
            Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "Tengo " + to_string(cartasEnPilon->size()) + " cartas" );
            jugarCarta();
            Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya hice mi jugada" );
            for (int j = 0; j < cantJugadores ; j++){
                if ((j+1) != nro){
                    cout << "Soy el jugador : " << this->nro << " y le digo al jugador " << j + 1 << " que puede leer " << endl;
                    semaforosJugadores->signal(j);//le doy permiso a los demas jugadores para que lean
                }
            }
            pasarTurno();
            Logger::getInstance() -> debug ("Jugador " + to_string(nro), " Ya pase el turno");
        }


    }
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
    semaforosJugadores->eliminar();
    exit(0);
}

void Jugador::pasarTurno() {
    semaforosJugadores->wait(cantJugadores,cantJugadores-1); // espero a que pasen todos
    string archivo("../src/juego/Jugador.cpp");
    cout << "Soy el jugador : " << this->nro << "y le voy a pasar el turno a " << this->nro + 1 << endl;
    MemoriaComp<int> turnoActual;
    int resTurno = turnoActual.crear(archivo,'T');
    if ( nro >= cantJugadores ) {
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al jugador 1 que ya es su turno" );
        turnoActual.escribir(1);
        semaforosJugadores->signal(0);
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador 1 que es su turno" );
    } else {
        cout << "Voy a escribir" << this->nro+1 << " y soy el jugador " << this->nro << endl;
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Le voy a avisar al jugador " + to_string(nro+1) + " que ya es su turno" );
        turnoActual.escribir(this->nro+1);
        cout << "El turno escrito ahora es " << turnoActual.leer() << endl;
        semaforosJugadores->signal(this->nro);
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador " + to_string(nro+1) + " que es su turno" );
    }
}

void Jugador::esperarTurno() {
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> turnoActual;
    int resTurno = turnoActual.crear(archivo,'T');

    cout << "Soy el jugador " << this->nro << " y me toca esperar al jugador " << turnoActual.leer() <<  endl;
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Voy a esperar a que sea mi turno para jugar" );
    this->semaforosJugadores->wait(nro - 1);
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya es mi turno" );
}

bool Jugador::tieneCartas() {
    return !cartasEnPilon->empty();
}
