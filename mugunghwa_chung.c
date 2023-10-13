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
typedef enum _state { alive, dead, finished }state;
typedef struct _tickState
{
	double goalTick;
	double cntTick;
}tickState;
void gotoxy(int row, int col);
void draw(void);
bool moveOn(point*, direction);	// 움직일 수 없으면 false, 있으면 움직이고 true 반환
double getTick();
int SayFlower();	// 무궁화꽃이피었습니다 에서 얼만큼 출력했는지 int형으로 반환
void killPlayer();
void playerDialog(void);
char map[9][40], front[9][40];
bool running = true;
state states[5] = { alive, };
state fStates[5] = { -1,-1,-1,-1,-1 };
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

	tickState plTicks[5] = { {100,0}, {1000,0}, {400,0}, {3000,0}, {1600,0}, };
	tickState taggerSaying = {100,0};	// 영희
	tickState taggerWatching = {3000,0}; // d영희
	bool isWatching = false;

	map[pl[0].y][pl[0].x] = '0';
	map[pl[1].y][pl[1].x] = '1';
	map[pl[2].y][pl[2].x] = '2';
	map[pl[3].y][pl[3].x] = '3';
	map[pl[4].y][pl[4].x] = '4';

	while (running) {
		draw();
		playerDialog();
		//플레이어 조작
		if (states[0] == alive && _kbhit() && plTicks[0].goalTick <= plTicks[0].cntTick)
		{
			plTicks[0].cntTick = 0;
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
				if (states[i] == alive && plTicks[i].goalTick <= plTicks[i].cntTick)
				{
					plTicks[i].cntTick = 0;
					if (isWatching == false || (rand()%10 == 0))	// 보고 있지않거나, 보고있더라고 10%의 확률로 실행
					{
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
			

		}
		
		// 무궁화꽃이 피었습니다 출력
		if (isWatching)
		{
			if (taggerWatching.goalTick <= taggerWatching.cntTick)
			{
				isWatching = false;
				taggerWatching.cntTick = 0;
				map[3][1] = '#';
				map[4][1] = '#';
				map[5][1] = '#';
				gotoxy(10, 0);
				printf("                                                               ");
			}
			else
			{
				map[3][1] = '@';
				map[4][1] = '@';
				map[5][1] = '@';
				killPlayer();
			}
		}
		else
		{
			if (taggerSaying.goalTick <= taggerSaying.cntTick)
			{
				int cnt = SayFlower();
				if (cnt < 10)
					taggerSaying.cntTick = taggerSaying.goalTick * (1 - (cnt + rand() % 11) * 0.1);	//0.5~0.1
				else
					taggerSaying.cntTick = taggerSaying.goalTick * ((cnt - 15 + rand() % 11) * 0.1);	//0.5 ~ 1
				//tagger.cntTick = 0;
				taggerSaying.goalTick += 100;
				if (20 <= cnt)
					isWatching = true;
			}
			
		}
		
		//tick 계산
		double tick = getTick();
		for (int i = 0; i < 5; i++) plTicks[i].cntTick += tick;
		taggerSaying.cntTick += tick;
		if(isWatching) taggerWatching.cntTick += tick;

		for (int i = 0; i <= 5; i++)
			if (i == 5)
				running = false;
			else if(states[i] != alive)
				continue;
			else
				break;

	}
	draw();
	playerDialog();
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
		gotoxy(10, cnt);
		printf("%c%c", sentence[cnt],sentence[cnt+1]);
		cnt += 2;
		return cnt;
	}
	cnt = 0;
	return cnt;
}
void playerDialog() {
	static int fplayerCnt=0;
	int playerCnt = 5;
	for (int i = 0; i < 5; i++)
		if (states[i] == dead)
			playerCnt--;
	
	if (fplayerCnt != playerCnt)
	{
		gotoxy(14, 0);
		fplayerCnt = playerCnt;
		printf("no. of players left: %d\n", playerCnt);
	}
	for (int i = 0; i < 5; i++)
	{
		if (fStates[i] != states[i])
		{
			fStates[i] = states[i];
			gotoxy(15 + i, 0);
			printf("player %d: ", i);
			if (states[i] == dead)
				printf("dead!\n");
			else
				printf("alive\n");
		}
	}
}
void killPlayer()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 40; j++)
			if (front[i][j] != map[i][j] && map[i][j] != '#' && map[i][j] != '@')
			{
				states[map[i][j] - '0'] = dead;
				for (int k = j - 1; 0 < k; k--)
				{
					if ('0' <= map[i][k] && map[i][k] <= '9')
						states[map[i][j] - '0'] = alive;
				}

			}
}
void gotoxy(int row, int col) {
	COORD pos = { col, row };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}
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