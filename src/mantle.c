#include "mantle.h"
#include <ncurses.h>


const char brickPattern[11] = "____|____|";

void drawChimney(int y, int x){
	int brick = 3;

	for(int i = y; i >= 0; i--){
		mvaddch(i, x, '|');
		mvaddch(i, x + 11, '|');
		
		brick ^= 2;
		
		for(int j=0; j<10; j++){
			mvaddch(i, x + j + 1, brickPattern[((brick + j) % 10)]);
		}
	}
}

void drawMantle(int y, int x){
	for(int i=1; i<=16; i++){
		mvaddch(y, x + i, '_');
		mvaddch(y + 6, x + i, '_');
	}
	
	mvaddch(y + 1, x, '/');
	mvaddch(y + 1, x + 17, '\\');
	mvaddch(y + 2, x, '|');
	mvaddch(y + 2, x + 17, '|');
	mvaddch(y + 3, x, '|');
	mvaddch(y + 3, x + 17, '|');
	mvaddch(y + 4, x, '|');
	mvaddch(y + 4, x + 17, '|');
	mvaddch(y + 5, x, '|');
	mvaddch(y + 5, x + 17, '|');
	mvaddch(y + 6, x, '\\');
	mvaddch(y + 6, x + 17, '/');
	
	drawChimney(y, x + 3);
	
}

int mantleDemo(void){
	initscr();
	noecho();
	cbreak();
	
	refresh();
	
	drawMantle(17, 30);
	
	refresh();
	getch();	
	endwin();
}

