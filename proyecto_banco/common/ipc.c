#include "ipc.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/sistema_banco"

#define SEM_SERVIDOR "/sem_servidor"

#define SEM_CLIENTE "/sem_cliente"

Solicitud* conectar_memoria() {

    int fd = shm_open(
        SHM_NAME,
        O_CREAT | O_RDWR,
        0666
    );

    ftruncate(fd, sizeof(Solicitud));

    return mmap(
        NULL,
        sizeof(Solicitud),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );
}

sem_t* conectar_semaforo_servidor() {

    return sem_open(
        SEM_SERVIDOR,
        O_CREAT,
        0666,
        0
    );
}

sem_t* conectar_semaforo_cliente() {

    return sem_open(
        SEM_CLIENTE,
        O_CREAT,
        0666,
        0
    );
}