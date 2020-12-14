#ifndef FIRE_HEAD
#define FIRE_HEAD
#include <ncurses.h>

struct firePart{
	int y;
	int x;
	char display;
	unsigned char valid;
};

struct fireWindow{
	WINDOW * cursWin;
	int FLINES;
	int FCOLS;
	struct firePart * particleList;
	int partMax;
	int valid;
};

struct fireWindow fCreateWindow(int y, int x, int particles);

void fDestroyWindow(struct fireWindow * window);

void fUpdateWindow(struct fireWindow * window);

int fireDemo(void);

int sign(int val);
#endif
