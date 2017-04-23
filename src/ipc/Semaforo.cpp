
#include "../../include/ipc/Semaforo.h"

Semaforo :: Semaforo ( const std::string& nombre, const char letra, const int valorInicial ) {
    key_t clave = ftok ( nombre.c_str(), letra );
    this->id = semget ( clave,1,0666 | IPC_CREAT );

    this->inicializar (valorInicial);
}

Semaforo::~Semaforo() {
}

int Semaforo :: inicializar (int valorInicial) const {

    union semnum {
        int val;
        struct semid_ds* buf;
        ushort* array;
    };

    semnum init;
    init.val = valorInicial;
    int resultado = semctl ( this->id,0,SETVAL,init );
    return resultado;
}

int Semaforo :: p (short int count) const {

    struct sembuf operacion;

    operacion.sem_num = 0;	// numero de semaforo
    operacion.sem_op  = -count;	// restar valor al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop ( this->id,&operacion,1 );
    return resultado;
}

int Semaforo :: v (short int count) const {

    struct sembuf operacion;

    operacion.sem_num = 0;	// numero de semaforo
    operacion.sem_op  = count;	// sumar valor al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop ( this->id,&operacion,1 );
    return resultado;
}

void Semaforo :: eliminar () const {
    semctl ( this->id,0,IPC_RMID );
}