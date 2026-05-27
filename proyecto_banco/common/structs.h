#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_NOMBRE 100
#define MAX_CORREO 100
#define MAX_PASSWORD 256
#define MAX_MENSAJE 512

#define TIPO_LOGIN 1
#define TIPO_REGISTRO 2
#define TIPO_CONSULTA 3
#define TIPO_DEPOSITO 4
#define TIPO_RETIRO 5

typedef struct {

    int tipo;

    char usuario[MAX_NOMBRE];
    char correo[MAX_CORREO];
    char password[MAX_PASSWORD];

    float monto;
    float saldo;

    char mensaje[MAX_MENSAJE];

    int respuesta;

} Solicitud;

#endif