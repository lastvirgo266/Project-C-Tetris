#ifndef __GAME_BOARD_H__
#define __GAME_BOARD_H__

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

#define TRUE 1
#define FALSE 0

//게임점수 얻기
int GetScore();

// 게임점수 초기화
void GameScoreReset();

//음악 끄기
void MusicFileOff();

//음악틀기
void MusicFileOpen();

//게임 보드판 그리기
void DrawGameBoard();

//점수판 그리기
void DrawScoreBoard();

//점수추가
void ScorePlus();

//최고점수얻기
int GetBestScore();

#endif