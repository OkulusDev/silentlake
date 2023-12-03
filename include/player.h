#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <ncurses.h>

typedef struct {
	int x;
	int y;
} Position;

typedef struct {
	Position pos;
	char ch;
	bool died;
} Entity;

Entity* createPlayer(Position start_pos, char ch);
void inputKeyboardHandle(int input, int row, int col);
extern Entity* player;

#endif
