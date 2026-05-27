#ifndef IPC_H
#define IPC_H

#include <semaphore.h>

#include "structs.h"

Solicitud* conectar_memoria();

sem_t* conectar_semaforo_servidor();

sem_t* conectar_semaforo_cliente();

#endif