CC = gcc

CFLAGS = -Wall -pthread -lrt

NCURSES = -lncurses

SSL = -lssl -lcrypto



all: servidor.out cliente.out admin.out



servidor.out:
	gcc servidor/servidor.c servidor/manejador_clientes.c common/ipc.c common/seguridad.c -o servidor.out $(CFLAGS) $(SSL)



cliente.out:
	gcc cliente/cliente.c cliente/cliente_ui.c common/ipc.c -o cliente.out $(CFLAGS) $(NCURSES)



admin.out:
	gcc admin/admin.c common/ipc.c -o admin.out $(CFLAGS) $(NCURSES)



clean:
	rm -f *.out