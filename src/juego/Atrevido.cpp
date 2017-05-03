
#include "../../include/juego/Atrevido.h"

Atrevido::~Atrevido() {
}

Atrevido::Atrevido(int nroJugadores) {
    iniciarJugadores(nroJugadores);
}

void Atrevido::iniciarJugadores(const int nroJugadores) {
    int cant_vueltas = 0;
    Logger::getInstance() -> info ( "Atrevido.cpp", "Van a jugar " + to_string(nroJugadores) + " jugadores" );
    Logger :: getInstance() -> debug( "Atrevido.cpp", "Soy el PADRE Atrevido con PID: " + to_string(getpid()));

    // Semaforos para administrar turnos
    int valoresInicialesJugadores [nroJugadores] = {};
    int valoresInicialesEscuchadores [nroJugadores] = {};
    int valoresInicialesCreacion [nroJugadores] = {};
    int valoresListeners [nroJugadores] = {};
    std::fill_n(valoresInicialesJugadores, nroJugadores, 0);    // inicializados en 0
    Semaforo semaforosJugadores ( "Atrevido.cpp", 'j', valoresInicialesJugadores, nroJugadores );
    Semaforo semaforosEscuchadores("Atrevido.cpp",'e',valoresInicialesEscuchadores,nroJugadores);
    Semaforo semaforosCreacion("Atrevido.cpp",'c',valoresInicialesCreacion,nroJugadores);
    Semaforo semaforosListeners("Atrevido.cpp",'l',valoresListeners,nroJugadores);

    // Semaforos para manejar el analisis de la ultima carta tirada para cada jugador
    int valoresInicialesAnalisis [nroJugadores] = {};
    std::fill_n(valoresInicialesAnalisis, nroJugadores, 0);    // inicializados en 0
    Semaforo semaforosAnalisis ( "Atrevido.cpp", 'a', valoresInicialesAnalisis, nroJugadores );

    asignarTurnoInicial();

    unsigned short  i;
    pid_t pid;
    pid_t pidListener;
    Mazo* mazo = new Mazo ();
    vector<stack<Carta*>*>* pilones = new vector<stack<Carta*>*> (nroJugadores);
    generarPilones(mazo, nroJugadores, pilones);
    Jugador* jugador;
    EscuchadorJugador* listenerJugador;
    semaforosCreacion.signal(0);
    pid_t pid1 = fork();
    if (pid1 < 0){
        Logger::getInstance()->error("Atrevido.cpp",
                                     "Error al crear proceso hijo para el jugador " + to_string(1));
        exit(1);
    } else if (pid1 == 0){ // es el hijo
        Logger::getInstance()->debug("Atrevido.cpp",
                                     "Se creo correctamente el proceso para el jugador " + to_string(1) +
                                     " con pid " + to_string(getpid())
                                     + " (padre: " + to_string(getppid()) + ")");
        jugador = new Jugador( 1, nroJugadores, &semaforosJugadores, &semaforosAnalisis);
        jugador->obtenerPilon(pilones->at(0));
        semaforosCreacion.signal(1);
        cout<< "Soy "<< getpid() << "y me voy a habilitar el primer turno\n";
        semaforosListeners.wait(0,nroJugadores);
        semaforosJugadores.signal(0);
        cout << "Soy "<< getpid() << "y ya me habilite el turno\n";
    } else{

        for (i = 1; i < nroJugadores; i++) {
            semaforosCreacion.wait(i,1);
            pid = fork ();
            if( pid < 0 ) {
                Logger::getInstance()->error("Atrevido.cpp",
                                             "Error al crear proceso hijo para el jugador " + to_string(i + 1));
                exit(1);
            } else if ( pid == 0 ) {
                Logger::getInstance()->debug("Atrevido.cpp",
                                             "Se creo correctamente el proceso para el jugador " + to_string(i + 1) +
                                             " con pid " + to_string(getpid())
                                             + " (padre: " + to_string(getppid()) + ")");
                jugador = new Jugador(i + 1, nroJugadores, &semaforosJugadores, &semaforosAnalisis);
                jugador->obtenerPilon(pilones->at(i));

                semaforosCreacion.signal(i+1);
                semaforosListeners.signal(0);

                break;
            }

        }
    }

    if ( pid == 0 || pid1 == 0 ) {
        cout << "Voy a empezar a jugar \n";
        cout << "La barrera funca \n";
        jugador->jugar();
        delete jugador;
    } else {
        wait(NULL);
        delete mazo;
        exit(0);
    }
}

void Atrevido::generarPilones(Mazo* mazo, int cantJugadores, vector<stack<Carta*>*>* pilones) {
    int cartasPorJugador = mazo->cantidadDeCartas() / cantJugadores;
    for (int j = 0; j < cantJugadores; j++){
        pilones->at(j) = new stack<Carta*>();
        for (int i = 0; i < cartasPorJugador; i++) {
            pilones->at(j)->push(mazo->tomarCarta());
            cout << " - Cartas en el mazo: " << mazo->cantidadDeCartas() << endl;
        }
    }
}

void Atrevido::asignarTurnoInicial() {
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> memoria;
    int estadoMemoria = memoria.crear(archivo, 'T');
    if ( estadoMemoria == SHM_OK ) {
        memoria.escribir(1) ;
        cout << "Atrevido.cpp: Escribo en MEM COMP que es el turno inicial (jugador 1)" << endl;
    } else {
        cout << "ERROR en memoria compartida. Error nro: " << estadoMemoria << endl;
    }
}

