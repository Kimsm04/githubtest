#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _point
{
	int x, y;
}point;
typedef enum _direction
{
	IDLE = 1, LEFT, UP, DOWN, RIGHT
}direction;
typedef enum _state { alive, dead, finished }state;		// 각 플레이어들의 상태를 나타내는 자료형
typedef struct _tickState
{
	double goalTick;	// 트리거틱
	double cntTick;		// 현재 틱
}tickState;		// 이벤트를 발생시키는 주기를 조절하기 위한 자료형

void init_nightgame();

bool night_moveOn(point*, direction); // 0 플레이어 이동
bool night_running = true;	// 게임 반복문 실행 여부
point* pl;				// 플레이어 위치들
tickState* plTicks;		// 플레이어 이동 주기
state* states;			// 플레이어 상태 (alive, dead, finished)
state* fstates;			// 더블 체크


int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];

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

		back_buf[px[i]][py[i]] = '0' + i; 
	}
	tick = 0;
}



void nightgame() {
	srand((unsigned int)time(NULL));
	init_nightgame();

	system("cls");
	display();
	while (night_running) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key != K_UNDEFINED)
		{
			if (key == K_QUIT)
				night_running = false;
			else if (states[0] == alive && plTicks[0].goalTick <= plTicks[0].cntTick)
				switch (key)
				{
				case K_LEFT:
					night_moveOn(pl + 0, LEFT);
					break;
				case K_UP:
					night_moveOn(pl + 0, UP);
					break;
				case K_DOWN:
					night_moveOn(pl + 0, DOWN);
					break;
				case K_RIGHT:
					night_moveOn(pl + 0, RIGHT);
					break;
				}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}

bool night_moveOn(point* pt, direction dir)
{
	switch (dir)
	{
	case LEFT:
		if (back_buf[pt->y][pt->x - 1] != ' ')
			return false;
		back_buf[pt->y][pt->x - 1] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->x -= 1;
		break;

	case UP:
		if (back_buf[pt->y - 1][pt->x] != ' ')
			return false;
		back_buf[pt->y - 1][pt->x] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->y -= 1;
		break;

	case DOWN:
		if (back_buf[pt->y + 1][pt->x] != ' ')
			return false;
		back_buf[pt->y + 1][pt->x] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->y += 1;
		break;

	case RIGHT:
		if (back_buf[pt->y][pt->x + 1] != ' ')
			return false;
		back_buf[pt->y][pt->x + 1] = back_buf[pt->y][pt->x];
		back_buf[pt->y][pt->x] = ' ';
		pt->x += 1;
		break;
	}
	return true;
}