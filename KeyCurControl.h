#ifndef __KEY_CUR_CONTORL_H__
#define __KEY_CUR_CONTROL_H__

#include"Point.h"

enum { LEFT, RIGHT, UP, DOWN };

//�����Ÿ��� Ŀ�� ���� ����
void RemoveCursor();

//���� Ŀ�� ��ġ ������ ���� ����ü ���� ��ȯ
Point GetCurrentCursorPos();

//Ŀ�� ��ġ�� ����
void SetCurrentCursorPos(int x, int y);


//���� Ű���¸� �ݿ�
int GetCurrentKey();
#endif