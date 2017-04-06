
#ifndef CONCURRENTES_TP1_MEMORIACOMPARTIDA_H
#define CONCURRENTES_TP1_MEMORIACOMPARTIDA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>

using namespace std;

template <class T> class MemoriaCompartida {

private:
    int	shmId;
    T*	ptrDatos;

    int	cantidadProcesosAdosados() const;

public:
    MemoriaCompartida();
    void crear(const string& archivo, const char letra);
    void liberar();

    MemoriaCompartida(const string& archivo, const char letra);
    MemoriaCompartida(const MemoriaCompartida& origen);
    ~MemoriaCompartida();
    MemoriaCompartida<T>& operator= (const MemoriaCompartida& origen);
    void escribir(const T& dato);
    T leer() const;

};


#endif //CONCURRENTES_TP1_MEMORIACOMPARTIDA_H
