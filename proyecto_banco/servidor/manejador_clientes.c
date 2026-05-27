#include "manejador_clientes.h"
#include "../common/seguridad.h"

#include <stdio.h>
#include <string.h>

void guardar_movimiento(char* usuario, char* tipo, float monto) {

    FILE* f = fopen("data/movimientos.txt", "a");

    if(!f) return;

    fprintf(f, "%s|%s|%.2f\n", usuario, tipo, monto);

    fclose(f);
}

void login_usuario(Solicitud* s) {

    FILE* f = fopen("data/usuarios.txt", "r");

    if(!f) {

        s->respuesta = 0;

        strcpy(s->mensaje, "Error archivo usuarios");

        return;
    }

    char linea[512];

    char usuario[100];
    char correo[100];
    char password[256];

    float saldo;

    char password_hash[256];

    hash_password(s->password, password_hash);

    while(fgets(linea, sizeof(linea), f)) {

        sscanf(
            linea,
            "%[^|]|%[^|]|%[^|]|%f",
            usuario,
            correo,
            password,
            &saldo
        );

        if(
            strcmp(usuario, s->usuario) == 0 &&
            strcmp(password, password_hash) == 0
        ) {

            s->respuesta = 1;

            s->saldo = saldo;

            strcpy(s->mensaje, "Login correcto");

            fclose(f);

            return;
        }
    }

    fclose(f);

    s->respuesta = 0;

    strcpy(s->mensaje, "Credenciales incorrectas");
}

void registrar_usuario(Solicitud* s) {

    FILE* f = fopen("data/usuarios.txt", "a");

    if(!f) {

        s->respuesta = 0;

        strcpy(s->mensaje, "Error archivo");

        return;
    }

    char password_hash[256];

    hash_password(s->password, password_hash);

    fprintf(
        f,
        "%s|%s|%s|1000\n",
        s->usuario,
        s->correo,
        password_hash
    );

    fclose(f);

    s->respuesta = 1;

    strcpy(s->mensaje, "Registro exitoso");
}

void consultar_saldo(Solicitud* s) {

    FILE* f = fopen("data/usuarios.txt", "r");

    if(!f) return;

    char linea[512];

    char usuario[100];
    char correo[100];
    char password[256];

    float saldo;

    while(fgets(linea, sizeof(linea), f)) {

        sscanf(
            linea,
            "%[^|]|%[^|]|%[^|]|%f",
            usuario,
            correo,
            password,
            &saldo
        );

        if(strcmp(usuario, s->usuario) == 0) {

            s->saldo = saldo;

            s->respuesta = 1;

            strcpy(s->mensaje, "Consulta exitosa");

            fclose(f);

            return;
        }
    }

    fclose(f);
}

void actualizar_saldo(
    char* usuario_busqueda,
    float nuevo_saldo
) {

    FILE* f = fopen("data/usuarios.txt", "r");

    FILE* temp = fopen("data/temp.txt", "w");

    char linea[512];

    char usuario[100];
    char correo[100];
    char password[256];

    float saldo;

    while(fgets(linea, sizeof(linea), f)) {

        sscanf(
            linea,
            "%[^|]|%[^|]|%[^|]|%f",
            usuario,
            correo,
            password,
            &saldo
        );

        if(strcmp(usuario, usuario_busqueda) == 0) {

            fprintf(
                temp,
                "%s|%s|%s|%.2f\n",
                usuario,
                correo,
                password,
                nuevo_saldo
            );
        }
        else {

            fprintf(
                temp,
                "%s",
                linea
            );
        }
    }

    fclose(f);

    fclose(temp);

    remove("data/usuarios.txt");

    rename(
        "data/temp.txt",
        "data/usuarios.txt"
    );
}

void depositar(Solicitud* s) {

    consultar_saldo(s);

    float nuevo = s->saldo + s->monto;

    actualizar_saldo(
        s->usuario,
        nuevo
    );

    guardar_movimiento(
        s->usuario,
        "DEPOSITO",
        s->monto
    );

    s->saldo = nuevo;

    s->respuesta = 1;

    strcpy(s->mensaje, "Deposito exitoso");
}

void retirar(Solicitud* s) {

    consultar_saldo(s);

    if(s->saldo < s->monto) {

        s->respuesta = 0;

        strcpy(s->mensaje, "Fondos insuficientes");

        return;
    }

    float nuevo = s->saldo - s->monto;

    actualizar_saldo(
        s->usuario,
        nuevo
    );

    guardar_movimiento(
        s->usuario,
        "RETIRO",
        s->monto
    );

    s->saldo = nuevo;

    s->respuesta = 1;

    strcpy(s->mensaje, "Retiro exitoso");
}

void procesar_solicitud(Solicitud* s) {

    switch(s->tipo) {

        case TIPO_LOGIN:
            login_usuario(s);
            break;

        case TIPO_REGISTRO:
            registrar_usuario(s);
            break;

        case TIPO_CONSULTA:
            consultar_saldo(s);
            break;

        case TIPO_DEPOSITO:
            depositar(s);
            break;

        case TIPO_RETIRO:
            retirar(s);
            break;

        default:

            s->respuesta = 0;

            strcpy(
                s->mensaje,
                "Operacion invalida"
            );
    }
}