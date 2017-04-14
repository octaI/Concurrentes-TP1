
#ifndef CONCURRENTES_TP1_REGISTRODEACCIONES_H
#define CONCURRENTES_TP1_REGISTRODEACCIONES_H


#include "Accion.h"

class RegistroDeAcciones {
    // TODO: Debe guardar en una cola las acciones relevantes y el jugador que la ejecuto.

public:
    RegistroDeAcciones ();
    ~RegistroDeAcciones ();
    RegistroDeAcciones (const RegistroDeAcciones& origen);
    RegistroDeAcciones& operator= (const RegistroDeAcciones& origen);

    const Accion& obtenerUltimaAccion ();
    void nuevaAccion (Accion& accion);

};


#endif //CONCURRENTES_TP1_REGISTRODEACCIONES_H
