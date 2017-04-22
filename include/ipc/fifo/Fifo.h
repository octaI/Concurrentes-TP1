
#ifndef CONCURRENTES_TP1_FIFO_H
#define CONCURRENTES_TP1_FIFO_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class Fifo {

public:
    Fifo(const std::string nombre);
    virtual ~Fifo();
    virtual void abrir() = 0;
    void cerrar();
    void eliminar() const;

protected:
    std::string nombre;
    int fd;

};


#endif //CONCURRENTES_TP1_FIFO_H
