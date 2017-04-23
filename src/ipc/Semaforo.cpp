
#include "../../include/ipc/Semaforo.h"

Semaforo :: Semaforo ( const std::string& nombre, const char letra, const int nsems, const int* valoresIniciales ) {
    key_t clave = ftok ( nombre.c_str(), letra );
    this->id = semget ( clave,nsems,0666 | IPC_CREAT );

    this->inicializar (nsems, valoresIniciales);
}

Semaforo::~Semaforo() {
}

int Semaforo :: inicializar (const int nsems, const int* valoresIniciales) const {

    union semnum {
        int val;
        struct semid_ds* buf;
        ushort* array;
    };
    semnum init;

    int resultados [nsems];
    for (int i = 0; i < nsems; i++) {
        init.val = valoresIniciales[i];
        resultados[i] = semctl ( this->id,i,SETVAL,init );
    }

    int semaforosInicializadosOK = 0;
    for (int j = 0; j < nsems; j++) {
        if (resultados[j] == 0) {
            semaforosInicializadosOK++;
        }
    }
    return semaforosInicializadosOK;
}

int Semaforo :: p (unsigned short nsem, short count) const {

    struct sembuf operacion;

    operacion.sem_num = nsem;	// numero de semaforo
    operacion.sem_op  = -count;	// restar valor al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop ( this->id,&operacion,1 );
    return resultado;
}

int Semaforo :: v (unsigned short nsem, short count) const {

    struct sembuf operacion;

    operacion.sem_num = nsem;	// numero de semaforo
    operacion.sem_op  = count;	// sumar valor al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop ( this->id,&operacion,1 );
    return resultado;
}

void Semaforo :: eliminar () const {
    semctl ( this->id,0,IPC_RMID );
}

int Semaforo::p(unsigned short *nsem, short count) const {
    size_t cant_operaciones = sizeof(nsem);
    struct sembuf operaciones [cant_operaciones];
    for (int i = 0; i < cant_operaciones; i++) {
        operaciones[i].sem_num = nsem[i];	// numero de semaforo
        operaciones[i].sem_op  = -count;	// restar valor al semaforo
        operaciones[i].sem_flg = SEM_UNDO;
    }
    int resultado = semop ( this->id,operaciones,cant_operaciones );
    return resultado;
}

int Semaforo::v(unsigned short* nsem, short count) const {
    size_t cant_operaciones = sizeof(nsem);
    struct sembuf operaciones [cant_operaciones];
    for (int i = 0; i < cant_operaciones; i++) {
        operaciones[i].sem_num = nsem[i];	// numero de semaforo
        operaciones[i].sem_op  = count;	// sumar valor al semaforo
        operaciones[i].sem_flg = SEM_UNDO;
    }
    int resultado = semop ( this->id,operaciones,cant_operaciones );
    return resultado;
}

