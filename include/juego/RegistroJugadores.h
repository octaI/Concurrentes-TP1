
#ifndef CONCURRENTES_TP1_REGISTROJUGADORES_H
#define CONCURRENTES_TP1_REGISTROJUGADORES_H

#include <sched.h>
#include <map>

using namespace std;

class RegistroJugadores {

private:
    std::map<pid_t,int> registroJugadores;

    static RegistroJugadores* instance;
    static int numeroJugadores;

    RegistroJugadores ();
public:
    static RegistroJugadores* getInstance();
    void registrarJugador(pid_t pid);
    int devolverNumeroJugador(pid_t pid);
};

#endif //CONCURRENTES_TP1_REGISTROJUGADORES_H
