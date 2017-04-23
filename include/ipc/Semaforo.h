
#ifndef CONCURRENTES_TP1_SEMAFORO_H
#define CONCURRENTES_TP1_SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
    int id;
    int valorInicial;

    int inicializar () const;

public:
    Semaforo ( const std::string& nombre,const int valorInicial );
    ~Semaforo();

    int p () const; // decrementa
    int v () const; // incrementa
    void eliminar () const;

};


#endif //CONCURRENTES_TP1_SEMAFORO_H
