#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void gotoxy(int row, int col);
void mugunghwa_print(void);
void draw(void);

char map[9][40], front[9][40];
char mugunghwa[20] = "무궁화꽃이피었습니다";
char mugunghwa_f[20] = {0};
void gotoxy(int row, int col) {
	COORD pos = { col, row };  
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}
void mugunghwa_print(void) {
	int speed = 2000;
	for (int i = 0; i < 20; i = i + 2) {
		if (mugunghwa_f[i] != mugunghwa[i] || mugunghwa_f[i + 1] != mugunghwa[i + 1]) {
			printf("%c%c ", mugunghwa_f[i], mugunghwa_f[i + 1]);
		}
		Sleep(speed);
		if (i < 10)
			speed = 500;
		else
			speed -= 50;
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w':  break;
			case 's':  break;
			case 'a':  break;
			case 'd':  break;
			case 'q': return 0;
			}
		}
	}
}
void draw(void) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (front[i][j] != map[i][j]) {
				front[i][j] = map[i][j];
			}
			gotoxy(i, j);
			printf("%c", front[i][j]);
		}
	}
}

int main(void) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0 || i == 8 || j == 0 || j == 39) {
				map[i][j] = '*';
			}
			else
			{
				map[i][j] = ' ';
			}
		}
	}
	srand((unsigned int)time(NULL));
	int AI_move1 = rand() % 10 +1;
	int AI_move2 = rand() % 10 + 1;
	int AI_move3 = rand() % 10 + 1;
	int AI_move4 = rand() % 10 + 1;
	map[2][38] = '0';
	map[3][38] = '1';
	map[4][38] = '2';
	map[5][38] = '3';
	map[6][38] = '4';

	while (1) {
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w':  break;
			case 's':  break;
			case 'a':  break;
			case 'd':  break;
			case 'q': return 0;
			}
		}
		map[3][1] = '#';
		map[4][1] = '#';
		map[5][1] = '#';
		draw();
		printf("\n");
		mugunghwa_print();
		map[3][1] = '@';
		map[4][1] = '@';
		map[5][1] = '@';
		draw();
		Sleep(3000);
		system("cls");
	}
	return 0;
}

