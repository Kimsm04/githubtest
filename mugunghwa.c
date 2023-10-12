#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void gotoxy(int row, int col);
void draw(void);

char map[9][40], front[9][40];
char mugunghwa[100] = "¹«±ÃÈ­²ÉÀÌÇÇ¾ú½À´Ï´Ù";
char mugunghwa_f[100];
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
	map[3][1] = '#';
	map[4][1] = '#';
	map[5][1] = '#';

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
		draw();
		printf("\n");
		int speed = 3000;
		for (int i = 0; i < 20; i=i+2) {
			printf("%c%c ", mugunghwa[i], mugunghwa[i + 1]);
			Sleep(speed);
			if (speed > 0) {
				speed -= 300;
				
			}
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
		Sleep(3000);
		system("cls");
	}
	return 0;
}

