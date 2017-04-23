
#ifndef CONCURRENTES_TP1_LOGGER_H
#define CONCURRENTES_TP1_LOGGER_H

#include <iostream>
#include <stdio.h>
#include <ctime>

#include "../../include/ipc/LockFile.h"

using namespace std;

class Logger {

private:
    static const string RUTA_BITACORA;
    static const string ARCHIVO_BITACORA;

    static const string DEBUG;
    static const string INFO;
    static const string WARN;
    static const string ERROR;

    static Logger* instance;
    Logger ( void );

    int escribir ( string modo, string msg );
    string fechaActual ();

public:
    static Logger* getInstance ();

    int debug(string msg);
    int info(string msg);
    int warn(string msg);
    int error(string msg);


};


#endif //CONCURRENTES_TP1_LOGGER_H
