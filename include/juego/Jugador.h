
#ifndef CONCURRENTES_TP1_JUGADOR_H
#define CONCURRENTES_TP1_JUGADOR_H

#include <stack>
#include "Carta.h"
#include "Mazo.h"
#include "../ipc/Pipe.h"

using namespace std;

class Jugador {

private:
    int nro;
    stack<Carta> cartasEnPilon;

public:
    Jugador(int nro);
    ~Jugador();
    Jugador(const Jugador& origen);
    Jugador& operator= (const Jugador& origen);
    stack<Carta> mostrarPilon();
    Carta jugarCarta ();
    int mostrarNumero();
    void tomarCarta (Carta& carta);
};


#endif //CONCURRENTES_TP1_JUGADOR_H
