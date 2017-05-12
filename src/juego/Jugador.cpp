#include "../../include/juego/Jugador.h"



Jugador::Jugador(int nro, int cantJugadores, Semaforo* semaforosJugadores, Semaforo* semaforoArbitro) {
    this->nro = nro;
    this->cantJugadores = cantJugadores;
    this->semaforosJugadores = semaforosJugadores;
    this->semaforoArbitro = semaforoArbitro;
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

    // Memoria para que el arbitro consulte
    MemoriaComp<int> memoriaCantCartas;
    char buffer [1];
    int estadoMemoriaCantCartas = memoriaCantCartas.crear( archivo, (char) sprintf(buffer, "%d", nro) );
    if (estadoMemoriaCantCartas == SHM_OK) {
        int cantCartas = (int) cartasEnPilon->size();
        memoriaCantCartas.escribir (cantCartas);
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "ESCRIBO la cant de cartas del pilon a MEM COMP: " + to_string(cantCartas) );
    } else {
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para la cantidad de cartas del pilon del jugador. Nro error: " + to_string(estadoMemoriaCantCartas) );
    }
}

int Jugador::mostrarNumero() {
    return nro;
}

Jugador::~Jugador() {
    //TODO: DELETEAR TODO BIEN aca esta el free con error que tira
    delete cartasEnPilon;

    delete pilonAuxiliar;


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

        //Obtengo el numero de la anteultima carta del pilon auxiliar:
        int nroAnteultimaCarta;
        Carta* anteultimaCarta;
        if (!pilonAuxiliar->empty()){
            anteultimaCarta = pilonAuxiliar->top();
            nroAnteultimaCarta = anteultimaCarta->getNumero();
        }
        else {
            nroAnteultimaCarta = 0;
        }

        // Creo la ultima carta jugada, que lei de memoria compartida:
        Carta* ultimaCartaJugada = new Carta(resultado, Palo(palo));
        pilonAuxiliar->push(ultimaCartaJugada);
        cout << "Jugador NRO: " << nro << " con PILON PRINCIPAL tamanio = " << cartasEnPilon->size() << endl;
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Lei la carta nro: " +
                to_string(resultado) + " de palo: " + to_string(palo) + " proveniente del jugador " +
                to_string(turnoActual.leer()));

        ultimaCartaJugada->accion(nro, nroAnteultimaCarta);


        //Analizo si fui el ultimo y me llevo el pilon:
        semaforosJugadores->wait(cantJugadores);
        int vueltaAnterior = nroVuelta.leer();
        nroVuelta.escribir(nroVuelta.leer() + 1);
        semaforosJugadores->signal(cantJugadores);
        bool rondaEspecial = esRondaEspecial(resultado, nroAnteultimaCarta);
        if (vueltaAnterior == (cantJugadores - 1) && rondaEspecial) {
            cout << "ACABA DE TERMINAR UNA RONDA ESPECIAL - SE ACTUALIZAN PILONES" << endl;
            Logger::getInstance()->debug("JUEGO", "ACABA DE TERMINAR UNA RONDA ESPECIAL");
            cout << endl;
            while (!pilonAuxiliar->empty()) {
                Carta *carta = pilonAuxiliar->top();
                pilonAuxiliar->pop();
                cartasEnPilon->push(carta);
            }
            cout << "El JUGADOR " << nro << " se lleva las cartas de esta ronda especial" << endl;
            Logger::getInstance()->debug("Jugador :"+to_string(nro), "Se llevo las cartas de la ronda especial");
        } else if (rondaEspecial){
            while (!pilonAuxiliar->empty()) {
                Carta *carta = pilonAuxiliar->top();
                pilonAuxiliar->pop();
                delete carta;
            }
        }

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
    this->semaforoArbitro = semaforoArbitro;
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
    while ( tieneCartas() && (finJuego.leer() == 0) ) {
        esperarTurno(); //aca lo duermo
        if (this->nro != turnoActual.leer() && (finJuego.leer() == 0)){ //viene con el numero 1, no frena aca
            analizarCarta();
            continue; // ya analizo, arranco el ciclo y que vaya a esperar
        }else if (finJuego.leer() == 0) {

            // Jugar
            Carta* jugada = jugarCarta();

            // Avisar al arbitro que puede consultar cantidad de cartas de los jugadores
            semaforoArbitro->signal();

            elegirSemaforosParaModificar(jugadoresQueDebenEsperar,cantJugadores,nro);
            semaforosJugadores->multiple_signal(jugadoresQueDebenEsperar,valores,cantJugadores-1); //levanto a los 3 espectadores
            semaforosJugadores->signal(cantJugadores);//habilito a que alguien pueda escribir la cant de vueltas
            analizarCarta();
            while (nroVuelta.leer() < cantJugadores){
                continue; //barrera casera para esperar que todos hayan leido
            }
            delete jugada;
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
    semaforosJugadores->signal(finJuego.leer(),cantJugadores-1);
    if (nro != finJuego.leer()){
        Logger::getInstance() -> debug ( "Jugador " + to_string(nro), "Perdi el juego" );
        semaforosJugadores->wait(finJuego.leer(),1);
    } else {
        semaforosJugadores->barrier(finJuego.leer());
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

    // Memoria para que el arbitro consulte
    MemoriaComp<int> memoriaCantCartas;
    char buffer [1];
    int estadoMemoriaCantCartas = memoriaCantCartas.crear( archivo, (char) sprintf(buffer, "%d", nro) );

    Carta* cartaAJugar = this->cartasEnPilon->top();
    this->cartasEnPilon->pop();
    cout << "Jugador " << nro << ": Tiro la carta de número " << cartaAJugar->getNumero() << " y palo " << cartaAJugar->getPalo() << " ---------------------------- "<< endl ;

    //Memoria compartida:
    if (estadoMemoriaNro == SHM_OK && estadoMemoriaPalo == SHM_OK ) {
        memoriaNro.escribir(cartaAJugar->getNumero());
        memoriaPalo.escribir(cartaAJugar->getPalo());
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "ESCRIBO la carta a MEM COMP con Nro: " + to_string(cartaAJugar->getNumero()) + " del Palo " + to_string(cartaAJugar->getPalo()) + " del JUGADOR " + to_string(turnoActual.leer()));
    } else {
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para el numero de carta. Nro error: " + to_string(estadoMemoriaNro) );
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para el palo de la carta. Nro error: " + to_string(estadoMemoriaPalo) );
    }

    if (estadoMemoriaCantCartas == SHM_OK) {
        int cantCartas = (int) cartasEnPilon->size();
        memoriaCantCartas.escribir (cantCartas);
        Logger::getInstance () -> debug ( "Jugador " + to_string(nro), "ESCRIBO la cant de cartas del pilon a MEM COMP: " + to_string(cantCartas) );
    } else {
        Logger :: getInstance() -> error ( "Jugador " + to_string(nro), "No se pudo crear la memoria compartida para la cantidad de cartas del pilon del jugador. Nro error: " + to_string(estadoMemoriaCantCartas) );
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
