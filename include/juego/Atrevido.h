
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


using namespace std;

class Atrevido {

private:
    Carta* ultimaCartaJugada = NULL;
    RegistroDeAcciones* acciones = new RegistroDeAcciones ();

    void crearJugadores (const int nroJugadores);

    void jugarRonda();
    bool hayGanador();
    void terminarPartida();

public:
    Atrevido(int nroJugadores);
    ~Atrevido();
    Atrevido(const Atrevido& origen);
    Atrevido& operator= (const Atrevido& origen);

    void jugarPartida();

};


#endif //CONCURRENTES_TP1_ATREVIDO_H
