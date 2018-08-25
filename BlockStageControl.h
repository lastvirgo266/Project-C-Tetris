#ifndef __BLOCK_STAGE_CONTROL_H__
#define __BLOCK_STAGE_CONTROL_H__

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

#define TRUE 1
#define FALSE 0

//���� ����
void GameReset();

//����� ������ġ ����
void InitNewBlockPos(int x, int y);

//�ý��� �����̰�
void SysDelay();

//��� ���� ����
void ChooseBlock();

//���� ��� ����
void NextBlock();

//��� ���
int GetCurrentBlockIdx();

//������� ���
int GetNextBlockIdx();

//������
void ShowBlock(char blockInfo[][4]);

//��µǾ� �ִ� ��� ����
void DeleteBlock(char blockInfo[][4]);

//��� ��ĭ ������
void BlockDown();

//��� �ٲٱ�
void ChangeBlock();

//����� �������� ���ϴ� ��Ȳ���� Ȯ��
int LeftBlockRock();

//����� �������� ���ϴ� ��Ȳ���� Ȯ��
int RightBlockRock();


//����� �������� ���ϴ� ��Ȳ���� Ȯ��
int LeftRotateCollision();

//����� �������� ���ϴ� ��Ȳ���� Ȯ��
int RightRotateCollision();


//��� ���� �浹 �˻�
int LeftBlockCollision();

//��� ������ �浹 �˻�
int RightBlockCollision();

//��� �Ʒ��� �浶 �˻�
int DownBlockCollision();

//����� ���ϼ��ִ��� �˻�
int BlockStack();

//��� ����
void BlockStop();

//1���� �ϼ��Ǹ� �������� ������
void BlockLineComplete();

//���ӿ��� üũ
int GameEndCheck();
#endif