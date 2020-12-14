#include "snow.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "fire.h"



void drawBlinds(struct snowWindow * window){
	mvwprintw(window->cursWin, 1, 1, "  |");
	mvwprintw(window->cursWin, 1, window->SCOLS-4, "|  ");
	mvwprintw(window->cursWin, 2, 1, "  /");
	mvwprintw(window->cursWin, 2, window->SCOLS-4, "\\  ");
	mvwprintw(window->cursWin, 3, 1, " /");
	mvwprintw(window->cursWin, 3, window->SCOLS-3, "\\ ");
	mvwaddch(window->cursWin, 4, 1, '|');
	mvwaddch(window->cursWin, 4, window->SCOLS-2, '|');
	mvwaddch(window->cursWin, 5, 1, '|');
	mvwaddch(window->cursWin, 5, window->SCOLS-2, '|');
	mvwaddch(window->cursWin, 6, 1, '/');
	mvwaddch(window->cursWin, 6, window->SCOLS-2, '\\');
}

struct snowWindow sCreateWindow(int y, int x, int particles){
	struct snowWindow ret;
	ret.cursWin = newwin(7, 13, y, x);
	wborder(ret.cursWin, '|', '|', '_', '_', ' ', ' ', '|', '|');
	
	
	wrefresh(ret.cursWin);
	ret.SLINES = 7;
	ret.SCOLS  = 13;
	
	ret.particleList = (struct snowflake *)malloc(sizeof(struct snowflake) * particles);
	ret.partMax = particles;
	ret.valid = 0;
	
	return ret;
}

void sDestroyWindow(struct snowWindow * window){
	free(window->particleList);
	window->partMax = 0;
	window->valid = 0;
	
	wborder(window->cursWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(window->cursWin);
	delwin(window->cursWin);
}

void printDetails(struct snowWindow * window, int starty, int startx){
	mvprintw(starty, startx, "i\tx\ty\tvalid\tprint");
	for(int i=0;i<window->valid;i++){
		mvprintw(starty + i + 1, startx, "%02d:\t%02d,\t%02d,\t%s\t%s", i, window->particleList[i].x, window->particleList[i].y, window->particleList[i].valid ? "true " : "false", 
	(window->particleList[i].valid && window->particleList[i].y > 1 && window->particleList[i].x > 1) ? "true " : "false");
	}
}


void sUpdateWindow(struct snowWindow * window){
	if(window->valid < window->partMax){
		window->particleList[window->valid].valid = true;
		window->valid++;
	}
	
	for(int i=0; i < window->valid; i++){
		if(window->particleList[i].valid){
			mvwaddch(window->cursWin, window->particleList[i].y, window->particleList[i].x, ' ');
			
			window->particleList[i].x += sign((rand() % 7) - 1);
			
			window->particleList[i].y += (rand() % 8 != 0);
			
			if(window->particleList[i].x > window->SCOLS - 2 || window->particleList[i].y > window->SLINES - 2)
				window->particleList[i].valid = false;
		}
		else{
			window->particleList[i].y = -2;
			window->particleList[i].x = ((rand() % ((window->SCOLS))) - 2);
			window->particleList[i].valid = true;
		}
		
		
		if(window->particleList[i].valid && (window->particleList[i].y > 1 && window->particleList[i].x > 1)){ //
			mvwaddch(window->cursWin, window->particleList[i].y, window->particleList[i].x, '.');
		}
		
	}
	wborder(window->cursWin, '|', '|', '_', '_', ' ', ' ', '|', '|');
	drawBlinds(window);
	
	wrefresh(window->cursWin);
}


int snowDemo(void){
	initscr();
	noecho();
	cbreak();
	
	refresh();
	
	//timeout((int)((20 * 1000) / 60));
	
	srand(time(NULL));
	
	struct snowWindow swin = sCreateWindow(4, 4, 15);
	char ch;
	
	do{
		sUpdateWindow(&swin);
		printDetails(&swin, 1, 20);
		
		mvprintw(LINES-1, 0, "Snowflakes: %d", swin.valid);
		move(LINES-1, COLS-1);
		
		ch = getch();
	}while(ch != '\n' && ch != 'q');
	
	sDestroyWindow(&swin);
	
	endwin();
}


