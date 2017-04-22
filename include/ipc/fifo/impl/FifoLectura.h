
#ifndef CONCURRENTES_TP1_FIFOLECTURA_H
#define CONCURRENTES_TP1_FIFOLECTURA_H


#include "../Fifo.h"

class FifoLectura : public Fifo {
public:
    FifoLectura(const std::string nombre);
    ~FifoLectura();

    void abrir();
    ssize_t leer(void* buffer,const ssize_t buffsize) const;
};


#endif //CONCURRENTES_TP1_FIFOLECTURA_H
