
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

    int wait (unsigned short nsem = 0, short count = 1) const; // decrementa
    int wait_multiple (unsigned short *nsem, short count = 1) const; // decrementa para varios semaforos

    int signal (unsigned short nsem = 0, short count = 1) const; // incrementa
    int signal_multiple (unsigned short *nsem, short count = 1) const; // incrementa para varios semaforos

    void eliminar () const;

};


#endif //CONCURRENTES_TP1_SEMAFORO_H
