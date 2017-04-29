
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

    int valoresInicialesJugadores [nroJugadores];
    std::fill_n(valoresInicialesJugadores, nroJugadores, 0);    // inicializados en 0
    valoresInicialesJugadores [0] = 1;  // empieza el primer jugador
    Semaforo semaforosJugadores ( "Atrevido.cpp", 'j', valoresInicialesJugadores, nroJugadores );

    int i;
    pid_t pid;
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

            // Tomo 2 cartas de ejemplo.
            Mazo mazo;
            mazo.generar();
            jugador->tomarCarta(mazo.tomarCarta());
            jugador->tomarCarta(mazo.tomarCarta());

            break;
        }
    }

    if ( pid == 0 ) {
        jugador->jugar();

    } else {

    }
}
