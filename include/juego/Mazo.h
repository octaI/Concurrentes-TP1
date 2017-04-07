
#ifndef CONCURRENTES_TP1_MAZO_H
#define CONCURRENTES_TP1_MAZO_H

#define CANT_CARTAS 40

#include <stack>
#include "Carta.h"

class Mazo {

private:
    std::stack<Carta&> cartas;

public:
    Mazo ();
    ~Mazo ();
    Mazo (const Mazo& origen);
    Mazo& operator= (const Mazo& origen);

    void barajar ();
    Carta& tomarCarta ();

};


#endif //CONCURRENTES_TP1_MAZO_H
