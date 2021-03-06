
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

template <class T> MemoriaCompartida<T>::MemoriaCompartida() : shmId(0), ptrDatos(NULL) {}

template <class T> void MemoriaCompartida<T>::crear ( const string& archivo, const char letra ) {
    key_t clave = ftok ( archivo.c_str(), letra );

    if ( clave > 0 ) {
        this->shmId = shmget ( clave, sizeof(T), 0644 | IPC_CREAT );

        if ( this->shmId > 0 ) {
            void* tmpPtr = shmat ( this->shmId, NULL, 0 );
            if ( tmpPtr != (void*) -1 ) {
                this->ptrDatos = static_cast<T*> (tmpPtr);
            } else {
                string mensaje = string("Error en shmat(): ") + string(strerror(errno));
                throw mensaje;
            }
        } else {
            string mensaje = string("Error en shmget(): ") + string(strerror(errno));
            throw mensaje;
        }
    } else {
        string mensaje = string("Error en ftok(): ") + string(strerror(errno));
        throw mensaje;
    }
}

template <class T> void MemoriaCompartida<T>::liberar () {
    int errorDt = shmdt ( (void *) this->ptrDatos );

    if ( errorDt != -1 ) {
        int procAdosados = this->cantidadProcesosAdosados ();
        if ( procAdosados == 0 ) {
            shmctl ( this->shmId, IPC_RMID, NULL );
        }
    } else {
        string mensaje = string("Error en shmdt(): ") + string(strerror(errno));
        throw mensaje;
    }
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida ( const string& archivo, const char letra ) : shmId(0), ptrDatos(NULL) {
    this->crear(archivo, letra);
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida ( const MemoriaCompartida& origen ) : shmId(origen.shmId) {
    void* tmpPtr = shmat ( origen.shmId, NULL, 0 );

    if ( tmpPtr != (void*) -1 ) {
        this->ptrDatos = static_cast<T*> (tmpPtr);
    } else {
        string mensaje = string("Error en shmat(): ") + string(strerror(errno));
        throw mensaje;
    }
}

template <class T> MemoriaCompartida<T>::~MemoriaCompartida () {
    this->liberar();
}

template <class T> MemoriaCompartida<T>& MemoriaCompartida<T>::operator= ( const MemoriaCompartida& origen ) {
    this->shmId = origen.shmId;
    void* tmpPtr = shmat ( this->shmId,NULL,0 );

    if ( tmpPtr != (void*) -1 ) {
        this->ptrDatos = static_cast<T*> (tmpPtr);
    } else {
        std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
        throw mensaje;
    }

    return *this;
}

template <class T> void MemoriaCompartida<T>::escribir ( const T& dato ) {
    *(this->ptrDatos) = dato;
}

template <class T> T MemoriaCompartida<T>::leer() const {
    return *(this->ptrDatos);
}

template <class T> int MemoriaCompartida<T>::cantidadProcesosAdosados () const {
    shmid_ds estado;
    shmctl ( this->shmId, IPC_STAT, &estado );
    return estado.shm_nattch;
}

#endif //CONCURRENTES_TP1_MEMORIACOMPARTIDA_H
