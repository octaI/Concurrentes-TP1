
#ifndef CONCURRENTES_TP1_SEMAFORO_H
#define CONCURRENTES_TP1_SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
    int id;

    int inicializar (const int nsems, const int* valoresIniciales) const;

public:
    Semaforo ( const std::string& nombre, const char letra, const int* valoresIniciales, const int nsems = 1 );
    ~Semaforo();

    int p (unsigned short nsem = 0, short count = 1) const; // decrementa
    int p (unsigned short* nsem, short count = 1) const; // decrementa para varios semaforos

    int v (unsigned short nsem, short count = 1) const; // incrementa
    int v (unsigned short* nsem, short count = 1) const; // incrementa para varios semaforos

    void eliminar () const;

};


#endif //CONCURRENTES_TP1_SEMAFORO_H
