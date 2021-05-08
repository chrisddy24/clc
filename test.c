#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


// definition of the screen size for the moment
#define col 48
#define row 27


// definition of constants in function of the screen size
 # define  r1 0
 # define r2 row/3
 # define r3 2*row/3
 # define c1 0
 # define c2 col/3
 # define c3 2*col/3 

typedef struct 
	{
		int x;
		int y;
	}tcoordinates;

tcoordinates gplace[3][3]={ 
			{ {r1, c1},{r1, c2},{r1, c3} },
			{ {r2, c1},{r2, c2},{r2, c3} },
			{ {r3, c1},{r3, c2},{r3, c3} },	
		           };
		           

void move_win(WINDOW *lwindow,tcoordinates loc)
{
		mvwin(lwindow,loc.x,loc.y);
		wrefresh(lwindow);
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


void window_verif_diff(WINDOW *BLANK ,WINDOW *CLICKED_WIN ,tcoordinates blank,tcoordinates clicked_win)//blank has to be set as a copy of a win and change aft the func
{
	if( ( blank.x==clicked_win.x && abs(blank.x-clicked_win.x)<=row/3 ) || ( blank.y==clicked_win.y && abs(blank.y-clicked_win.y)<=col/3) )
	{
		move_win(BLANK,clicked_win);
		move_win(CLICKED_WIN,blank);
		BLANK = CLICKED_WIN;
		//exit();
	}
	//print smthng like you can't move this picture
}

void window_verif_easy(WINDOW *BLANK ,WINDOW *CLICKED_WIN ,tcoordinates blank,tcoordinates clicked_win)//blank has to be set as a copy of a win and change aft the func
{
	if( ( blank.x==clicked_win.x && abs(blank.x-clicked_win.x)<=row/3 ) || ( blank.y==clicked_win.y && abs(blank.y-clicked_win.y)<=col/3) )
	{
		move_win(BLANK,clicked_win);
		move_win(CLICKED_WIN,blank);
		BLANK = CLICKED_WIN;
		//exit();
	}
	else
	{
		tcoordinates tabb[4]={
					{blank.x, blank.y},
					{blank.x, blank.y+c2},
					{blank.x+r2, blank.y},
					{blank.x+r2, blank.y+c2},
				      };
		tcoordinates tabcw[4]={
					{clicked_win.x, clicked_win.y},
					{clicked_win.x, clicked_win.y+c2},
					{clicked_win.x+r2, clicked_win.y},
					{clicked_win.x+r2, clicked_win.y+c2},
				      };
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(tabb[i].x==tabcw[j].x && tabb[i].y==tabcw[j].y)
				{
					move_win(BLANK,clicked_win);
					move_win(CLICKED_WIN,blank);
					BLANK = CLICKED_WIN;
					//exit();
				}
			}
		}	
	}
	//print smthng like you can't move this picture
}
int main (int argc ,char *argv[])
{
initscr();
	
	
	
	
	printf("coucou = %d \n",gplace[0][0].y);
endwin();	
return 0;
}


