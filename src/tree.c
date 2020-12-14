#include "tree.h"

#include <ncurses.h>


void drawTreePot(int y, int x, int width){
	mvaddch(y, x+1, '/');
	mvaddch(y, x+width+2, '\\');
	mvprintw(y+1, x, "||");
	mvprintw(y+1, x+width+2, "||");
	mvprintw(y+2, x, "|\\");
	mvprintw(y+2, x+width+2, "/|");
	mvaddch(y+3, x, '|');
	mvaddch(y+3, x+width+3, '|');
	mvprintw(y+4, x, "\\_");
	mvprintw(y+4, x+width+2, "_/");
	for(int i=0; i<width; i++){
		mvaddch(y+1, x + i + 2, '~');
		mvaddch(y+2, x + i + 2, '_');
		mvaddch(y+4, x + i + 2, '_');
	}
}

void drawTree(int boughs, int firstheight, int ystart, int xstart){
	int mirrdist = 0;
	int y = ystart;
	
	
	for(int i=0;i<boughs;i++){
		//draw bough
		for(int j = 0; j < firstheight + i; j++){
			if(mirrdist == 0){
				mvaddch(y, xstart, '^');
			}
			else{
				y++;
				mvaddch(y, xstart - mirrdist, '/');
				mvaddch(y, xstart + mirrdist, '\\');
			}
			mirrdist++;
		}
		//bottom edge of each bough
		mirrdist-= 2;
		mvaddch(y, xstart - mirrdist, '_');
		mvaddch(y, xstart + mirrdist, '_');
		
		mirrdist--;
		mvaddch(y, xstart - mirrdist, '_');
		mvaddch(y, xstart + mirrdist, '_');
	}
	//bottom of last bough
	for(mirrdist; mirrdist > 1; mirrdist--){
		mvaddch(y, xstart - mirrdist, '_');
		mvaddch(y, xstart + mirrdist, '_');
	}
	mirrdist++;
	//trunk
	for(int i = 0; i < 3; i++){
		y++;
		mvaddch(y, xstart - mirrdist, '|');
		mvaddch(y, xstart + mirrdist, '|');
	}
	drawTreePot(y - 1, xstart - 4, mirrdist * 2 + 1);
}

int treedemo(void){
	
	initscr();
	noecho();
	cbreak();
	//curs_set(0) //does not work in mate terminal
	refresh();
	
	drawTree(3, 4, 2, 10);
	refresh();
	
	getch();
	
	
	endwin();
}



