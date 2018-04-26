#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/* Fonctions */
void ncurses_initializer();
void ncurses_stopper();
void ncurses_colors();
void ncurses_mouse();
int mouse_getpos(int *x, int *y, int *bouton);

#endif