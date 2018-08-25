#include"BlockStageControl.h"
#include"KeyCurControl.h"
#include"GameBoard.h"
#include"GameData.h"
#include"common.h"


#define START_CURPOS_X (5*2)
#define START_CURPOS_Y (0)

void GameStart(){

	GameReset();
	GameScoreReset();

	RemoveCursor();
	MusicFileOpen();
	DrawGameBoard();
	NextBlock();


	while (!GameEndCheck()){
		ChooseBlock();
		DrawScoreBoard();
		InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);


		while (!BlockStack()){
			BlockDown();
			SysDelay();

		}

		BlockStop();
		BlockLineComplete();

	}

	system("cls");
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2);
	printf("THE END!\n\nEnter 키를 누르면 종료합니다.");
	GameDataSave(GetBestScore());
	getchar();
	MusicFileOff();

	return ;

}