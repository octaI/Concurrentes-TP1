
#include "../../include/juego/Atrevido.h"

Atrevido::~Atrevido() {
}

Atrevido::Atrevido(int nroJugadores) {
    iniciarJugadores(nroJugadores);
}

void Atrevido::iniciarJugadores(const int nroJugadores) {
    Logger::getInstance() -> info ( "Atrevido.cpp", "Van a jugar " + to_string(nroJugadores) + " jugadores" );

    int valoresInicialesJugadores [nroJugadores];
    int valorInicialCantjugadores[1] = {nroJugadores};
    std::fill_n(valoresInicialesJugadores, nroJugadores, 0);    // inicializados en 0
    valoresInicialesJugadores [0] = 1;  // empieza el primer jugador
    Semaforo semaforosJugadores ( "Atrevido.cpp", 'j', valoresInicialesJugadores, nroJugadores );

    Logger :: getInstance() -> debug( "Atrevido.cpp", "Soy el PADRE Atrevido con PID: " + to_string(getpid()));

    Semaforo semaforoAtrevido("Atrevido.cpp", 'a',valorInicialCantjugadores, 1);
    int i;
    pid_t pid;
    Mazo* mazo = new Mazo ();
    Jugador* jugador;
    for (i = 0; i < nroJugadores; i++) {
        pid = fork ();
        if( pid < 0 ) {
            Logger :: getInstance() -> error("Atrevido.cpp", "Error al crear proceso hijo para el jugador " + to_string(i + 1));
            exit(1);
        } else if ( pid == 0 ) {
            Logger :: getInstance() -> debug( "Atrevido.cpp",
                    "Se creo correctamente el proceso para el jugador " + to_string(i + 1) + " con pid " + to_string(getpid())
                    + " (padre: " + to_string(getppid()) + ")" );
            jugador = new Jugador ( i + 1, nroJugadores, &semaforosJugadores );
            repartirCartas(mazo, jugador, nroJugadores);
            //semaforoAtrevido.wait(0,1);
            break;
        }
    }

    if ( pid == 0 ) {
        //semaforoAtrevido.barrier(0);
        jugador->jugar();

    } else {

    }
}

void Atrevido::repartirCartas(Mazo* mazo, Jugador* jugador, int cantJugadores) {
    int cartasPorJugador = mazo->cantidadDeCartas() / cantJugadores;
    for (int i = 0; i < cartasPorJugador; i++) {
        jugador->tomarCarta(mazo->tomarCarta());
    }
}
