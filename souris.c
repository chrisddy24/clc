
/*gcc -o EXEC projetc.c -Wall -lncurses*/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <ncurses.h> 
#include <unistd.h>

/*meme prog que donné mais utilisation de tcoordinates*/
typedef struct 
	{
		int x;
		int y;
	}tcoordinates;

tcoordinates m_click;/*L(m_click.x) pour désigner la ligne et C(m_click.y) la colonne du click de la souris*/ 

/**Initialisation de ncurses**/ // R a modif
void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}


/**Initialisation des couleurs**/ //r a modif
void ncurses_couleurs() {
  /* Vérification du support de la couleur */
  if(has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    exit(EXIT_FAILURE);
  }

  /* Activation des couleurs */
  start_color();

}

/**Initialisation de la souris**/  //RAM
void ncurses_souris() {
  if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
    endwin();
    fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
    exit(EXIT_FAILURE);
  }

  if(has_mouse() != TRUE) {
    endwin();
    fprintf(stderr, "Aucune souris n'est détectée.\n");
    exit(EXIT_FAILURE);
  }
}


/**Pour récupérer les coordonnées (x,y) du clik de la souris**/
int click_souris()
{
  MEVENT event ;
  int ch;

  while((ch = getch()) != KEY_F(1)) 
  {
    switch(ch) 
    {
      case KEY_F(2): /*Pour quitter le jeu*/
	return 1;
      case KEY_MOUSE:
        if(getmouse(&event) == OK) 
	{
	  m_click.x = event.x;
	  m_click.y = event.y;
	  if(event.bstate & BUTTON1_CLICKED)
	  {
	    if (m_click.x< 51 && m_click.y<132) /*Vous pouvez changer ici et mettre les dimensions de votre plateau de jeu*/
	    {
	    return 0;
	    }
	  }
	}
    }
  }
  return 0;
}




int main() {
  
  
  ncurses_initialiser(); //Initialisation de ncurses
  //ncurses_couleurs();
  ncurses_souris();
  scrollok(stdscr, TRUE);
  
  while (1)
  {
    click_souris();
    clear();
    printw("Vous avez cliqué sur la poisition (%d,%d)\n", m_click.x, m_click.y);
  }
  endwin(); // Suspendre la sesion ncurses et restorer le terminal
  return 0;
}

