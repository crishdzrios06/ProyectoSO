#include <ncurses.h>

int main() {

    initscr();

    mvprintw(2, 5, "=== PANEL ADMINISTRADOR ===");
    mvprintw(4, 5, "1. Usuarios");
    mvprintw(5, 5, "2. Productos");
    mvprintw(6, 5, "3. Reportes");

    refresh();

    getch();

    endwin();

    return 0;
}