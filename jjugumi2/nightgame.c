#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3


void init_nightgame();
void item_spawn();
void chocie();
void move_manual(key_t key);
void move_random(int i, int dir);
void move_tail(int i, int nx, int ny);

int item_buf[ROW_MAX][COL_MAX];
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int ix[ITEM_MAX], iy[ITEM_MAX];

void init_nightgame() {
	map_init(8, 23);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);
		if (player[i].is_alive == true) {
			back_buf[px[i]][py[i]] = '0' + i;
		}
	}
	item_spawn();
}

void item_spawn() {
	srand((unsigned int)time(NULL));
	int n_item = 2;
	int x, y;
	for (int i = 0; i < n_item; i++) {
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		ix[i] = x;
		iy[i] = y;
		back_buf[ix[i]][iy[i]] = 'I';
		item_buf[ix[i]][iy[i]] = rand() % 7;
	}
}

void chocie() {

}

void move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (back_buf[nx][ny] == 'I') {
		if (player[0].hasitem == false) {
			player[0].item;
			player[0].hasitem = true;
		}
		else if (player[0].hasitem = true) {
			if (!placable(nx, ny)) {
				return;
			}
		}
	}
	else {
		if (!placable(nx, ny)) {
			return;
		}
	}

	move_tail(0, nx, ny);
}

void move_random(int player, int dir) {
	int p = player;  
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	do {
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

void move_tail(int player, int nx, int ny) {
	int p = player;  
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void nightgame() {
	srand((unsigned int)time(NULL));
	init_nightgame();

	system("cls");
	display();
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				move_random(i, -1);
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}

