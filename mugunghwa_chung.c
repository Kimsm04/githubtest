#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

// *: 벽
// #: 영희
// @: 뒤돌아본 영희
typedef struct _point
{
	int x, y;
}point;
typedef enum _direction
{
	IDLE = 1, LEFT, UP, DOWN, RIGHT
}direction;
typedef enum _state {alive,dead,finished}state;
void gotoxy(int row, int col);
void draw(void);
bool moveOn(point *, direction);	// 움직일 수 없으면 false, 있으면 움직이고 true 반환
char map[9][41] = { 0, }, front[9][41] = { 0, };
bool running = true;

int main() {
	srand((unsigned int)time(NULL));
	//맵 생성
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0 || i == 8 || j == 0 || j == 39)	// 벽 생성
				map[i][j] = '*';
			else
				map[i][j] = ' ';
		}
	}

	//영희 생성
	map[3][1] = '#';
	map[4][1] = '#';
	map[5][1] = '#';

	// 참가자 위치 초기화
	point pl[5] = { {38,2}, {38,3},{38,4},{38,5},{38,6} };
	bool states[5] = { alive, };

	map[pl[0].y][pl[0].x] = '0';
	map[pl[1].y][pl[1].x] = '1';
	map[pl[2].y][pl[2].x] = '2';
	map[pl[3].y][pl[3].x] = '3';
	map[pl[4].y][pl[4].x] = '4';

	while (running) {

		draw();
		//플레이어 조작
		if ( states[0] == alive && _kbhit())
		{
			int key = _getch();
			switch (key)
			{
			case 'w':
				moveOn(pl, UP);
				break;

			case 's':
				moveOn(pl, DOWN);
				break;

			case 'a':
				moveOn(pl, LEFT);
				break;

			case 'd':
				moveOn(pl, RIGHT);
				break;

			case 'q':
				running = false;
				break;
			}
			if ((pl[0].x == 1) || (pl[0].x == 2 && 3 <= pl[0].y && pl[0].y <= 5))
				states[0] = finished;
		}
		for (int i = 1; i < 5; i++)
		{
			if (states[i] == alive)
			{
				// pl마다 개별 이동주기를 가짐
				// 무궁화

				int random = rand() % 10;
				if (random == 0)
					moveOn(pl + i, IDLE);
				else if (random == 1)
					moveOn(pl + i, UP);
				else if (random == 2)
					moveOn(pl + i, DOWN);
				else
					moveOn(pl + i, LEFT);

				if ((pl[i].x == 1) || (pl[i].x == 2 && 3 <= pl[i].y && pl[i].y <= 5))
					states[i] = finished;
			}

		}
		Sleep(500);

	}

	return 0;
}




bool moveOn(point* pt, direction dir)
{
	switch (dir)
	{
	case LEFT:
		if (map[pt->y][pt->x - 1] != ' ')
			return false;
		map[pt->y][pt->x - 1] = map[pt->y][pt->x];
		map[pt->y][pt->x] = ' ';
		pt->x -= 1;
		break;

	case UP:
		if (map[pt->y-1][pt->x] != ' ')
			return false;
		map[pt->y-1][pt->x] = map[pt->y][pt->x];
		map[pt->y][pt->x] = ' ';
		pt->y -= 1;
		break;

	case DOWN:
		if (map[pt->y+1][pt->x] != ' ')
			return false;
		map[pt->y+1][pt->x] = map[pt->y][pt->x];
		map[pt->y][pt->x] = ' ';
		pt->y += 1;
		break;

	case RIGHT:
		if (map[pt->y][pt->x + 1] != ' ')
			return false;
		map[pt->y][pt->x + 1] = map[pt->y][pt->x];
		map[pt->y][pt->x] = ' ';
		pt->x += 1;
		break;
	}
	return true;
}




void gotoxy(int row, int col) {
	COORD pos = { col, row };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}
//맵 함수
void draw(void) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (front[i][j] != map[i][j]) {
				front[i][j] = map[i][j];
				gotoxy(i, j);
				printf("%c", front[i][j]);
			}
		}

	}
}