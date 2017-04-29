
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

    int valoresIniciales [nroJugadores] = { }; //inicializados en 0
    int valorAtrevidoInicial [1] = {1};
    int valorCreacionInicial [1] = {0};
    Semaforo semaforosJugadores ( "Atrevido.cpp", 'j', valoresIniciales, nroJugadores );
    Semaforo semaforoAtrevido("Atrevido.cpp",'m',valorAtrevidoInicial,1);
    Semaforo semaforoCreacion("Atrevido.cpp",'c',valorCreacionInicial,1);
    RegistroJugadores *registroJugadores = RegistroJugadores::getInstance();

    int i;
    pid_t pid;
    for (i = 0; i < nroJugadores; i++) {
        pid = fork ();
        Jugador* jugador;
        if( pid < 0 ) {
            Logger :: getInstance() -> error("Atrevido.cpp", "Error al crear proceso hijo para el jugador " + to_string(i + 1));
            exit(1);
        } else if ( pid == 0 ) {
            registroJugadores->registrarJugador(getpid());
            Logger :: getInstance() -> debug( "Atrevido.cpp",
                    "Se creo correctamente el proceso para el jugador " + to_string(i + 1) + " con pid " + to_string(getpid())
                    + " (padre: " + to_string(getppid()) + ")" );
            jugador = new Jugador (i + 1);
            semaforoCreacion.v(0,1); //ya cree este jugador
            break;
        }
    }

    if ( pid == 0 ) {
        int nroJugador = registroJugadores->devolverNumeroJugador(getpid());
        Logger::getInstance()->debug("Atrevido.cpp","Acá estoy, soy el jugador "+nroJugador);
        semaforosJugadores.p(nroJugador,1);
        Logger::getInstance()->debug("Atrevido.cpp","Jugada dummy");
        Logger::getInstance()->debug("Atrevido.cpp","Voy a avisarle al juego que ya jugué");
        semaforoAtrevido.v(0,1);
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
        semaforoCreacion.p(0, nroJugadores);
        for (int j = 0; j< nroJugadores; j++){
            Logger::getInstance()->debug("Atrevido.cpp","Voy a llamar al jugador "+to_string(j));
            semaforosJugadores.v(j,1);
            Logger::getInstance()->debug("Atrevido.cpp","Voy a esperar que termine su jugada el jugador "+to_string(j));
            semaforoAtrevido.p(0,1);
            Logger::getInstance()->debug("Atrevido.cpp","Ya termino su turno, lo freno al jugador "+to_string(j));
            semaforosJugadores.p(j,1);
        }
        wait ( NULL );

        Logger :: getInstance() -> debug( "Atrevido.cpp", "Termino la partida!" );
        if(!Atrevido::hayGanador()){
            exit (0);
        }

    }
}
