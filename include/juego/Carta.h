
#ifndef CONCURRENTES_TP1_CARTA_H
#define CONCURRENTES_TP1_CARTA_H


class Carta {

public:
    Carta ();
    ~Carta ();
    Carta (const Carta& origen);
    Carta& operator= (const Carta& origen);

};


#endif //CONCURRENTES_TP1_CARTA_H
