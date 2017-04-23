
#ifndef CONCURRENTES_TP1_ARBITRO_H
#define CONCURRENTES_TP1_ARBITRO_H

#include <vector>
#include "Carta.h"
#include "Jugador.h"

using namespace std;

class Arbitro {

public:
    Arbitro();
    ~Arbitro();
    Arbitro(const Arbitro& origen);

    int verPilonDe(Jugador& jugador);

};


#endif //CONCURRENTES_TP1_ARBITRO_H
