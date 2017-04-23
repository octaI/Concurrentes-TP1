
#ifndef CONCURRENTES_TP1_ATREVIDO_H
#define CONCURRENTES_TP1_ATREVIDO_H

#include <vector>
#include "Jugador.h"
#include "RegistroDeAcciones.h"

using namespace std;

class Atrevido {

private:
    vector<Jugador*> jugadores;
    Carta* ultimaCartaJugada = NULL;
    RegistroDeAcciones* acciones = new RegistroDeAcciones ();

    void crearJugadores (int nroJugadores);

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
