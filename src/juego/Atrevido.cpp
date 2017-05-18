
#include "../../include/juego/Atrevido.h"

Atrevido::~Atrevido() {
}

Atrevido::Atrevido(int nroJugadores) {
    iniciarJugadores(nroJugadores);
}

void Atrevido::iniciarJugadores(const int nroJugadores) {
    string archivo("../src/juego/Jugador.cpp");
    MemoriaComp<int> turnoJugador;
    MemoriaComp<int> finJuego;
    MemoriaComp<int> cantCartasJugadores;
    finJuego.crear(archivo,'E');
    finJuego.escribir(0);
    int resultado = turnoJugador.crear(archivo,'T');
    turnoJugador.escribir(1); // numero de jugador inicial
    Logger::getInstance() -> info ( "Atrevido.cpp", "Van a jugar " + to_string(nroJugadores) + " jugadores" );
    Logger :: getInstance() -> debug( "Atrevido.cpp", "Soy el PADRE Atrevido con PID: " + to_string(getpid()));

    // Semaforos para administrar turnos
    int valoresInicialesJugadores [nroJugadores+1] = {}; //la ultima pos es un contador para el turno
    int valoresInicialesCreacion [nroJugadores] = {};
    std::fill_n(valoresInicialesJugadores, nroJugadores+1, 0);    // inicializados en 0
    Semaforo semaforosJugadores ( "Atrevido.cpp", 'j', valoresInicialesJugadores, nroJugadores+1 );
    Semaforo semaforosCreacion("Atrevido.cpp",'c',valoresInicialesCreacion,nroJugadores);

    // Semaforo de arbitro
    int valorInicialArbitro [1] = {0};
    Semaforo semaforoArbitro ( "../src/juego/Arbitro.cpp", 'a', valorInicialArbitro );

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
        jugador = new Jugador( 1, nroJugadores, &semaforosJugadores, &semaforoArbitro );
        jugador->obtenerPilon(pilones->at(0));
        semaforosCreacion.signal(1);
        semaforosCreacion.wait(0,nroJugadores);
        semaforosJugadores.signal(0);
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
                jugador = new Jugador(i + 1, nroJugadores, &semaforosJugadores, &semaforoArbitro );
                jugador->obtenerPilon(pilones->at(i));

                semaforosCreacion.signal(i+1);
                semaforosCreacion.signal(0);

                break;
            }

        }
    }

    if ( pid == 0 || pid1 == 0 ) {
        jugador->jugar();
        delete jugador;
    } else {

        Arbitro* arbitro;
        pid_t pid2 = fork ();
        if ( pid2 < 0 ) {
            Logger::getInstance()->error("Atrevido.cpp",
                                         "Error al crear proceso hijo para el árbitro");
            exit(1);
        } else if ( pid2 == 0 ) {
            Logger::getInstance()->debug("Atrevido.cpp",
                                         "Se creo correctamente el proceso para el árbitro "
                                         " con pid " + to_string(getpid())
                                         + " (padre: " + to_string(getppid()) + ")");
            arbitro = new Arbitro ( &semaforoArbitro, nroJugadores );
        } else {
            wait(NULL);
            int j = 0;
            while(j < nroJugadores) {
                if ((j+1) != finJuego.leer()){
                    cout << "Jugador " << j+1 << " perdio el juego" << endl;
                } else{
                    cout << "Jugador " << j+1 << " gano el juego" << endl;

                }
                j++;
            }
            semaforosCreacion.eliminar(0);
            semaforosJugadores.eliminar(0);
            semaforoArbitro.eliminar(0);
            MemoriaComp<int> memoriaNro;
            MemoriaComp<int> memoriaPalo;
            memoriaNro.crear(archivo,'J');
            memoriaPalo.crear(archivo,'P');
            memoriaNro.liberar();
            memoriaPalo.liberar();
            finJuego.liberar();
            turnoJugador.liberar();

            MemoriaComp<int> shMemCantCartasJugadores;
            for (int j = 0; j < nroJugadores; j++) {
                shMemCantCartasJugadores.crear("../src/juego/Jugador.cpp", (char) i + 1);
                shMemCantCartasJugadores.liberar();
            }

            delete mazo;
            //delete arbitro;
            exit(0);
        }
    }
}


void Atrevido::generarPilones(Mazo* mazo, int cantJugadores, vector<stack<Carta*>*>* pilones) {
    int cartasPorJugador = mazo->cantidadDeCartas() / cantJugadores;
    for (int j = 0; j < cantJugadores; j++){
        pilones->at(j) = new stack<Carta*>();
        for (int i = 0; i < cartasPorJugador; i++) {
            pilones->at(j)->push(mazo->tomarCarta());
        }
    }
}

