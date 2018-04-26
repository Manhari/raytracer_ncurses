/* Definitions */

#define POSX				4	/* */
#define POSY				2	/* */
#define WIDTH_MAX			90	/* */
#define WIDTH_MIN			30	/* */

#define MAX(A,B) ((A>B)?A:B)

/* Include des bibliotheques natives utilises */
#include <math.h>				/* */
#include <ncurses.h>			/* */
#include <signal.h>				/* */
#include <stdio.h>				/* */
#include <stdlib.h>				/* */
#include <time.h>				/* */

/* Include de nos fichiers d'en-tete */
#include "tools/display.h"		/* Pour les fonctionnalites liees a ncurses */

/* Variables globales */

WINDOW *main_window=NULL, *title_window=NULL, *manager_window=NULL;
int height_main, height_manager=5, height_title=3;

/* Fonctions propres au controleur */

void handler(int code) {
    if(code==SIGINT || code==SIGSEGV) {
        /* Affichage du code du signal reçu*/
        printf("SIGNAL %i reçu\n", code);

        /* Destruction des fenetres */
        delwin(manager_window);
        delwin(title_window);
        /*delwin(main_window);*/

        /* Arret de ncurses */
        ncurses_stopper();

        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

void show_command_synthax(char *program_name) {
    fprintf(stderr,"%s [NOMBRE_D_OBJETS]\n", program_name);
    fprintf(stderr,"\tWhere :\n\t[NOMBRE_D_OBJETS] is the maximum number of object\n");
}

/* Programme principal du client */
int main(int argc, char *argv[]) {
    /* Declaration des variables */
	/*struct sigaction action;*/
    int current_position=0, i=0, maximum_objects=0, /*tmp=1, */width=0;
    char c;

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
        fprintf(stderr,"Invalid argument : %s\n", argv[1]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Mise en place du handler */
    /*if((sigaction(SIGINT, &action, NULL)==-1) || (sigaction(SIGSEGV, &action, NULL)==-1)) {
        perror("sigaction(SIGINT, &action, NULL) || sigaction(SIGSEGV, &action, NULL)");
        exit(EXIT_FAILURE);
    }*/

    /* Initialisation des variables */
    maximum_objects=atoi(argv[1]);
    height_manager+=maximum_objects;
    height_main=height_manager+height_title;

    /* Initialisation de ncurses */
	ncurses_initializer();
	ncurses_colors();
    ncurses_mouse();

    /* Calcul de la largeur de l'affichage */
	width=MAX(COLS-2*POSX, WIDTH_MIN);

    /* Initialisation des fenetres */
    /*main_window=newwin(height_main, width, POSY, POSX);*/
	manager_window=newwin(/*main_window, */height_manager, width, POSY+1+height_title, POSX+2);
	title_window=newwin(/*main_window, */height_title, width, POSY+1, POSX+2);

    /* Création des bordures */
	/*box(main_window, 0, 0);*/
	box(manager_window, 0, 0);
	box(title_window, 0, 0);

    /* Affichage du manager */
    wattron(manager_window, A_BOLD);
	for(i=1; i<=maximum_objects; i++) {
        /* Numerotation de l'objet */
        current_position+=2;
        mvwprintw(manager_window, 1, current_position, "objet %i : ", i);

        /* Coordonnees x */
        /*mvwprintw(manager_window, i, cursor, "x");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Coordonnees y */
        /*mvwprintw(manager_window, i, cursor, "y");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Coordonnees z */
        /*mvwprintw(manager_window, i, cursor, "z");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Rayon */
        /*mvwprintw(manager_window, i, cursor, "r");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Couleur */
        /*srand(time(NULL)+i);
        tmp=(rand()%4)+1;
        mvwprintw(manager_window, i, cursor, "c");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(tmp));
        mvwprintw(manager_window, i, cursor, "   ");
        cursor+=5;
        wattroff(manager_window, COLOR_PAIR(tmp));*/

        /* Direction x */
        /*mvwprintw(manager_window, i, cursor, "x");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Direction y */
        /*mvwprintw(manager_window, i, cursor, "y");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Direction z */
        /*mvwprintw(manager_window, i, cursor, "z");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Vitesse */
        /*mvwprintw(manager_window, i, cursor, "v");
        cursor+=2;
        wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " 0 ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/

        /* Creation et suppression x */
        /*srand(time(NULL)+tmp);
        tmp=(rand()%2)+1;
        wattron(manager_window, COLOR_PAIR(tmp));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, "   ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(tmp));*/

        /* Pause et reprise x */
        /*wattron(manager_window, COLOR_PAIR(5));
        wattroff(manager_window, A_BOLD);
        mvwprintw(manager_window, i, cursor, " || ");
        cursor+=5;
        wattron(manager_window, A_BOLD);
        wattroff(manager_window, COLOR_PAIR(5));*/
	}
    wattroff(manager_window, A_BOLD);

    /* Affichage du titre */
	wattron(title_window, A_BOLD);
	mvwaddch(title_window, 1, width/2-8, ACS_RARROW);
	mvwprintw(title_window, 1, width/2-5, "CONTROLER");
	mvwaddch(title_window, 1, width/2+6, ACS_LARROW);
	wattroff(title_window, A_BOLD);

	/* Mise a jour de l'affichage */
	/*wrefresh(main_window);*/
	wrefresh(manager_window);
	wrefresh(title_window);

    /* Maintien du programme */
    while((c=getch())!=KEY_F(2)) {}

    return EXIT_SUCCESS;
}