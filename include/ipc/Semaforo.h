
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
    int multiple_wait (unsigned short* nsem, short* count, short cantSemaforos) const; //decrementa multiples

    int signal (unsigned short nsem = 0, short count = 1) const; // incrementa
    int multiple_signal (unsigned short* nsem, short* count, short cantSemaforos) const;//incrementa multiples

    int barrier (unsigned short nsem = 0) const; // metodo barrera para el semaforo. semop 0
    int multiple_barrier (unsigned short* nsem, short cantSemaforos) const; // metodo barrera multiple

    void eliminar (unsigned short nsem = 0) const;

};


#endif //CONCURRENTES_TP1_SEMAFORO_H
