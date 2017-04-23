
#include "../../include/logger/Logger.h"

const string Logger::RUTA_BITACORA = "../logs/";
const string Logger::ARCHIVO_BITACORA = RUTA_BITACORA + "log.txt";
const string Logger::DEBUG = "DEBUG";
const string Logger::INFO = "INFO";
const string Logger::WARN = "WARN";
const string Logger::ERROR = "ERROR";

Logger* Logger :: instance = NULL;

Logger::Logger() {}

Logger* Logger::getInstance() {

    if ( instance == NULL ) {
        instance = new Logger();
    }
    return instance;

}

int Logger::escribir ( string modo, string tag, string msg ) {
    LockFile lock (ARCHIVO_BITACORA);
    lock.tomarLock();

    const string log = fechaActual() + " [" + modo + "] - " + tag + ": " + msg + "\n";
    int resultado = lock.escribir ( static_cast<const void *>(log.c_str()), log.size() );

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
           + to_string(now->tm_mday) + 'T'
           + to_string(now->tm_hour) + ':'
           + to_string(now->tm_min) + ':'
           + to_string(now->tm_sec);
}

int Logger::debug(string tag, string msg) {
    return escribir(DEBUG, tag, msg);
}

int Logger::info(string tag, string msg) {
    return escribir(INFO, tag, msg);
}

int Logger::warn(string tag, string msg) {
    return escribir(WARN, tag, msg);
}

int Logger::error(string tag, string msg) {
    return escribir(ERROR, tag, msg);
}
