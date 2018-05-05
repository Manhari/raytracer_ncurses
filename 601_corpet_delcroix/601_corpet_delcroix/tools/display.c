#include <ncurses.h>
#include <stdlib.h>

#include "display.h"

/* Démarrage de ncurses */
void ncurses_initializer() {
	initscr();				/* Demarre le mode ncurses */
	cbreak();				/* Pour les saisies clavier (desac. mise en buffer) */
	noecho();				/* Desactive l'affichage des caracteres saisis */
	keypad(stdscr, TRUE);	/* Active les touches specifiques */
	refresh();				/* Met a jour l'affichage */
	curs_set(FALSE);		/* Masque le curseur */
}

/* Arrêt de ncurses */
void ncurses_stopper() {
	endwin();
}

/* Activation des couleurs */
void ncurses_colors() {
	/* Vérification du support de la couleur */
	if(has_colors()==FALSE) {
		ncurses_stopper();
		fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
		exit(EXIT_FAILURE);
	}

	/* Activation des couleurs */
	start_color();

	/* Definition de la palette */
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_BLUE, COLOR_BLUE);	
	init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
}

/* Activation de la souris */
void ncurses_mouse() {
	if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
		ncurses_stopper();
		fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
		exit(EXIT_FAILURE);
	}

	if(has_mouse()!=TRUE) {
		ncurses_stopper();
		fprintf(stderr, "Aucune souris n'est détectée.\n");
		exit(EXIT_FAILURE);
	}
}

/* Récupération de la position de la souris */
int mouse_getpos(int *x, int *y, int *bouton) {
  MEVENT event;
  int resultat=getmouse(&event);
 
  if(resultat==OK) {
    *x = event.x;
    *y = event.y;
    if(bouton != NULL) *bouton=event.bstate;
  }
  return resultat;
}

/**
 * Check the size of the terminal.
 * @param height the height needed
 * @param width the width needed
 * @return TRUE if the sizes are OK else returns FALSE
 */
int ncurses_checksize(int height, int width) {
  int result=TRUE;

  if((COLS < width) || (LINES < height))
    result=FALSE;

  return result;
}