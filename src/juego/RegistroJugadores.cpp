#include "../../include/juego/RegistroJugadores.h"

RegistroJugadores* RegistroJugadores::instance = NULL;

int RegistroJugadores::numeroJugadores = 0;

RegistroJugadores::RegistroJugadores() {

}
RegistroJugadores* RegistroJugadores::getInstance() {
    if (instance == NULL){
        instance = new RegistroJugadores();
        numeroJugadores = 0;
    }
    return instance;
}

void RegistroJugadores::registrarJugador(pid_t pid) {
    instance->registroJugadores[pid] = numeroJugadores;
    numeroJugadores++;
}

int RegistroJugadores::devolverNumeroJugador(pid_t pid) {
    return instance->registroJugadores[pid];
}