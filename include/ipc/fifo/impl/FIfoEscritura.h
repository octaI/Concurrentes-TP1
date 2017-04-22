
#ifndef CONCURRENTES_TP1_FIFOESCRITURA_H
#define CONCURRENTES_TP1_FIFOESCRITURA_H


#include "../Fifo.h"

class FifoEscritura : public Fifo {
public:
    FifoEscritura(const std::string nombre);
    ~FifoEscritura();

    void abrir();
    ssize_t escribir(const void* buffer,const ssize_t buffsize) const;
};


#endif //CONCURRENTES_TP1_FIFOESCRITURA_H
