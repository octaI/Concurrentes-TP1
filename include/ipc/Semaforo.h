
#ifndef CONCURRENTES_TP1_SEMAFORO_H
#define CONCURRENTES_TP1_SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
    int id;

    int inicializar (int valorInicial) const;

public:
    Semaforo ( const std::string& nombre, const char letra, const int valorInicial );
    ~Semaforo();

    int p (short int count = 1) const; // decrementa
    int v (short int count = 1) const; // incrementa
    void eliminar () const;

};


#endif //CONCURRENTES_TP1_SEMAFORO_H
