
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
    int valoresInicialesCreacion [nroJugadores] = {};
    std::fill_n(valoresInicialesJugadores, nroJugadores, 0);    // inicializados en 0
    Semaforo semaforosJugadores ( "Atrevido.cpp", 'j', valoresInicialesJugadores, nroJugadores );
    Semaforo semaforosCreacion("Atrevido.cpp",'c',valoresInicialesCreacion,nroJugadores);

    unsigned short  i;
    pid_t pid;
    Mazo* mazo = new Mazo ();
    vector<stack<Carta*>*>* pilones = new vector<stack<Carta*>*> (nroJugadores);
    generarPilones(mazo, nroJugadores, pilones);
    Jugador* jugador;
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
        jugador = new Jugador( 1, nroJugadores, &semaforosJugadores);
        jugador->obtenerPilon(pilones->at(0));
        semaforosCreacion.signal(1);
        cout<< "Soy "<< getpid() << "y me voy a habilitar el primer turno\n";
        semaforosCreacion.wait(0,nroJugadores);
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
                jugador = new Jugador(i + 1, nroJugadores, &semaforosJugadores);
                jugador->obtenerPilon(pilones->at(i));

                semaforosCreacion.signal(i+1);
                semaforosCreacion.signal(0);

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

