#include<iostream>
#include "windows.h"
#include<conio.h> // отслеживает нажатие пользователя не закрывая терминал
using namespace std;

bool SETUP_HIT_BOUNDS = false;
int SETUP_DELAY = 100; // задержка отрисовки в милисекундах

bool gameover;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // перечисления - это тип который может содержать значения указанные программистом.
eDirection dir;

void Setup() {
	gameover = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");// отчистка экрана консоли
	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) { // по y
		for (int j = 0; j < width; j++) { // по x
			if (j == 0 || j == (width - 1)) 
				cout << "#";
			if (i == y && j == x) 
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "0";
					}
				}
				if (print == false) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) { // узнает, нажата ли клавиша
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (!SETUP_HIT_BOUNDS) {

		if (x >= width - 1) {
			x = 0;
		}
		else if (x < 0) {
			x = width - 2;
		}
		if (y >= height) {
			y = 0;
		}
		else if (y < 0) {
			y = height - 2;
		}
	}
	else if (x >= width - 1 || x < 0 || y >= height || y < 0){gameover = true;}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameover = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

int main() {
	Setup();
	while (!gameover) {
		Draw();
		Input();
		Logic();
		Sleep(SETUP_DELAY);
	}
	//#define WINPAUSE system("pause")
	return 0;
}
