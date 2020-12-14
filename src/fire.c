#include "fire.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int sign(int val){
	if(val < 0)
		return -1;
	if(val > 0)
		return 1;
	return 0;
}

const char firechars[10] = {'.', '.', '\'', '\'', ',', ',', '^', ';', '(', ')'};

struct fireWindow fCreateWindow(int y, int x, int particles){
	struct fireWindow ret;
	
	ret.cursWin = newwin(5, 12, y, x);
	wborder(ret.cursWin, '|', '|', '_', '_', ' ', ' ', '|', '|');
	mvwprintw(ret.cursWin, 4, 2, "^^^^^^^^");
	
	wrefresh(ret.cursWin);
	
	ret.FLINES = 5;
	ret.FCOLS  = 12;
	
	ret.particleList = (struct firePart *)malloc(sizeof(struct firePart) * particles);
	ret.partMax = particles;
	ret.valid = 0; 
	
	return ret;
}

void fDestroyWindow(struct fireWindow * window){
	free(window->particleList);
	window->partMax = 0;
	window->valid = 0;
	
	wborder(window->cursWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(window->cursWin);
	delwin(window->cursWin);
	srand(time(NULL));
}


void fUpdateWindow(struct fireWindow * window){
	if(window->valid < window->partMax){
		int goal = window->valid + 3;
		do{
			window->particleList[window->valid].valid = false;
			window->valid++;
		} while(window->valid < goal && window->valid < window->partMax);
	}
	
	for(int i=0; i < window->valid; i++){
		if(window->particleList[i].valid){
			mvwaddch(window->cursWin, window->particleList[i].y, window->particleList[i].x, ' ');
			window->particleList[i].x += sign( (rand() % 4) - 1) * (((window->FCOLS / 2) > window->particleList[i].x) ? 1 : -1);
			
			window->particleList[i].y -= (rand() % 4 != 0) ? 1 : 0;
			
			if(window->particleList[i].y <= 0 || window->particleList[i].x <= 1 || window->particleList[i].x >= window->FCOLS - 2){
				window->particleList[i].valid = false;
			}
		}
		else{
			
			window->particleList[i].y = window->FLINES - 2;
			window->particleList[i].x = (rand() % (window->FCOLS - 4)) + 2;
			//getch();
			window->particleList[i].display = firechars[rand() % 10];
			window->particleList[i].valid = true;
		}
		if(window->particleList[i].valid)
			mvwaddch(window->cursWin, window->particleList[i].y, window->particleList[i].x, window->particleList[i].display);
		wrefresh(window->cursWin);
		//getch();
	}
	
	mvwaddch(window->cursWin, window->FLINES-2, 2, '(');
	mvwaddch(window->cursWin, window->FLINES-2, window->FCOLS - 3, ')');
	
	wrefresh(window->cursWin);
}


int fireDemo(void){
	initscr();
	noecho();
	cbreak();
	
	refresh();
	
	timeout((int)((10 * 1000) / 60));
	
	srand(time(NULL));
	
	struct fireWindow fwin = fCreateWindow(4, 4, 15);
	char ch;
	
	do{
		fUpdateWindow(&fwin);
		move(LINES-1, COLS-1);
		ch = getch();
	}while(ch != '\n' && ch != 'q');
	
	fDestroyWindow(&fwin);
	
	endwin();
}


