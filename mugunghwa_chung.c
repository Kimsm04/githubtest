#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
// *: ��
// #: ����
// @: �ڵ��ƺ� ����
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
bool moveOn(point*, direction);	// ������ �� ������ false, ������ �����̰� true ��ȯ
double getTick();
int SayFlower();	// ����ȭ�����Ǿ����ϴ� ���� ��ŭ ����ߴ��� int������ ��ȯ
void killPlayer();
void playerDialog(void);
char map[9][40], front[9][40];
bool running = true;
state states[5] = { alive, };
state fStates[5] = { -1,-1,-1,-1,-1 };
int main() {
	srand((unsigned int)time(NULL));
	//�� ����
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0 || i == 8 || j == 0 || j == 39)	// �� ����
				map[i][j] = '*';
			else
				map[i][j] = ' ';
		}
	}

	//���� ����
	map[3][1] = '#';
	map[4][1] = '#';
	map[5][1] = '#';

	// ������ ��ġ �ʱ�ȭ
	point pl[5] = { {38,2}, {38,3},{38,4},{38,5},{38,6} };

	tickState plTicks[5] = { {100,0}, {1000,0}, {400,0}, {3000,0}, {1600,0}, };
	tickState taggerSaying = {100,0};	// ����
	tickState taggerWatching = {3000,0}; // d����
	bool isWatching = false;

	map[pl[0].y][pl[0].x] = '0';
	map[pl[1].y][pl[1].x] = '1';
	map[pl[2].y][pl[2].x] = '2';
	map[pl[3].y][pl[3].x] = '3';
	map[pl[4].y][pl[4].x] = '4';

	while (running) {
		draw();
		playerDialog();
		//�÷��̾� ����
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
					if (isWatching == false || (rand()%10 == 0))	// ���� �����ʰų�, �����ִ���� 10%�� Ȯ���� ����
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
		
		// ����ȭ���� �Ǿ����ϴ� ���
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
		
		//tick ���
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
	const char* sentence = "����ȭ�����Ǿ����ϴ�";
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