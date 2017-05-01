#ifndef CONCURRENTES_TP1_MEMORIACOMP_H
#define CONCURRENTES_TP1_MEMORIACOMP_H

#define SHM_OK			 0
#define	ERROR_FTOK		-1
#define ERROR_SHMGET	-2
#define	ERROR_SHMAT		-3

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>


template <class T> class MemoriaComp {

private:
    int shmId;
    T*	ptrDatos;

    int cantidadProcesosAdosados () const;

public:
    MemoriaComp ();
    ~MemoriaComp ();
    int crear ( const std::string& archivo,const char letra );
    void liberar ();
    void escribir ( const T& dato );
    T leer () const;

};

template <class T> MemoriaComp<T> :: MemoriaComp() : shmId(0), ptrDatos(NULL) {
}

template <class T> MemoriaComp<T> :: ~MemoriaComp() {
}

template <class T> int MemoriaComp<T> :: crear ( const std::string& archivo,const char letra ) {

    // generacion de la clave
    key_t clave = ftok ( archivo.c_str(),letra );
    if ( clave == -1 )
        return ERROR_FTOK;
    else {
        // creacion de la memoria compartida
        this->shmId = shmget ( clave,sizeof(T),0644|IPC_CREAT );

        if ( this->shmId == -1 )
            return ERROR_SHMGET;
        else {
            // attach del bloque de memoria al espacio de direcciones del proceso
            void* ptrTemporal = shmat ( this->shmId,NULL,0 );

            if ( ptrTemporal == (void *) -1 ) {
                return ERROR_SHMAT;
            } else {
                this->ptrDatos = static_cast<T*> (ptrTemporal);
                return SHM_OK;
            }
        }
    }
}


template <class T> void MemoriaComp<T> :: liberar () {
    // detach del bloque de memoria
    shmdt ( static_cast<void*> (this->ptrDatos) );

    int procAdosados = this->cantidadProcesosAdosados ();

    if ( procAdosados == 0 ) {
        shmctl ( this->shmId,IPC_RMID,NULL );
    }
}

template <class T> void MemoriaComp<T> :: escribir ( const T& dato ) {
    * (this->ptrDatos) = dato;
}

template <class T> T MemoriaComp<T> :: leer () const {
    return ( *(this->ptrDatos) );
}

template <class T> int MemoriaComp<T> :: cantidadProcesosAdosados () const {
    shmid_ds estado;
    shmctl ( this->shmId,IPC_STAT,&estado );
    return estado.shm_nattch;
}

#endif //CONCURRENTES_TP1_MEMORIACOMP_H
