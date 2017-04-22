
#ifndef CONCURRENTES_TP1_LOCKFILE_H
#define CONCURRENTES_TP1_LOCKFILE_H

#include <unistd.h>
#include <fcntl.h>
#include <string>

class LockFile {

private:
    struct flock fl;
    int fd;
    std::string nombre;

public:
    LockFile ( const std::string nombre );
    ~LockFile();

    int tomarLock ();
    int liberarLock ();
    ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
};


#endif //CONCURRENTES_TP1_LOCKFILE_H
