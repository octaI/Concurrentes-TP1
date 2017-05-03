#include "../../include/juego/Jugador.h"



Jugador::Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforosJugadores = semaforosJugadores;
    this->archivo = "../src/juego/Jugador.cpp";
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

void Jugador::analizarCarta(){
    MemoriaComp<int> memoria;

    int estadoVuelta = nroVuelta.crear(archivo,'V');
    int estadoTurno = turnoActual.crear(archivo,'T');
    int estadoMemoria = memoria.crear(archivo, 'J');
    if ( estadoMemoria == SHM_OK ) {
        int resultado = memoria.leer();
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Lei la carta" + to_string(resultado) + " proveniente del jugador " + to_string(turnoActual.leer()));
        //this->semaforosJugadores->wait(this->nro-1); //lo preparo para dormir

        int vueltaAnterior = nroVuelta.leer();
        nroVuelta.escribir(vueltaAnterior+1);
        //this->semaforosJugadores->signal(cantJugadores); //sumo uno para llegar a la barrera//                                                                                                             "numero " + to_string(turnoActual.leer()) );
        cout << "analicé, le mandé la signal al semaforoJugadores" << endl;
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
    int estadoTurno = turnoActual.crear(archivo,'T');
    int estadoVuelta = nroVuelta.crear(archivo,'V');
    unsigned short jugadoresQueDebenEsperar[cantJugadores-1] = {};
    short valores[cantJugadores-1] = {};
    fill_n(valores,cantJugadores-1,1);
    int turno = turnoActual.leer(); // que jugador debe jugar
    //TODO: Ver donde poner el analizarCarta para que realicen la accion.
    while ( tieneCartas() ) {
        esperarTurno(); //aca lo duermo
        if (this->nro != turnoActual.leer()){ //viene con el numero 1, no frena aca
            analizarCarta();
            continue; // ya analizo, arranco el ciclo y que vaya a esperar
        }else {

            // Jugar

            jugarCarta();
            int k = 0;
            for (int j = 0; j < cantJugadores ; j++){
                if ((j+1) != nro){
                    jugadoresQueDebenEsperar[k] = j;
                    k++;
                }
            }
            semaforosJugadores->multiple_signal(jugadoresQueDebenEsperar,valores,cantJugadores-1); //levanto a los 3 espectadores
            analizarCarta();
            while (nroVuelta.leer() < cantJugadores){
                cout << "Estoy esperando a que lean las cartas y soy el jugador" << nro << endl; //espera hasta que lean todos los jugadores
            }
            cout << "Voy a liberar " << endl;
            pasarTurno(); //despierto al proximo jugador
        }


    }
    Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
    semaforosJugadores->eliminar(this->nro -1);
    exit(0);
}

Carta* Jugador::jugarCarta() {
    int estadoVuelta = nroVuelta.crear(archivo,'V');
    nroVuelta.escribir(0); //aca arrancaría el turno
    int estadoTurno = turnoActual.crear(archivo,'T');
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

void Jugador::pasarTurno() {
    int resTurno = turnoActual.crear(archivo,'T');
    int estadoVuelta = nroVuelta.crear(archivo,'V');
    // this->semaforosJugadores->wait(this->nro-1); //lo preparo para dormir
    if (nroVuelta.leer() == (cantJugadores)){
        if ( nro >= cantJugadores ) {
            turnoActual.escribir(1);
            nroVuelta.escribir(0);
            semaforosJugadores->signal(0);
            Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador 1 que es su turno" );
        } else {
            turnoActual.escribir(this->nro+1);
            nroVuelta.escribir(0);
            semaforosJugadores->signal(this->nro);
            Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Ya le avise al jugador " + to_string(nro+1) + " que es su turno" );
        }
        //se resetea el contador

    }
}

void Jugador::esperarTurno() {
    int resTurno = turnoActual.crear(archivo,'T');
    cout << "Estoy en el wait de esperar turno y soy el jugador " << nro << endl;
    this->semaforosJugadores->wait(nro - 1); // si es el jugador 1, pasa de largo y tiene semaforo 0
    //el resto queda varado aca
    //una vez que pasa el jugarCarta salen de aca

}

bool Jugador::tieneCartas() {
    return !cartasEnPilon->empty();
}
