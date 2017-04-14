
#ifndef CONCURRENTES_TP1_ACCION_H
#define CONCURRENTES_TP1_ACCION_H

#include <string>
#include "Jugador.h"

using namespace std;

class Accion {

private:
    string mensaje;
    Jugador& ejecutor;

public:
    Accion ();
    ~Accion ();
    Accion (const Accion& origen);
    Accion& operator= (const Accion& origen);

    string obtenerMensaje ();
    const Jugador& obtenerEjecutor ();
};


#endif //CONCURRENTES_TP1_ACCION_H
