#include "../../include/juego/Arbitro.h"


Arbitro::Arbitro(Semaforo *semaforoArbitro, int cantJugadores) {
    this->semaforoArbitro = semaforoArbitro;
    this->cantJugadores = cantJugadores;
    iniciar();
}

void Arbitro::iniciar() {
    while ( !terminoPartida() ) {
        semaforoArbitro->wait();
        consultarJugadores();
    }
    Logger :: getInstance() -> debug ( "Árbitro", "Terminó la partida, el árbitro se retira" );

    shMemCantCartasJugadores.liberar();
    exit(0);
}

bool Arbitro::terminoPartida() {
    shMemFinJuego.crear( "../src/juego/Jugador.cpp", 'E' );
    return shMemFinJuego.leer() > 0;
}

void Arbitro::consultarJugadores() {
    int resultadoShMemCantCartasJugadores = shMemCantCartasJugadores.crear( "../src/juego/Jugador.cpp", 'C' );

    if ( resultadoShMemCantCartasJugadores == SHM_OK ) {
        int* cantCartasJugadores = shMemCantCartasJugadores.leer();
        for (int i = 0; i < cantJugadores; i++) {
            int cantCartas = cantCartasJugadores [i];
            Logger :: getInstance() -> info ( "Árbitro", "El jugador " + to_string(i + 1) + " tiene " + to_string(cantCartas) + " cartas en su pilón" );
            cout << "Árbitro: El jugador " << i + 1 << " tiene " << cantCartas << " cartas en su pilón" << endl;
        }
    } else {
        Logger :: getInstance() -> error ("Árbitro", "No se pudo crear la memoria compartida para obtener la cantidad de cartas en el pilón de cada jugador. "
                                                             "Error nro: " + to_string(resultadoShMemCantCartasJugadores) );
    }
}
