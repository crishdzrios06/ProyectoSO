#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "../common/ipc.h"
#include "manejador_clientes.h"

Solicitud* memoria;
sem_t* sem_servidor;
sem_t* sem_cliente;

void* hilo_cliente(void* arg) {

    procesar_solicitud(memoria);

    sem_post(sem_cliente);

    pthread_exit(NULL);
}

int main() {

    printf("Servidor iniciado...\n");

    memoria = conectar_memoria();

    sem_servidor = conectar_semaforo_servidor();
    sem_cliente = conectar_semaforo_cliente();

    while(1) {

    sem_wait(sem_servidor);

    printf("\n====================================\n");

    switch(memoria->tipo) {

        case TIPO_LOGIN:

            printf(
                "[SERVIDOR] LOGIN solicitado por: %s\n",
                memoria->usuario
            );

            break;

        case TIPO_REGISTRO:

            printf(
                "[SERVIDOR] REGISTRO solicitado por: %s\n",
                memoria->usuario
            );

            break;

        case TIPO_CONSULTA:

            printf(
                "[SERVIDOR] CONSULTA DE SALDO de: %s\n",
                memoria->usuario
            );

            break;

        case TIPO_DEPOSITO:

            printf(
                "[SERVIDOR] DEPOSITO solicitado por %s -> %.2f\n",
                memoria->usuario,
                memoria->monto
            );

            break;

        case TIPO_RETIRO:

            printf(
                "[SERVIDOR] RETIRO solicitado por %s -> %.2f\n",
                memoria->usuario,
                memoria->monto
            );

            break;

        default:

            printf(
                "[SERVIDOR] Operacion desconocida\n"
            );
    }

    procesar_solicitud(memoria);

    printf(
        "[SERVIDOR] Resultado: %s\n",
        memoria->mensaje
    );

    printf("====================================\n");

    sem_post(sem_cliente);
}

    return 0;
}