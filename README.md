# Sistema Bancario Concurrente en C

## Descripción

Sistema bancario concurrente desarrollado en lenguaje C utilizando:

- Memoria compartida POSIX
- Semáforos POSIX
- Hilos
- Archivos planos
- ncurses

El sistema permite:

- Registro de usuarios
- Inicio de sesión
- Consulta de saldo
- Depósitos
- Retiros
- Comunicación cliente-servidor concurrente

---

# Requisitos

Trabajar en Linux o WSL Ubuntu.

## Instalar dependencias

```bash
sudo apt update

sudo apt install build-essential

sudo apt install libncurses5-dev

sudo apt install libssl-dev

sudo apt install tree
```

---

# Estructura del proyecto

```txt
proyecto_banco/
├── Makefile
├── admin
├── cliente
├── common
├── data
└── servidor
```

---

# Compilación

Entrar a la carpeta del proyecto:

```bash
cd ~/proyecto_banco
```

Compilar:

```bash
make clean
make
```

Si todo salió correctamente aparecerán:

```txt
servidor.out
cliente.out
admin.out
```

---

# Ejecutar el sistema

## 1. Iniciar servidor

Abrir una terminal:

```bash
./servidor.out
```

El servidor permanecerá activo esperando clientes.

---

## 2. Iniciar cliente

Abrir OTRA terminal:

```bash
cd ~/proyecto_banco

./cliente.out
```

---

# Funcionalidades actuales

## Cliente

- Registro
- Login
- Consulta de saldo
- Depósito
- Retiro

---

## Servidor

- Procesamiento concurrente
- Gestión de usuarios
- Actualización de saldos
- Registro de movimientos
- Logs de operaciones

---

# Archivos utilizados

## usuarios.txt

Guarda:

```txt
usuario|correo|password_hash|saldo
```

---

## movimientos.txt

Guarda:

```txt
usuario|tipo|monto
```

Ejemplo:

```txt
juan|DEPOSITO|500
juan|RETIRO|200
```

---

# Tecnologías utilizadas

## IPC

- shm_open()
- mmap()

## Semáforos

- sem_open()
- sem_wait()
- sem_post()

## Hilos

- pthread_create()

## Interfaz

- ncurses

---

# Restricciones cumplidas

- Solo lenguaje C  
- Sin sockets  
- Sin gbd 
- Uso de semáforos  
- Uso de memoria compartida  
- Uso de hilos  
- Uso de archivos planos  
- Uso de ncurses  

---

# Cómo detener el servidor

En la terminal del servidor:

```bash
CTRL + C
```

---

# Solución de errores comunes

## Error de ncurses

Instalar:

```bash
sudo apt install libncurses5-dev
```

---

## Error de OpenSSL

Instalar:

```bash
sudo apt install libssl-dev
```

---

## Error de memoria compartida

Eliminar recursos IPC:

```bash
rm /dev/shm/sem.sem_servidor

rm /dev/shm/sem.sem_cliente

rm /dev/shm/sistema_banco
```

---

# Ver estructura del proyecto

```bash
tree
```

---

# Ejecutar múltiples clientes

Abrir varias terminales y ejecutar:

```bash
./cliente.out
```

Esto permite probar concurrencia real.

---

