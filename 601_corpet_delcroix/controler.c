/* Definitions */
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

/* Inclusion des bibliothèques natives utilisées */
#include <errno.h>		/* Pour la gestion d'erreur */
#include <ncurses.h>	/* Pour l'affichage lors de l'utilisation */
#include <signal.h>     /* Pour la gestion des signaux */
#include <stdio.h>      /* Pour l'affichage hors ncurses */
#include <stdlib.h>     /* Pour les éléments standards */

/* Inclusion de nos fichiers d'en-tête */
#include "display.h"    /* Pour les fonctionnalités liées a ncurses */

/* Définition des constantes */
#define POSX		0	/* Marge horizontale */
#define POSY		0	/* Marge verticale */
#define X_COORD		14	/* Position de la valeur de la coordonnée en X */
#define Y_COORD		21	/* Position de la valeur de la coordonnée en Y */
#define Z_COORD		28	/* Position de la valeur de la coordonnée en Z */
#define RADIUS		35	/* Position de la valeur du rayon */
#define COLOR		42	/* Position de la couleur */
#define X_DIR		49	/* Position de la valeur de la direction en X */
#define Y_DIR		56	/* Position de la valeur de la direction en Y */
#define Z_DIR		63	/* Position de la valeur de la direction en Z */
#define SPEED		70	/* Position de la valeur de la vitesse */
#define CREATE		75	/* Position de la bascule de création */
#define PAUSE		80	/* Position de la bascule de pause */

/* Variables globales */
int create = 0;			/* Sauvegarde de la bascule de création */
int pause = 0;			/* Sauvegarde de la bascule de pause */

/* Gestion des signaux reçus par le controleur */
void handler(int sig) {
	if(sig == SIGSEGV) {
		ncurses_stopper();
		printf("Erreur : segmentation fault.\n");
		exit(EXIT_FAILURE);
	}
}

/* Affichage de la commande correcte en cas d'erreur d'exécution */
void show_command_synthax(char *program_name) {
    fprintf(stderr,"%s [NOMBRE_D_OBJETS]\n", program_name);
    fprintf(stderr,"\tWhere :\n\t[NOMBRE_D_OBJETS] is the maximum number of object\n");
}

/* Mise à jour des données affichées */
void refresh_window(WINDOW* window, int nb_objects, int** object_data) {
	int i;
	for(i = 0; i < nb_objects; i++) {
		/* Numérotation de l'objet */
		mvwprintw(window, i+1, 1, "objet %d : ", i);

		/* Coordonnées x */
		mvwprintw(window, i+1, X_COORD - 2, "x");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, X_COORD, " %d ", object_data[i][0]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Coordonnées y */
		mvwprintw(window, i+1, Y_COORD - 2, "y");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, Y_COORD, " %d ", object_data[i][1]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Coordonnées z */
		mvwprintw(window, i+1, Z_COORD - 2, "z");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, Z_COORD, " %d ", object_data[i][2]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Rayon */
		mvwprintw(window, i+1, RADIUS - 2, "r");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, RADIUS, " %d ", object_data[i][3]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Couleur */
		mvwprintw(window, i+1, COLOR - 2, "c");
		wattron(window, COLOR_PAIR(object_data[i][4] + 1));
		mvwprintw(window, i+1, COLOR, "   ");
		wattroff(window, COLOR_PAIR(object_data[i][4] + 1));

		/* Direction x */
		mvwprintw(window, i+1, X_DIR - 2, "x");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, X_DIR, " %d ", object_data[i][5]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Direction y */
		mvwprintw(window, i+1, Y_DIR - 2, "y");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, Y_DIR, " %d ", object_data[i][6]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Direction z */
		mvwprintw(window, i+1, Z_DIR - 2, "z");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, Z_DIR, " %d ", object_data[i][7]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Vitesse */
		mvwprintw(window, i+1, SPEED - 2, "v");
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, SPEED, " %d ", object_data[i][8]);
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));

		/* Création et suppression */
		wattron(window, COLOR_PAIR((object_data[i][9] % 2) + 1));
		wattroff(window, A_BOLD);
		mvwprintw(window, i+1, CREATE, "   ");
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR((object_data[i][9] % 2) + 1));

		/* Pause et reprise */
		wattron(window, COLOR_PAIR(5));
		wattroff(window, A_BOLD);
		if(object_data[i][10] == 0) {
			mvwprintw(window, i+1, PAUSE, " |> ");
		} else {
			mvwprintw(window, i+1, PAUSE, " || ");
		}
		wattron(window, A_BOLD);
		wattroff(window, COLOR_PAIR(5));
	}

	/* Pause et reprise - global */
	wattron(window, COLOR_PAIR(5));
	wattroff(window, A_BOLD);
	if(pause == 0) {
		mvwprintw(window, nb_objects + 2, PAUSE, " |> ");
	} else {
		mvwprintw(window, nb_objects + 2, PAUSE, " || ");
	}
	wattron(window, A_BOLD);
	wattroff(window, COLOR_PAIR(5));

	/* Création et suppression - global */
	wattron(window, COLOR_PAIR(create + 1));
	wattroff(window, A_BOLD);
	mvwprintw(window, nb_objects + 2, CREATE, "   ");
	wattron(window, A_BOLD);
	wattroff(window, COLOR_PAIR(create + 1));

	/* Stop */
	wattron(window, COLOR_PAIR(5));
	wattroff(window, A_BOLD);
	mvwprintw(window, nb_objects + 2, 1, " STOP ");
	wattron(window, A_BOLD);
	wattroff(window, COLOR_PAIR(5));

	/* Rafraichissement de la fenêtre */
	wrefresh(window);
}

/* Programme principal du client */
int main(int argc, char *argv[]) {
	/* Variables */
	WINDOW* window;
	int nb_objects = 0, ch, i, j, **object_data, mouse_x, mouse_y, button;

	signal(SIGSEGV, handler);

    /* Vérification des arguments de la commande ./client */
    if(argc < 2) {
        fprintf(stderr, "Too few arguments to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        fprintf(stderr, "Too many arguments to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[1]) < 0) {
        fprintf(stderr, "Invalid argument : %s\n", argv[1]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    }

	/* Récupération des arguments */
	nb_objects = atoi(argv[1]);

	/* Démarrage ncurses */
	ncurses_initializer();
	ncurses_colors();
	ncurses_mouse();

	/* Vérification de la taille du terminal */
	if(LINES < nb_objects + 4 + POSY || COLS < PAUSE + 5 + POSX) {
		int lines = LINES;
		int cols = COLS;
		ncurses_stopper();
        fprintf(stderr, "Terminal is too small, need %d / %d, got %d / %d\n", nb_objects + 4 + POSY, PAUSE + 5 + POSX, lines, cols);
        exit(EXIT_FAILURE);
    }

	/* Initialisation du tableau */
	object_data = (int**) malloc(nb_objects*sizeof(int*));
	for(i = 0; i < nb_objects; i++) {
		object_data[i] = (int*) malloc(11*sizeof(int));
		for(j = 0; j < 11; j++) {
			object_data[i][j] = 0;
		}
	}

	/* Initialisation des fenêtres */
	window = newwin(nb_objects + 4, PAUSE + 5, POSY, POSX);
	box(window, 0, 0);
	wattron(window, A_BOLD);
	refresh_window(window, nb_objects, object_data);

	/* Déroulement du programme */
	while((ch = getch()) != KEY_F(2)) {
		/* Si clic souris */
		if(ch == KEY_MOUSE) {
			if(mouse_getpos(&mouse_x, &mouse_y, &button) == OK) {
				if((mouse_y >= POSY + 1) && (mouse_y < POSY + nb_objects + 1)) {
					if((mouse_x >= POSX + X_COORD) && (mouse_x < POSX + X_COORD + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][0]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][0]--;
						}
					} else if((mouse_x >= POSX + Y_COORD) && (mouse_x < POSX + Y_COORD + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][1]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][1]--;
						}
					} else if((mouse_x >= POSX + Z_COORD) && (mouse_x < POSX + Z_COORD + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][2]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][2]--;
						}
					} else if((mouse_x >= POSX + RADIUS) && (mouse_x < POSX + RADIUS + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][3]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][3]--;
						}
					} else if((mouse_x >= POSX + COLOR) && (mouse_x < POSX + COLOR + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][4]++;
							if(object_data[mouse_y - POSY - 1][4] == 4) {
								object_data[mouse_y - POSY - 1][4] = 0;
							}
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][4]--;
							if(object_data[mouse_y - POSY - 1][4] == -1) {
								object_data[mouse_y - POSY - 1][4] = 3;
							}
						}
					} else if((mouse_x >= POSX + X_DIR) && (mouse_x < POSX + X_DIR + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][5]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][5]--;
						}
					} else if((mouse_x >= POSX + Y_DIR) && (mouse_x < POSX + Y_DIR + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][6]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][6]--;
						}
					} else if((mouse_x >= POSX + Z_DIR) && (mouse_x < POSX + Z_DIR + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][7]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][7]--;
						}
					} else if((mouse_x >= POSX + SPEED) && (mouse_x < POSX + SPEED + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							object_data[mouse_y - POSY - 1][8]++;
						} else if (button & BUTTON3_CLICKED) {
							object_data[mouse_y - POSY - 1][8]--;
						}
					} else if((mouse_x >= POSX + CREATE) && (mouse_x < POSX + CREATE + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED || button & BUTTON3_CLICKED) {
							if(object_data[mouse_y - POSY - 1][9] == 0) {
								object_data[mouse_y - POSY - 1][9] = 1;
							} else if(object_data[mouse_y - POSY - 1][9] == 1) {
								object_data[mouse_y - POSY - 1][9] = 0;
							}
						}
					} else if((mouse_x >= POSX + PAUSE) && (mouse_x < POSX + PAUSE + 4)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED || button & BUTTON3_CLICKED) {
							if(object_data[mouse_y - POSY - 1][10] == 0) {
								object_data[mouse_y - POSY - 1][10] = 1;
							} else if(object_data[mouse_y - POSY - 1][10] == 1) {
								object_data[mouse_y - POSY - 1][10] = 0;
							}
						}
					}
				} else if((mouse_y >= POSY + nb_objects + 2) && (mouse_y < POSY + nb_objects + 3)) {
					if((mouse_x >= POSX + 1) && (mouse_x < POSX + 7)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED) {
							ncurses_stopper();
							exit(EXIT_SUCCESS);
						}
					} else if((mouse_x >= POSX + CREATE) && (mouse_x < POSX + CREATE + 3)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED || button & BUTTON3_CLICKED) {
							int i;
							if(create == 0) {
								create = 1;
							} else {
								create = 0;
							}
							for(i = 0; i < nb_objects; i++) {
								object_data[i][9] = create;
							}
						}
					} else if((mouse_x >= POSX + PAUSE) && (mouse_x < POSX + PAUSE + 4)) {
						if(button & BUTTON1_CLICKED || button & BUTTON1_DOUBLE_CLICKED || button & BUTTON3_CLICKED) {
							int i;
							if(pause == 0) {
								pause = 1;
							} else {
								pause = 0;
							}
							for(i = 0; i < nb_objects; i++) {
								object_data[i][10] = pause;
							}
						}
					}
				}
				refresh_window(window, nb_objects, object_data);
			}
		}
	}

	/* Suppression des fenêtres */
	delwin(window);

	/* Libération mémoire */
	for(i = 0; i < nb_objects; i++) {
		free(object_data[i]);
	}
	free(object_data);

	/* Arrêt de ncurses */
	ncurses_stopper();

    return EXIT_SUCCESS;
}
