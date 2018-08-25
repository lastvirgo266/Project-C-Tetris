#include"GameBoard.h"
#include"KeyCurControl.h"
#include"BlockStageControl.h"
#include"GameData.h"
#include"common.h"

#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") //MCI

extern char blockModel[][4][4];
int bestScore;
int score = 0;

int GetScore(){
	return score;
}


void GameScoreReset(){
	score = 0;
	bestScore = GameDataLoad();
}


void MusicFileOff(){
	mciSendString("stop DreamSolister.mp3", NULL, 0, NULL);//정지
}


void MusicFileOpen(){

	mciSendString("play DreamSolister.mp3 repeat", NULL, 0, NULL);//재생반복
	
}


void DrawGameBoard(){
	int x, y;

	for (y = 0; y <= GBOARD_HEIGHT; y++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("└");
		else
			printf("│");
	}

	for (y = 0; y <= GBOARD_HEIGHT; y++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("┘");
		else
			printf("│");
	}

	for (x = 1; x <GBOARD_WIDTH + 1; x++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("─");
	}

}


void DrawScoreBoard(){
	int x, y;

	//다음블록 표시
	for (x = 0; x <= 6; x++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH+1)*2 + 4 + x*2, GBOARD_ORIGIN_Y + 4);

		if (x == 0)
			printf("┌");
		else if (x == 6)
			printf("┐");

		else
			printf("─");
	}

	for (y = 0; y <= 4; y++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2 + 4, GBOARD_ORIGIN_Y+ 5 + y);
		printf("│");
	}

	for (y = 0; y <= 4; y++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2 + 16, GBOARD_ORIGIN_Y +5 + y);
		printf("│");
	}

	for (x = 0; x <=6; x++){
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2 + 4 + x * 2, GBOARD_ORIGIN_Y + 9);
		if (x == 0)
			printf("└");
		else if (x == 6)
			printf("┘");

		else
			printf("─");
	}

	
	SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2 + 8, GBOARD_ORIGIN_Y + 5);
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	ShowBlock(blockModel[GetNextBlockIdx()]);


	if(score >= bestScore)
		bestScore = score;

	//점수표시
	SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2 + 4, GBOARD_ORIGIN_Y + 11);
	printf("최고점수 : %d", bestScore);
	SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2 + 4, GBOARD_ORIGIN_Y + 12);
	printf("현재점수 : %d", score);
	
}


int GetBestScore(){
	if (bestScore >= score)
		return bestScore;
	else
		return score;
}


void ScorePlus(){
	score += 100;
	/*파일깨짐으로 인한 일시 주석*/
	//2018.03.20.13.52 녹화시작 녹화자: 정승진
	//mciSendString("play Mayuri.mp3", NULL, 0, NULL);//재생
}