
#include "../../include/logger/Logger.h"

const string Logger::RUTA_BITACORA = "../../logs/";
const string Logger::ARCHIVO_BITACORA = RUTA_BITACORA + "log.txt";
const string Logger::DEBUG = "debug";
const string Logger::INFO = "info";
const string Logger::WARN = "warn";
const string Logger::ERROR = "error";

Logger* Logger :: instance = NULL;

Logger::Logger() {}

Logger* Logger::getInstance() {

    if ( instance == NULL ) {
        instance = new Logger();
    }
    return instance;

}

int Logger::escribir ( string modo, string msg ) {
    LockFile lock (ARCHIVO_BITACORA);
    lock.tomarLock();

    const string log = fechaActual() + ": [" + modo + "] " + msg;
    int resultado = lock.escribir ( static_cast<const void *>(log.c_str()), sizeof(log) );

    lock.liberarLock();
    delete &lock;
    return resultado;
}

// TODO: Buscar metodo para trabajar con precision de milisegundos, sino el log pierde sentido.
string Logger::fechaActual() {
    time_t t = time(0);
    struct tm * now = localtime( & t );
    return to_string(now->tm_year + 1900) + '-'
           + to_string(now->tm_mon + 1) + '-'
           + to_string(now->tm_mday)
           + to_string(now->tm_mday)
           + to_string(now->tm_hour)
           + to_string(now->tm_min)
           + to_string(now->tm_sec);
}

int Logger::debug(string msg) {
    return escribir(DEBUG, msg);
}

int Logger::info(string msg) {
    return escribir(INFO, msg);
}

int Logger::warn(string msg) {
    return escribir(WARN, msg);
}

int Logger::error(string msg) {
    return escribir(ERROR, msg);
}
