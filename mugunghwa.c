#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
typedef struct _point
{
	int x, y;
}point;
typedef enum _direction
{
	IDLE = 1, LEFT, UP, DOWN, RIGHT
}direction;
typedef enum _state { alive, dead, finished }state;
typedef struct _tickState
{
	double goalTick;
	double cntTick;
}tickState;
bool moveOn(point*, direction);	
double getTick();
int SayFlower();	
void killPlayer();
char map[9][40], front[9][40];
bool running = true;
state states[10] = { alive, };
state fStates[5] = { -1,-1,-1,-1,-1 };
int x, y;

void mugunghwa() {
	srand((unsigned int)time(NULL));
	//맵 생성
	system("cls");
	if (n_player > 5) {
		map_init(4+n_player, 40);
	}
	else {
		map_init(9, 40);
	}
	//영희 생성
	back_buf[N_ROW/2-1][1] = '#';
	back_buf[N_ROW/2][1] = '#';
	back_buf[N_ROW/2+1][1] = '#';

	// 참가자 위치 초기화
	point pl[5] = { {38,2}, {38,3},{38,4},{38,5},{38,6} };

	tickState plTicks[5] = { {0,0}, {200,0}, {400,0}, {600,0}, {800,0}, };
	tickState taggerSaying = { 100,0 };	// 영희
	tickState taggerWatching = { 3000,0 }; // d영희
	bool isWatching = false;
	for (int i = 0; i < n_player; i++) {
		x = 2+i;
		y = 38;
		px[i] = x;
		py[i] = y;

		back_buf[px[i]][py[i]] = '0' + i;
	}
	while (running) {
		display();
		key_t key = get_key();
		//플레이어 조작
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}
		if ((pl[0].x == 1) || (pl[0].x == 2 && 3 <= pl[0].y && pl[0].y <= 5))
				states[0] = finished;
		//ai움직임
		for (int i = 1; i < n_player; i++)
		{
			if (states[i] == alive && plTicks[i].goalTick <= plTicks[i].cntTick)
			{
				plTicks[i].cntTick = 0;
				if (isWatching == false || (rand() % 10 == 0))	// 보고 있지않거나, 보고있더라고 10%의 확률로 실행
				{
					int random = rand() % 10;
					if (random == 0)
						moveOn(pl + i, IDLE);
					else if (random == 1)
						moveOn(pl + i, UP);
					else if (random == 2)
						moveOn(pl + i, DOWN);
					else
					{
					}
						moveOn(pl + i, LEFT);

					if ((pl[i].x == 1) || (pl[i].x == 2 && 3 <= pl[i].y && pl[i].y <= 5))
						states[i] = finished;
				}
			}


		}

		// 무궁화꽃이 피었습니다 출력
		if (isWatching)
		{
			if (taggerWatching.goalTick <= taggerWatching.cntTick)
			{
				isWatching = false;
				taggerWatching.cntTick = 0;
				back_buf[N_ROW / 2 - 1][1] = '#';
				back_buf[N_ROW / 2][1] = '#';
				back_buf[N_ROW / 2 + 1][1] = '#';
				gotoxy(N_ROW+1, 0);
				printf("                                                               ");
			}
			else
			{
				back_buf[N_ROW / 2 - 1][1] = '@';
				back_buf[N_ROW / 2][1] = '@';
				back_buf[N_ROW / 2 + 1][1] = '@';
				killPlayer();
			}
		}
		else
		{
			if (taggerSaying.goalTick <= taggerSaying.cntTick)
			{
				int cnt = SayFlower();
				if (cnt < 10) {
					if (cnt == 0)
						taggerSaying.goalTick = 1000;
					taggerSaying.goalTick += rand() % 200;
				}
				else
				{
					if (cnt == 10)
						taggerSaying.goalTick = 1000;
					taggerSaying.goalTick -= rand() % 300;
				}
				taggerSaying.cntTick = 0;
				if (20 <= cnt)
					isWatching = true;
			}

		}

		//tick 계산
		double tick = getTick();
		for (int i = 0; i < 5; i++) plTicks[i].cntTick += tick;
		taggerSaying.cntTick += tick;
		if (isWatching) taggerWatching.cntTick += tick;

		int leftPlayer = 0;
		int deadPlayer = 0;
		for (int i = 0; i < n_player; i++)
			if (states[i] == alive)
				leftPlayer++;
			else if (states[i] == dead)
				deadPlayer++;
		if (leftPlayer <= 1)
			if (leftPlayer == 1 && deadPlayer == 4)
				running = false;
			else if (leftPlayer == 0)
				running = false;


	}
	display();
	gotoxy(20, 0);
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
		if (map[pt->y - 1][pt->x] != ' ')
			return false;
		map[pt->y - 1][pt->x] = map[pt->y][pt->x];
		map[pt->y][pt->x] = ' ';
		pt->y -= 1;
		break;

	case DOWN:
		if (map[pt->y + 1][pt->x] != ' ')
			return false;
		map[pt->y + 1][pt->x] = map[pt->y][pt->x];
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
double getTick()
{
	static double beforeClock = 0;
	double temp = beforeClock;
	beforeClock = clock();
	return clock() - temp;

}
int SayFlower()
{
	static int cnt = 0;
	const char* sentence = "무궁화꽃이피었습니다";
	while (cnt < strlen(sentence))
	{
		gotoxy(N_ROW+1, cnt);
		printf("%c%c", sentence[cnt], sentence[cnt + 1]);
		cnt += 2;
		return cnt;
	}
	cnt = 0;
	return cnt;
}
//void playerDialog() {
//	static int fplayerCnt = 0;
//	int playerCnt = 5;
//	for (int i = 0; i < 5; i++)
//		if (states[i] == dead)
//			playerCnt--;
//
//	if (fplayerCnt != playerCnt)
//	{
//		gotoxy(14, 0);
//		fplayerCnt = playerCnt;
//		printf("no. of players left: %d\n", playerCnt);
//	}
//	for (int i = 0; i < 5; i++)
//	{
//		if (fStates[i] != states[i])
//		{
//			fStates[i] = states[i];
//			gotoxy(15 + i, 0);
//			printf("player %d: ", i);
//			if (states[i] == alive)
//				printf("alive\n");
//			else if (states[i] == dead)
//				printf("dead!\n");
//			else
//				printf("finished\n");
//		}
//	}
//}
void killPlayer()
{
	for (int i = 0; i < N_ROW; i++)
		for (int j = 0; j < N_COL; j++)
			if (front[i][j] != back_buf[i][j] && back_buf[i][j] != '#' && back_buf[i][j] != '@')
			{
				states[back_buf[i][j] - '0'] = dead;
				for (int k = j - 1; 0 < k; k--)
				{
					if ('0' <= back_buf[i][k] && back_buf[i][k] <= '9')
						states[back_buf[i][j] - '0'] = alive;
				}
				if (states[back_buf[i][j] - '0'] == dead)
					back_buf[i][j] = ' ';
			}
}