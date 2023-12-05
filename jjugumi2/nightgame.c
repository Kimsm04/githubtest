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
typedef enum _state { alive, dead, finished }state;		// �� �÷��̾���� ���¸� ��Ÿ���� �ڷ���
typedef struct _tickState
{
	double goalTick;	// Ʈ����ƽ
	double cntTick;		// ���� ƽ
}tickState;		// �̺�Ʈ�� �߻���Ű�� �ֱ⸦ �����ϱ� ���� �ڷ���

void init_nightgame();

bool night_moveOn(point*, direction); // 0 �÷��̾� �̵�
bool night_running = true;	// ���� �ݺ��� ���� ����
point* pl;				// �÷��̾� ��ġ��
tickState* plTicks;		// �÷��̾� �̵� �ֱ�
state* states;			// �÷��̾� ���� (alive, dead, finished)
state* fstates;			// ���� üũ


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
		// player 0�� ������ ������(4����)
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