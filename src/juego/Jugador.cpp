#include "../../include/juego/Jugador.h"



Jugador::Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforosJugadores = semaforosJugadores;
    this->archivo = "../src/juego/Jugador.cpp";
    this->pilonAuxiliar = new stack<Carta*>();
}

void elegirSemaforosParaModificar(unsigned short arreglo[], int cantJugadores, int nro){
    int k = 0;
    for (int j = 0; j < cantJugadores ; j++){
        if ((j+1) != nro){
            arreglo[k] = j;
            k++;
        }
    }
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
    //TODO: DELETEAR TODO BIEN aca esta el free con error que tira
    /*limpiarPilon(cartasEnPilon);
    delete cartasEnPilon;

    limpiarPilon(pilonAuxiliar);
    delete pilonAuxiliar;
     */

}

void Jugador::limpiarPilon(stack<Carta*>* pilon){
    while (!pilon->empty()){
        Carta* cartaTemp = pilon->top();
        delete cartaTemp;
    }
}

void Jugador::analizarCarta(){

    int estadoVuelta = nroVuelta.crear(archivo,'V');
    int estadoTurno = turnoActual.crear(archivo,'T');

    MemoriaComp<int> memoriaNro;
    int estadoMemoriaNro = memoriaNro.crear(archivo, 'J');
    MemoriaComp<int> memoriaPalo;
    int estadoMemoriaPalo = memoriaPalo.crear(archivo, 'P');


    if ( estadoMemoriaNro == SHM_OK && estadoMemoriaPalo == SHM_OK) {
        int resultado = memoriaNro.leer();
        int palo = memoriaPalo.leer();

        //Obtengo la anteultima carta del pilon auxiliar:
        int nroAnteultimaCarta;
        Carta* anteultimaCarta;
        if (!pilonAuxiliar->empty()){
            anteultimaCarta = pilonAuxiliar->top();
            nroAnteultimaCarta = anteultimaCarta->getNumero();
        }
        else {
            anteultimaCarta = NULL;
            nroAnteultimaCarta = 0;
        }

        // Creo la ultima carta jugada, que lei de memoria compartida:
        Carta* ultimaCartaJugada = new Carta(resultado, Palo(palo));
        pilonAuxiliar->push(ultimaCartaJugada);
        cout << "Jugador NRO: " << nro << " con PILON AUX tamanio = " << pilonAuxiliar->size() << endl;
        cout << "Jugador NRO: " << nro << " con PILON PRINCIPAL tamanio = " << cartasEnPilon->size() << endl;

        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Lei la carta nro: " +
                to_string(resultado) + " de palo: " + to_string(palo) + " proveniente del jugador " +
                to_string(turnoActual.leer()));

        ultimaCartaJugada->accion(nro, nroAnteultimaCarta);

        //this->semaforosJugadores->wait(this->nro-1); //lo preparo para dormir

        int vueltaAnterior = nroVuelta.leer();
        nroVuelta.escribir(vueltaAnterior + 1);
        //cout << "Jugador NRO: " << nro << " con VUELTA ANTERIOR = " << vueltaAnterior << endl;

        bool rondaEspecial = esRondaEspecial(resultado, nroAnteultimaCarta);
        if (vueltaAnterior == (cantJugadores - 1) && rondaEspecial) {
            cout << "Estoy ACA FUE RONDA ESPECIAL" << endl;
            cout << endl;
            while (!pilonAuxiliar->empty()) {
                Carta *carta = pilonAuxiliar->top();
                pilonAuxiliar->pop();
                cartasEnPilon->push(carta);
            }
        } else if (rondaEspecial){
            while (!pilonAuxiliar->empty()) {
                Carta *carta = pilonAuxiliar->top();
                pilonAuxiliar->pop();
                delete carta;
            }
        }

        //this->semaforosJugadores->signal(cantJugadores); //sumo uno para llegar a la barrera//                                                                                                             "numero " + to_string(turnoActual.leer()) );
        // TODO: Falta liberar memoria
        //memoria . liberar () ;
    } else {
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para el numero de carta. Nro error: " + to_string(estadoMemoriaNro) );
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para el palo de la carta. Nro error: " + to_string(estadoMemoriaPalo) );
    }
}

bool Jugador::esRondaEspecial(int nroUltimaCarta, int nroAnteultimaCarta){
    if (nroUltimaCarta == 7 || nroUltimaCarta == nroAnteultimaCarta){
        return true;
    }
    return false;
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
    finJuego.crear(archivo,'E');
    unsigned short jugadoresQueDebenEsperar[cantJugadores-1] = {};
    short valores[cantJugadores-1] = {};
    fill_n(valores,cantJugadores-1,1);
    int turno = turnoActual.leer(); // que jugador debe jugar
    //TODO: Ver donde poner el analizarCarta para que realicen la accion.
    while ( tieneCartas() && (finJuego.leer() == 0) ) {
        esperarTurno(); //aca lo duermo
        if (this->nro != turnoActual.leer() && (finJuego.leer() == 0)){ //viene con el numero 1, no frena aca
            analizarCarta();
            continue; // ya analizo, arranco el ciclo y que vaya a esperar
        }else if (finJuego.leer() != 1) {

            // Jugar

            jugarCarta();

            elegirSemaforosParaModificar(jugadoresQueDebenEsperar,cantJugadores,nro);
            semaforosJugadores->multiple_signal(jugadoresQueDebenEsperar,valores,cantJugadores-1); //levanto a los 3 espectadores
            analizarCarta();
            while (nroVuelta.leer() < cantJugadores){
                //cout << "Estoy esperando a que lean las cartas y soy el jugador" << nro << endl; //espera hasta que lean todos los jugadores
            }

            if (!tieneCartas()){
                finJuego.escribir(nro);
                Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "No tengo mas cartas para jugar" );
                semaforosJugadores->multiple_signal(jugadoresQueDebenEsperar,valores,cantJugadores-1);
                break;
            } else{
                pasarTurno(); //despierto al proximo jugador

            }
        }


    }
    //elegirSemaforosParaModificar(jugadoresQueDebenEsperar,cantJugadores,nro);
    semaforosJugadores->signal(finJuego.leer(),cantJugadores-1);
    if (nro != finJuego.leer()){
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Perdi el juego" );
        semaforosJugadores->wait(finJuego.leer(),1);
    } else {
        semaforosJugadores->barrier(finJuego.leer());
        semaforosJugadores->eliminar(this->nro -1);
        exit(0);
    }
}

Carta* Jugador::jugarCarta() {
    int estadoVuelta = nroVuelta.crear(archivo,'V');
    nroVuelta.escribir(0); //aca arrancaría el turno
    int estadoTurno = turnoActual.crear(archivo,'T');

    //Memorias para las cartas:
    MemoriaComp<int> memoriaNro;
    int estadoMemoriaNro = memoriaNro.crear(archivo, 'J');
    MemoriaComp<int> memoriaPalo;
    int estadoMemoriaPalo = memoriaPalo.crear(archivo, 'P');

    Carta* cartaAJugar = this->cartasEnPilon->top();
    this->cartasEnPilon->pop();
    //TODO: delete carta deberia ir aca o no. Sino perdes la referencia.
    cout << "Jugador " << nro << ": Tiro la carta de número " << cartaAJugar->getNumero() << " y palo " << cartaAJugar->getPalo() << " ---------------------------- "<< endl ;

    //Memoria compartida:
    if (estadoMemoriaNro == SHM_OK && estadoMemoriaPalo == SHM_OK ) {
        memoriaNro.escribir(cartaAJugar->getNumero());
        memoriaPalo.escribir(cartaAJugar->getPalo());
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "ESCRIBO la carta a MEM COMP con Nro: " + to_string(cartaAJugar->getNumero()) + " del Palo " + to_string(cartaAJugar->getPalo()) + " del JUGADOR " + to_string(turnoActual.leer()));
        // TODO: Falta liberar memoria.
        //memoria.liberar ();
    } else {
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para el numero de carta. Nro error: " + to_string(estadoMemoriaNro) );
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para el palo de la carta. Nro error: " + to_string(estadoMemoriaPalo) );
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
    this->semaforosJugadores->wait(nro - 1); // si es el jugador 1, pasa de largo y tiene semaforo 0
    //el resto queda varado aca
    //una vez que pasa el jugarCarta salen de aca

}

bool Jugador::tieneCartas() {
    return !cartasEnPilon->empty();
}
