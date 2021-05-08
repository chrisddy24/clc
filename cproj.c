#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

// definition of the screen size for the moment
#define col 48
#define row 27		//getmaxyx(stdscr,row,col);


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
//
tcoordinates gplace[3][3]={ //original places of wins
			{ {r1, c1},{r1, c2},{r1, c3} },
			{ {r2, c1},{r2, c2},{r2, c3} },
			{ {r3, c1},{r3, c2},{r3, c3} },	
		           };

WINDOW *create_win(int nlines, int ncols, tcoordinates coor)//func to create win
{
	WINDOW *lwindow;
	
	lwindow = newwin(nlines,ncols,coor.x,coor.y);
	box(lwindow,0,0);
	wrefresh(lwindow);
	
	return lwindow;	
}


int main (int argc ,char *argv[])
{
initscr();
	int l=10,h=16;
	//windows creation
	WINDOW *originwin[3][3];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			originwin[i][j]=create_win(l,h,gplace[i][j]);
		}
	}
	//test window disp
	wprintw(originwin[0][0],"\n\thello");
	wrefresh(originwin[0][0]);
	
	wprintw(originwin[1][1],"\n\tworld");
	wrefresh(originwin[1][1]);
	sleep(5);
	
	mvwin(originwin[0][0],gplace[1][1].x,gplace[1][1].y);
	mvwin(originwin[1][1],gplace[0][0].x,gplace[0][0].y);
	wrefresh(originwin[0][0]);
	wrefresh(originwin[1][1]);
	sleep(5);
	
	//create a function that makes all changes for a window
	//how to move windows
	//coordinates comparison (do we have to add sizes like r1,c1 to compare ?
	
endwin();
return 0;
}
