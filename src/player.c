#include <stdlib.h>
#include <ncurses.h>
#include <player.h>

Entity* createPlayer (Position start_pos, char ch) {
	Entity* player = calloc(1, sizeof(Entity));

	player->pos.x = start_pos.x;
	player->pos.y = start_pos.y;
	player->ch = ch;

	return player;
}

void inputKeyboardHandle(int input_code, int row, int col) {
	switch (input_code) {
		case 'a':										// Влево
			// Постфиксный декремент позиции Y
			if (player->pos.x >= row - 3 && player->pos.y > 1) {
				player->pos.y--;
			}
			break;
		case 'd':										// Вправо
			// Постфиксный инкремент позиции Y
			if (player->pos.x >= row - 3 && player->pos.y <= col - 3) {
				player->pos.y++;
			}
		default:
			break;
	}
}
