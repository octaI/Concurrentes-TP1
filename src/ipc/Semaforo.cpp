
#include "../../include/ipc/Semaforo.h"

Semaforo :: Semaforo ( const std::string& nombre, const char letra, const int* valoresIniciales, const int nsems ) {
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

int Semaforo :: wait(unsigned short nsem, short count) const {

    struct sembuf operacion;

    operacion.sem_num = nsem;	// numero de semaforo
    operacion.sem_op  = -count;	// restar valor al semaforo
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop ( this->id,&operacion,1 );
    return resultado;
}

int Semaforo :: signal(unsigned short nsem, short count) const {

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

int Semaforo :: barrier(unsigned short nsem) const {
    struct sembuf operacion;
    operacion.sem_num = nsem;
    operacion.sem_op = 0;
    operacion.sem_flg = SEM_UNDO;

    int resultado = semop(this->id,&operacion,1);
    return resultado;
}

int Semaforo:: multiple_wait(unsigned short nsem[], short count[], short cantSemaforos) const{
    int resultado;
    struct sembuf operacion[cantSemaforos];
    for(int i = 0; i < cantSemaforos; i++ ) {

        operacion[i].sem_num = nsem[i];
        operacion[i].sem_op = -count[i];
        operacion[i].sem_flg = SEM_UNDO;

    }
    resultado = semop(this->id, operacion, cantSemaforos);
    return resultado;
    }

int Semaforo:: multiple_signal(unsigned short nsem[], short count[], short cantSemaforos) const{
    int resultado;
    struct sembuf operacion[cantSemaforos];
    for(int i = 0; i < cantSemaforos; i++){
        operacion[i].sem_num = nsem[i];
        operacion[i].sem_op = count[i];
        operacion[i].sem_flg = SEM_UNDO;
    }
    resultado = semop(this->id,operacion,cantSemaforos);

    return resultado;
}

int Semaforo:: multiple_barrier(unsigned short nsem[], short cantSemaforos) const{
    int resultado;
    struct sembuf operacion[cantSemaforos];
    for(int i = 0; i < cantSemaforos; i++){
        operacion[i].sem_op = 0;
        operacion[i].sem_flg = SEM_UNDO;
        operacion[i].sem_num = nsem[i];
    }
    resultado = semop(this->id,operacion,cantSemaforos);

    return resultado;
}