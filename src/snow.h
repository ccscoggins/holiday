#ifndef SNOW_HEAD
#define SNOW_HEAD
#include <ncurses.h>

struct snowflake{
	int y;
	int x;
	char valid;
};

struct snowWindow{
	WINDOW * cursWin;
	int SLINES;
	int SCOLS;
	struct snowflake * particleList;
	int partMax;
	int valid;
};

struct snowWindow sCreateWindow(int y, int x, int particles);

void sDestroyWindow(struct snowWindow * window);

void sUpdateWindow(struct snowWindow * window);

int snowDemo(void);

#endif
