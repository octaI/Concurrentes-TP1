
#include "../../include/juego/Atrevido.h"

Atrevido::~Atrevido() {
}

bool Atrevido::hayGanador() {
    return false;
}

Atrevido::Atrevido(int nroJugadores) {
    crearJugadores (nroJugadores);
}

void Atrevido::crearJugadores(const int nroJugadores) {
    Logger::getInstance() -> info ( "Atrevido.cpp", "Van a jugar " + to_string(nroJugadores) + " jugadores" );

    int valoresIniciales [nroJugadores];
    Semaforo semaforos ( "Atrevido.cpp", 'j', valoresIniciales, nroJugadores );
    semaforos.v (0);

    Jugador* jugador = NULL;
    int i;
    pid_t pid;
    for (i = 0; i < nroJugadores; i++) {
        pid = fork ();
        if( pid < 0 ) {
            Logger :: getInstance() -> error("Atrevido.cpp", "Error al crear proceso hijo para el jugador " + to_string(i + 1));
            exit(1);
        } else if ( pid == 0 ) {
            Logger :: getInstance() -> debug( "Atrevido.cpp",
                    "Se creo correctamente el proceso para el jugador " + to_string(i + 1) + " con pid " + to_string(getpid())
                    + " (padre: " + to_string(getppid()) + ")" );
            jugador = new Jugador (i + 1);
            break;
        }
    }

    if ( pid == 0 ) {

        /*
        int j = 0;
        while ( j < 1 ) {
            semaforos.p (i);

            Carta cartaJugada = jugador->jugarCarta();
            Logger :: getInstance() -> debug( "Atrevido.cpp", "Carta jugada por Jugador " + to_string(i + 1) + ": " + Carta::serializar(cartaJugada) );

            if ( i + 1 < nroJugadores ) {
                semaforos.v ( i + 1 );
            } else {
                semaforos.v (0);
            }

            j++;
        }
        */

        exit (0);

    } else {
        wait ( NULL );

        Logger :: getInstance() -> debug( "Atrevido.cpp", "Termino la partida!" );
        exit (0);
    }
}
