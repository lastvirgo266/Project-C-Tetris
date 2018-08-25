#ifndef __KEY_CUR_CONTORL_H__
#define __KEY_CUR_CONTROL_H__

#include"Point.h"

enum { LEFT, RIGHT, UP, DOWN };

//깜빡거리는 커서 상태 제거
void RemoveCursor();

//현재 커서 위치 정보를 담은 구조체 변수 반환
Point GetCurrentCursorPos();

//커서 위치를 설정
void SetCurrentCursorPos(int x, int y);


//누른 키상태를 반영
int GetCurrentKey();
#endif