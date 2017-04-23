
#include "../../include/juego/Atrevido.h"

Atrevido::~Atrevido() {
    for (Jugador* jugador : this->jugadores) {
        delete jugador;
    }
}

void Atrevido::jugarPartida() {
    while (!hayGanador()) {
        jugarRonda();
    }
    terminarPartida();
}

void Atrevido::jugarRonda() {

}

void Atrevido::terminarPartida() {

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
    valoresIniciales[0] = 1;
    Semaforo semaforos ( "Atrevido.cpp", 'j', valoresIniciales, nroJugadores );

    Mazo mazo;
    mazo.barajar();

    for (int i = 0; i < nroJugadores; i++) {
        pid_t pid = fork ();
        if( pid < 0 ) {
            Logger :: getInstance() -> error("Atrevido.cpp", "Error al crear proceso hijo para el jugador " + to_string(i + 1));
            exit(1);
        } else if ( pid == 0 ) {
            // Creo Jugadores hijos
            Logger :: getInstance() -> debug( "Atrevido.cpp",
                    "Se creo correctamente el proceso para el jugador " + to_string(i + 1) + " con pid " + to_string(getpid())
                    + " (padre: " + to_string(getppid()) + ")" );

            Jugador* jugador = new Jugador (i + 1);
            this->jugadores[i] = jugador;

            exit(0);
        } else {
            // Administro el turno.
            wait ( NULL );
        }
    }

    sleep(5);
    Logger :: getInstance() -> debug ("Atrevido.cpp", "Fueron creados " + to_string(this->jugadores.size()) + " jugadores");
}
