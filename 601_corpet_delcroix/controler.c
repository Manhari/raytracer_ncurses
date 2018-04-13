/* Definitions */

/* Inclusion des bibliothèques natives utilisées */
#include <ncurses.h>	/* */
#include <signal.h>     /* */
#include <stdio.h>      /* */
#include <stdlib.h>     /* */
#include <time.h>		/* */

/* Inclusion de nos fichiers d'en-tête */
#include "display.h"    /* Pour les fonctionnalités liées a ncurses */

/* Définition des constantes */
#define POSX    4
#define POSY    2
#define X_COORD	13
#define Y_COORD	13
#define Z_COORD	13
#define RADIUS	13
#define COLOR	13
#define X_DIR	13
#define Y_DIR	13
#define Z_DIR	13
#define SPEED	13
#define CREATE	13
#define PAUSE	13

/* Variables globales */

/* Fonctions propres au contrôleur */

void handler(int code) {
}

void show_command_synthax(char *program_name) {
    fprintf(stderr,"%s [NOMBRE_D_OBJETS]\n", program_name);
<<<<<<< HEAD
    fprintf(stderr,"\tWhere :\n\t[NOMBRE_D_OBJETS] is the number of objects\n");
=======
    fprintf(stderr,"\tWhere :\n\t[NOMBRE_D_OBJETS] is the maximum number of object\n");
>>>>>>> 08e785e0a429fb8cd7e59ee8f971e15c5d95a8d8
}

/* Programme principal du client */
int main(int argc, char *argv[]) {
<<<<<<< HEAD
	/* Variables */
	WINDOW* window;
	int nObjects = 0, ch, i;

    /* Vérification des arguments de la commande ./client */
    if(argc < 2) {
        fprintf(stderr,"Too few arguments to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        fprintf(stderr,"Too many arguments to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[1]) < 0) {
=======
    /* Verification des donnees passees en argument de la commande ./client */
    if(argc<2) {
        fprintf(stderr,"Too few argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc>2) {
        fprintf(stderr,"Too many argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[1])==0) {
>>>>>>> 08e785e0a429fb8cd7e59ee8f971e15c5d95a8d8
        fprintf(stderr,"Invalid argument : %s\n", argv[1]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    }

	/* Récupération des arguments */
	nObjects = atoi(argv[1]);

	/* Démarrage ncurses */
	ncurses_initializer();
	ncurses_colors();
	ncurses_mouse();

	/* Initialisation des fenêtres */
	window = newwin(LINES - 2*POSY - 1, COLS - 2*POSX - 1, POSY, POSX);
	box(window, 0, 0);
	wattron(window, A_BOLD);
	for(i = 1; i <= nObjects; i++) {
		int cursor = 1, tmp = 1;

		/* Numérotation de l'objet */
		mvwprintw(window, i, cursor, "objet %d : ", i);
		cursor += 10;

		/* Coordonnées x*/
		mvwprintw(window, i, cursor, "x");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Coordonnées y*/
		mvwprintw(window, i, cursor, "y");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Coordonnées z*/
		mvwprintw(window, i, cursor, "z");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Rayon*/
		mvwprintw(window, i, cursor, "r");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Couleur*/
		srand(time(NULL) + i);
		tmp = (rand() % 4) + 1;
		mvwprintw(window, i, cursor, "c");
		cursor += 2;
		wattron(window, COLOR_PAIR(tmp));
		mvwprintw(window, i, cursor, "   ");
		cursor += 5;
		wattroff(window, COLOR_PAIR(tmp));

		/* Direction x*/
		mvwprintw(window, i, cursor, "x");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Direction y*/
		mvwprintw(window, i, cursor, "y");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Direction z*/
		mvwprintw(window, i, cursor, "z");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Vitesse*/
		mvwprintw(window, i, cursor, "v");
		cursor += 2;
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " 0 ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Création et suppression x*/
		srand(time(NULL) + tmp);
		tmp = (rand() % 2) + 1;
		wattron(window, COLOR_PAIR(tmp));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, "   ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(tmp));

		/* Pause et reprise x*/
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i, cursor, " || ");
		cursor += 5;
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));
	}

	/* Rafraichissement de la fenêtre */
	wrefresh(window);

	/* Maintien du programme */
	while((ch = getch()) != KEY_F(2)) { }

	/* Suppression des fenêtres */
	delwin(window);

	/* Arrêt de ncurses */
	ncurses_stopper();

    return EXIT_SUCCESS;
}
