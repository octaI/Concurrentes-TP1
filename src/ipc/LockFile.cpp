
#include <dirent.h>
#include <sys/stat.h>
#include "../../include/ipc/LockFile.h"

LockFile :: LockFile ( const std::string nombre ) {

    this->nombre = nombre;
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;

    crearDirectorioSiNoExiste(nombre);
    this->fd = open ( this->nombre.c_str(),O_CREAT|O_WRONLY,0777 );

}

int LockFile :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockFile :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

ssize_t LockFile :: escribir ( const void* buffer,const ssize_t buffsize ) const {
    lseek ( this->fd,0,SEEK_END );
    return write ( this->fd,buffer,buffsize );
}

LockFile :: ~LockFile () {
    close ( this->fd );
}

int LockFile::crearDirectorioSiNoExiste(string rutaCompletaArchivo) {
    string path = rutaCompletaArchivo.substr(0, rutaCompletaArchivo.find_last_of("\\/"));
    DIR* dir = opendir(path.c_str());
    if (dir) {
        return closedir(dir);
    }
    else if (ENOENT == errno) {
        return mkdir(path.c_str(), 0777);
    }
}
