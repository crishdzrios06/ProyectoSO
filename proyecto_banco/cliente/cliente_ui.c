#include "cliente_ui.h"

void iniciar_ui() {

    initscr();

    cbreak();

    noecho();

    keypad(stdscr, TRUE);
}

void finalizar_ui() {

    endwin();
}

void menu_principal() {

    clear();

    mvprintw(2, 5, "===== SISTEMA BANCARIO =====");

    mvprintw(4, 5, "1. Login");

    mvprintw(5, 5, "2. Registro");

    mvprintw(6, 5, "3. Salir");

    mvprintw(8, 5, "Seleccione: ");

    refresh();
}