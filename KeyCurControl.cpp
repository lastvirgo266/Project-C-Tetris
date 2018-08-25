#include"common.h"
#include"KeyCurControl.h"

void RemoveCursor(){
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}


Point GetCurrentCursorPos(){
	Point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}


void SetCurrentCursorPos(int x, int y){
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int GetCurrentKey(){
	if(_getch() == 224)
	switch (_getch()){
	case 75:
		return LEFT;
	case 72:
		return UP;
	case 77:
		return RIGHT;
	case 80:
		return DOWN;
	}
}