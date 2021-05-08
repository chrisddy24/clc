#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

// definition of the screen size for the moment
#define row 27
#define col 48
		//getmaxyx(stdscr,row,col);


// definition of constants according to the screen size defined
 # define  r1 0
 # define r2 row/3
 # define r3 2*row/3
 # define c1 0
 # define c2 col/3
 # define c3 2*col/3 
 // types definition
 typedef struct 
	{
		int x;
		int y;
	}tcoordinates;

tcoordinates gplace[3][3]={ //original places of wins
			{ {r1, c1},{r1, c2},{r1, c3} },
			{ {r2, c1},{r2, c2},{r2, c3} },
			{ {r3, c1},{r3, c2},{r3, c3} },	
		           };
		           
tcoordinates place[3][3]={ //original places of wins
			{ {r1, c1},{r1, c2},{r1, c3} },
			{ {r2, c1},{r2, c2},{r2, c3} },
			{ {r3, c1},{r3, c2},{r3, c3} },	
		           };
tcoordinates m_click;/*L(m_click.x) pour désigner la ligne et C(m_click.y) la colonne du click de la souris*/ 

/**Initialisation de ncurses**/ 
void ncurses_initialiser() {
  initscr();	        /* Demarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Desactive l'affichage des caracteres saisis */
  keypad(stdscr, TRUE);	/* Active les touches specifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}

/**Initialisation de la souris**/  
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

WINDOW *create_win(int nlines, int ncols, tcoordinates coor)//func to create win
{
	WINDOW *lwindow;
	
	lwindow = newwin(nlines,ncols,coor.x,coor.y);
	box(lwindow,0,0);
	mvwprintw(lwindow, coor.x+3, coor.y+2, " n=%d", coor.x+coor.y); 
	wrefresh(lwindow);
	
	return lwindow;	
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
	    if (m_click.x< 27 && m_click.y<48) /*Vous pouvez changer ici et mettre les dimensions de votre plateau de jeu*/
	    {
	    return 0;
	    }
	  }
	}
    }
  }
  return 0;
}
	
tcoordinates window_finder(tcoordinates mouse_click)//have to return tcoordinates type but how can i take it 
{
	tcoordinates w={0,0};
	//find the row
	if (mouse_click.x>=r2)	w.x=1;
	if (mouse_click.x>=r3)	w.x=2;
	
	//find the column
	if (mouse_click.y>=c2)	w.y=1;
	if (mouse_click.y>=c3)	w.y=2;
	
	return w ;
}//put it in clicked_win

void move_win(WINDOW *lwindow,tcoordinates loc)
{
		mvwin(lwindow,loc.x,loc.y);
		wrefresh(lwindow);
}

void window_verif_diff(WINDOW *BLANK ,WINDOW *CLICKED_WIN ,tcoordinates blank,tcoordinates clicked_win)//blank has to be set as a copy of a win and change aft the func
{
	if( ( blank.x==clicked_win.x && abs(blank.x-clicked_win.x)<=row/3 ) || ( blank.y==clicked_win.y && abs(blank.y-clicked_win.y)<=col/3) )
	{
		move_win(BLANK,clicked_win);
		move_win(CLICKED_WIN,blank);
		BLANK = CLICKED_WIN;
		// exchange values of place[window_finder(blank).x][window_finder(blank).y] and place[window_finder(clicked_win.x)][window_finder(clicked_win.y)]  
		//exit();
	}
	//print smthng like you can't move this picture
}








	
int main (int argc ,char *argv[])
{
ncurses_initialiser(); //Initialisation de ncurses
 
 int l=10,h=16;
 tcoordinates win_click={0,0};
	//windows creation
	WINDOW *originwin[3][3];
	WINDOW *BLANK=originwin[3][3];
	tcoordinates blank;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			originwin[i][j]=create_win(l,h,gplace[i][j]);
		}
	}
	
  //mouse initialisation	
  ncurses_souris();
  scrollok(stdscr, TRUE);
  while (1)
  {
    click_souris();
    
    win_click=window_finder(m_click);
    clear();
    printw("Vous avez cliqué dans la fenetre (%d,%d)\n", win_click.x+1, win_click.y+1);
    
    /*
    window_verif_diff(BLANK ,originwin[win_click.x][win_click.y],blank, place[win_click.x][win_click.y]);
    getparyx(BLANK,blank.x,blank.y);
    
    
    
    clear();
    printw("Vous avez cliqué sur la poisition (%d,%d)\n", m_click.x, m_click.y);
    */
  }
  
  
  
endwin();
return 0;
}
