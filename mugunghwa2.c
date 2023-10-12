#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

void gotoxy(int row, int col);
void draw(void);
char map[9][40], front[9][40];

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

int main() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0 || i== 8 || j == 0 || j == 39)
				map[i][j] = '*';
			else
				map[i][j] = ' ';
		}
	}
	//영희
	map[3][1] = '#';
	map[4][1] = '#';
	map[5][1] = '#';

	int p_x = 2, p_y = 38;
	int AI1_x = 3, AI1_y = 38,
		AI2_x = 4, AI2_y = 38,
		AI3_x = 5, AI3_y = 38,
		AI4_x = 6, AI4_y = 38;

	int fp_x = p_x, fp_y = p_y,
		fAI1_x = AI1_x, fAI1_y = AI1_y,
		fAI2_x = AI2_x, fAI2_y = AI2_y,
		fAI3_x = AI3_x, fAI3_y = AI3_y,
		fAI4_x = AI4_x, fAI4_y = AI4_y;
	
	map[p_x][p_y] = '0';
	map[AI1_x][AI1_y] = '1';
	map[AI2_x][AI2_y] = '2';
	map[AI3_x][AI3_y] = '3';
	map[AI4_x][AI4_y] = '4';
	while (1) {
		//AI 움직임 값생성
		int AI_move1 = rand() % 10 ;
		int AI_move2 = rand() % 10 ;
		int AI_move3 = rand() % 10 ;
		int AI_move4 = rand() % 10 ;

		//플레이어
		

		draw();
		//플레이어 조작
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w':p_x -= 1;
				if (p_x > 0 && p_x < 8 && p_y > 0 && p_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || p_x != AI2_x || p_y != AI2_y || p_x != AI3_x || p_y != AI3_y || p_x != AI4_x || p_y != AI4_y)
					 map[fp_x][fp_y] = ' '; fp_x = p_x, fp_y = p_y; map[p_x][p_y] = '0';}break;

			case 's': p_x += 1; 
				if (p_x > 0 && p_x < 8 && p_y > 0 && p_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || p_x != AI2_x || p_y != AI2_y || p_x != AI3_x || p_y != AI3_y || p_x != AI4_x || p_y != AI4_y)
					 map[fp_x][fp_y] = ' '; fp_x = p_x, fp_y = p_y; map[p_x][p_y] = '0';
			} break;

			case 'a': p_y -= 1; 
				if (p_x > 0 && p_x < 8 && p_y > 0 && p_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || p_x != AI2_x || p_y != AI2_y || p_x != AI3_x || p_y != AI3_y || p_x != AI4_x || p_y != AI4_y)
					 map[fp_x][fp_y] = ' '; fp_x = p_x, fp_y = p_y; map[p_x][p_y] = '0';
			}break;

			case 'd':p_y += 1;
				if (p_x > 0 && p_x < 8 && p_y > 0 && p_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || p_x != AI2_x || p_y != AI2_y || p_x != AI3_x || p_y != AI3_y || p_x != AI4_x || p_y != AI4_y)
					 map[fp_x][fp_y] = ' '; fp_x = p_x, fp_y = p_y; map[p_x][p_y] = '0';
			} break;

			case 'q': return 0;
			}
		}
		//AI별 움직임 구현
		// 가독성 너무 떨어지는데
		//1player
		if (1) {
			switch (AI_move1) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6: if (AI1_x > 0 && AI1_x < 8 && AI1_y > 0 && AI1_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || AI1_x != AI2_x || AI1_y != AI2_y || AI1_x != AI3_x || AI1_y != AI3_y || AI1_x != AI4_x || AI1_y != AI4_y)
					AI1_y -= 1; map[fAI1_x][fAI1_y] = ' '; fAI1_x = AI1_x, fAI1_y = AI1_y; map[AI1_x][AI1_y] = '1';
			} break;

			case 7: if (AI1_x != p_x || AI1_y != p_y || AI1_x > 0 && AI1_x < 8 && AI1_y > 0 && AI1_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || AI1_x != AI2_x || AI1_y != AI2_y || AI1_x != AI3_x || AI1_y != AI3_y || AI1_x != AI4_x || AI1_y != AI4_y)
					AI1_x += 1; map[fAI1_x][fAI1_y] = ' '; fAI1_x = AI1_x, fAI1_y = AI1_y; map[AI1_x][AI1_y] = '1';
			} break;

			case 8: if (AI1_x > 0 && AI1_x < 8 && AI1_y > 0 && AI1_y < 39) {
				if (AI1_x != p_x || AI1_y != p_y || AI1_x != AI2_x || AI1_y != AI2_y || AI1_x != AI3_x || AI1_y != AI3_y || AI1_x != AI4_x || AI1_y != AI4_y)
					AI1_x -= 1; map[fAI1_x][fAI1_y] = ' '; fAI1_x = AI1_x, fAI1_y = AI1_y; map[AI1_x][AI1_y] = '1';
			} break;
			case 9: break;
			}

			//2player	
			switch (AI_move2) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6: if (AI2_x > 0 && AI2_x < 8 && AI2_y > 0 && AI2_y < 39) {
				if (AI2_x != p_x || AI2_y != p_y || AI1_x != AI2_x || AI1_y != AI2_y || AI2_x != AI3_x || AI2_y != AI3_y || AI2_x != AI4_x || AI2_y != AI4_y)
					AI2_y -= 1; map[fAI2_x][fAI2_y] = ' '; fAI2_x = AI2_x, fAI2_y = AI2_y; map[AI2_x][AI2_y] = '2';
			} break;

			case 7: if (AI2_x > 0 && AI2_x < 8 && AI2_y > 0 && AI2_y < 39) {
				if (AI2_x != p_x || AI2_y != p_y || AI1_x != AI2_x || AI1_y != AI2_y || AI2_x != AI3_x || AI2_y != AI3_y || AI2_x != AI4_x || AI2_y != AI4_y)
					AI2_x += 1; map[fAI2_x][fAI2_y] = ' '; fAI2_x = AI2_x, fAI2_y = AI2_y; map[AI2_x][AI2_y] = '2';
			} break;

			case 8: if (AI2_x > 0 && AI2_x < 8 && AI2_y > 0 && AI2_y < 39) {
				if (AI2_x != p_x || AI2_y != p_y || AI1_x != AI2_x || AI1_y != AI2_y || AI2_x != AI3_x || AI2_y != AI3_y || AI2_x != AI4_x || AI2_y != AI4_y)
					AI2_x -= 1; map[fAI2_x][fAI2_y] = ' '; fAI2_x = AI2_x, fAI2_y = AI2_y; map[AI2_x][AI2_y] = '2';
			}break;
			case 9: break;
			}

			//3player
			switch (AI_move3) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6: if (AI3_x > 0 && AI3_x < 8 && AI3_y > 0 && AI3_y < 39) {
				if (AI3_x != p_x || AI3_y != p_y || AI3_x != AI1_x || AI3_y != AI1_y || AI3_x != AI2_x || AI3_y != AI2_y || AI3_x != AI4_x || AI3_y != AI4_y)
					AI3_y -= 1; map[fAI3_x][fAI3_y] = ' '; fAI3_x = AI3_x, fAI3_y = AI3_y; map[AI3_x][AI3_y] = '3';
			} break;

			case 7: if (AI3_x > 0 && AI3_x < 8 && AI3_y > 0 && AI3_y < 39) {
				if (AI3_x != p_x || AI3_y != p_y || AI3_x != AI1_x || AI3_y != AI1_y || AI3_x != AI2_x || AI3_y != AI2_y || AI3_x != AI4_x || AI3_y != AI4_y)
					AI3_x += 1; map[fAI3_x][fAI3_y] = ' '; fAI3_x = AI3_x, fAI3_y = AI3_y; map[AI3_x][AI3_y] = '3';
			} break;

			case 8: if (AI3_x > 0 && AI3_x < 8 && AI3_y > 0 && AI3_y < 39) {
				if (AI3_x != p_x || AI3_y != p_y || AI3_x != AI1_x || AI3_y != AI1_y || AI3_x != AI2_x || AI3_y != AI2_y || AI3_x != AI4_x || AI3_y != AI4_y)
					AI3_x -= 1; map[fAI3_x][fAI3_y] = ' '; fAI3_x = AI3_x, fAI3_y = AI3_y; map[AI3_x][AI3_y] = '3';
			}break;
			case 9: break;
			}

			//4player
			switch (AI_move4) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6: if (AI4_x > 0 && AI4_x < 8 && AI4_y > 0 && AI4_y < 39) {
				if (AI4_x != p_x || AI4_y != p_y || AI4_x != AI1_x || AI4_y != AI1_y || AI4_x != AI2_x || AI4_y != AI2_y || AI3_x != AI4_x || AI3_y != AI4_y)
					AI4_y -= 1; map[fAI4_x][fAI4_y] = ' '; fAI4_x = AI4_x, fAI4_y = AI4_y; map[AI4_x][AI4_y] = '4';
			} break;

			case 7: if (AI4_x > 0 && AI4_x < 8 && AI4_y > 0 && AI4_y < 39) {
				if (AI4_x != p_x || AI4_y != p_y || AI4_x != AI1_x || AI4_y != AI1_y || AI4_x != AI2_x || AI4_y != AI2_y || AI3_x != AI4_x || AI3_y != AI4_y)
					AI4_x += 1; map[fAI4_x][fAI4_y] = ' '; fAI4_x = AI4_x, fAI4_y = AI4_y; map[AI4_x][AI4_y] = '4';
			}break;

			case 8: if (AI4_x > 0 && AI4_x < 8 && AI4_y > 0 && AI4_y < 39) {
				if (AI4_x != p_x || AI4_y != p_y || AI4_x != AI1_x || AI4_y != AI1_y || AI4_x != AI2_x || AI4_y != AI2_y || AI3_x != AI4_x || AI3_y != AI4_y)
					AI4_x -= 1; map[fAI4_x][fAI4_y] = ' '; fAI4_x = AI4_x, fAI4_y = AI4_y; map[AI4_x][AI4_y] = '4';
			}break;
			case 9: break;
			}
			Sleep(500);
		}
	}

	return 0;
}
