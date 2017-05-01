
#ifndef CONCURRENTES_TP1_ATREVIDO_H
#define CONCURRENTES_TP1_ATREVIDO_H

#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "Jugador.h"
#include "RegistroDeAcciones.h"
#include "../../include/ipc/Semaforo.h"
#include "../../include/logger/Logger.h"
#include "../../include/ipc/Pipe.h"
#include "../../include/juego/RegistroJugadores.h"


using namespace std;

class Atrevido {

private:
    Carta* ultimaCartaJugada = NULL;
    pid_t pidPadre;
    RegistroDeAcciones* acciones = new RegistroDeAcciones ();

    void iniciarJugadores(const int nroJugadores);
    void repartirCartas(Mazo* mazo, Jugador* jugador, int cantJugadores);
    void generarPilones(Mazo* mazo, int cantJugadores, vector<stack<Carta*>*>* pilones);

public:
    Atrevido(int nroJugadores);
    ~Atrevido();
    Atrevido(const Atrevido& origen);
    Atrevido& operator= (const Atrevido& origen);

    void jugarPartida();

};


#endif //CONCURRENTES_TP1_ATREVIDO_H
