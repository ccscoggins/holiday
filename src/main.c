#include "tree.h"
#include "mantle.h"
#include "fire.h"
#include "snow.h"


#include <ncurses.h>
#include <time.h>
#include <stdlib.h>



int mainMain(void){
	
	initscr();
	noecho();
	cbreak();
	
	srand(time(NULL));
	
	timeout((10 * 1000) / 60);
	int snowtimer = 0;
	
	drawTree(3, 4, 1, 9);
	drawMantle(15, 40);
	
	refresh();
	
	struct fireWindow fwin = fCreateWindow(16, 43, 18);
	struct snowWindow swin = sCreateWindow(6, 18, 12);
	
	
	do{
		fUpdateWindow(&fwin);
		if(snowtimer ^= 1)
			sUpdateWindow(&swin);
		mvprintw(LINES-1, 0, "Happy Holidays from Cameron");
		move(LINES-1, COLS-1);
	}while(getch() == ERR);
	
	fDestroyWindow(&fwin);
	sDestroyWindow(&swin);
	endwin();
	return 0;
}

int main(void){
	mainMain();
}
