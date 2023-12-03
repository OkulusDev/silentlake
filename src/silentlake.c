/******************************************************************************
 * Название: RPG игра "Молчаливое озеро"
 * Файл: src/silentlake.c
 * Автор: Okulus Dev aka DrArgentum
 * Лицензия: MIT LICENSE
 * ****************************************************************************
 *	Описание: главный исполняемый файл игры
 * */
#include <locale.h>
#include <stdlib.h>
#include <ncurses.h>

#include <player.h>

#define DEFAULT				0
#define RED					1
#define GREEN				2
#define YELLOW				3
#define BLUE				4
#define CYAN				5

#define CTRL(c) ((c) & 037)

Entity* player;

void init_ncurses() {
	raw();
	noecho();
	curs_set(0);
	start_color();
}

void init_colors() {
	init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
}

void print_parameters(WINDOW *win) {
	wattron(win, COLOR_PAIR(RED));
	mvwprintw(win, 1, 1, "Здоровье: 100");
	wattron(win, COLOR_PAIR(RED));
}

void update_win(WINDOW *win) {
	refresh();
	wrefresh(win);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	int row, col;
	int ch;
	int winrow, wincol;
	int mainwinrow, mainwincol;

	initscr();

	if (!has_colors()) {
		endwin();
		printf("К сожалению, ваш терминал не поддерживает цвета");
		exit(1);
	}
	// Инициализация NCURSES, цветов, фонового цвета и получение размера
	// экрана в рядах и колонках
	init_ncurses();
	init_colors();
	bkgdset(COLOR_PAIR(DEFAULT));
	getmaxyx(stdscr, row, col);

	WINDOW *playerwin = newwin(row, col / 3, 0, 0);
	WINDOW *mainwin = newwin(row, col / 3 * 2, 0, col / 3);

	refresh();
	box(playerwin, 0, 0);
	box(mainwin, 0, 0);

	getmaxyx(mainwin, mainwinrow, mainwincol);

	Position start_pos = {winrow - 3, 1};
	player = createPlayer(start_pos, '@');

	mvwprintw(mainwin, 0, 1, "Молчаливое озеро");
	mvwprintw(playerwin, 0, 1, "Игрок");

	print_parameters(playerwin);

	mvwprintw(mainwin, 1, 1, "[Друид озера] Приветствую тебя!");
	mvwprintw(mainwin, 2, 1, "[y] Поприветствовать [n] Промолчать");

	update_win(mainwin);
	update_win(playerwin);

	ch = getch();

	if (ch == CTRL('q')) {
		endwin();
	} else 

	if (ch == 'y') {
		for (int i=1; i < mainwincol - 1; i++)
			mvwprintw(mainwin, 2, i, " ");
	
		mvwprintw(mainwin, 2, 1, "[Вы] Приветствую и тебя, друид!");
		update_win(mainwin);
	} else if (ch == 'n') {
		for (int i=1; i < mainwincol - 1; i++)
			mvwprintw(mainwin, 2, i, " ");

		mvwprintw(mainwin, 2, 1, "[Друид] Не молчи, как не живой. Как ты оказался в священном лесу?");
		update_win(mainwin);
	}

	getch();
		
		/*
 else {
			inputKeyboardHandle(ch, winrow, wincol);
			if (ch == 'w' && !jumped) {
				player->pos.x--;
				jumped = true;
			} else if (jumped) {
				if (ch == 'a' && player->pos.y > 1) {
					player->pos.y--;
				} else if (ch == 'd' && player->pos.y <= wincol - 3) {
					player->pos.y++;
				}
				player->pos.x++;
				jumped = false;
			}
		}
		*/

	endwin();
	return 0;
}

