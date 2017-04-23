
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

    ssize_t escribir ( string modo, string tag, string msg );
    string fechaActual ();

public:
    static Logger* getInstance ();

    ssize_t debug(string tag, string msg);
    ssize_t info(string tag, string msg);
    ssize_t warn(string tag, string msg);
    ssize_t error(string tag, string msg);


};


#endif //CONCURRENTES_TP1_LOGGER_H
