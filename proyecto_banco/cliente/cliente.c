#include <stdio.h>
#include <semaphore.h>

#include "../common/ipc.h"
#include "../common/structs.h"

#include "cliente_ui.h"

Solicitud* memoria;

sem_t* sem_servidor;
sem_t* sem_cliente;

int sesion = 0;

void consultar() {

    memoria->tipo = TIPO_CONSULTA;

    sem_post(sem_servidor);

    sem_wait(sem_cliente);

    clear();

    mvprintw(
        5,
        5,
        "Saldo actual: %.2f",
        memoria->saldo
    );

    getch();
}

void depositar_cliente() {

    echo();

    clear();

    memoria->tipo = TIPO_DEPOSITO;

    mvprintw(5, 5, "Monto: ");

    scanw("%f", &memoria->monto);

    noecho();

    sem_post(sem_servidor);

    sem_wait(sem_cliente);

    mvprintw(7, 5, "%s", memoria->mensaje);

    getch();
}

void retirar_cliente() {

    echo();

    clear();

    memoria->tipo = TIPO_RETIRO;

    mvprintw(5, 5, "Monto: ");

    scanw("%f", &memoria->monto);

    noecho();

    sem_post(sem_servidor);

    sem_wait(sem_cliente);

    mvprintw(7, 5, "%s", memoria->mensaje);

    getch();
}

void panel_bancario() {

    int op;

    while(1) {

        clear();

        mvprintw(2, 5, "===== PANEL BANCARIO =====");

        mvprintw(4, 5, "1. Consultar saldo");

        mvprintw(5, 5, "2. Depositar");

        mvprintw(6, 5, "3. Retirar");

        mvprintw(7, 5, "4. Logout");

        mvprintw(9, 5, "Seleccione: ");

        scanw("%d", &op);

        switch(op) {

            case 1:
                consultar();
                break;

            case 2:
                depositar_cliente();
                break;

            case 3:
                retirar_cliente();
                break;

            case 4:
                return;
        }
    }
}

void login() {

    echo();

    clear();

    memoria->tipo = TIPO_LOGIN;

    mvprintw(2, 5, "Usuario: ");
    getstr(memoria->usuario);

    mvprintw(3, 5, "Password: ");
    getstr(memoria->password);

    noecho();

    sem_post(sem_servidor);

    sem_wait(sem_cliente);

    mvprintw(6, 5, "%s", memoria->mensaje);

    getch();

    if(memoria->respuesta == 1) {

        panel_bancario();
    }
}

void registro() {

    echo();

    clear();

    memoria->tipo = TIPO_REGISTRO;

    mvprintw(2, 5, "Usuario: ");
    getstr(memoria->usuario);

    mvprintw(3, 5, "Correo: ");
    getstr(memoria->correo);

    mvprintw(4, 5, "Password: ");
    getstr(memoria->password);

    noecho();

    sem_post(sem_servidor);

    sem_wait(sem_cliente);

    mvprintw(6, 5, "%s", memoria->mensaje);

    getch();
}

int main() {

    memoria = conectar_memoria();

    sem_servidor = conectar_semaforo_servidor();

    sem_cliente = conectar_semaforo_cliente();

    iniciar_ui();

    int opcion;

    while(1) {

        menu_principal();

        scanw("%d", &opcion);

        switch(opcion) {

            case 1:
                login();
                break;

            case 2:
                registro();
                break;

            case 3:

                finalizar_ui();

                return 0;
        }
    }

    return 0;
}