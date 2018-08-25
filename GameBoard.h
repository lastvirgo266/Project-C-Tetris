#ifndef __GAME_BOARD_H__
#define __GAME_BOARD_H__

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

#define TRUE 1
#define FALSE 0

//�������� ���
int GetScore();

// �������� �ʱ�ȭ
void GameScoreReset();

//���� ����
void MusicFileOff();

//����Ʋ��
void MusicFileOpen();

//���� ������ �׸���
void DrawGameBoard();

//������ �׸���
void DrawScoreBoard();

//�����߰�
void ScorePlus();

//�ְ��������
int GetBestScore();

#endif