#include"Block.h"
#include"Point.h"
#include"KeyCurControl.h"
#include"BlockStageControl.h"
#include"GameBoard.h"
#include"common.h"

static int number = 0;
Point savePoint[200];
Point maxDirect[4];

int check = 0;
static int nextBlockMdoel;
static int currentBlockModel;
static int curPosX, curPosY;

//게임을 시작하기전에 게임의 값들을 초기화
void GameReset(){
	number = 0;

	for (int i = 0; i < 200; i++){
		savePoint[i].x = 0;
		savePoint[i].y = 0;
	}

	for (int i = 0; i < 4; i++){
		maxDirect[i].x = 0;
		maxDirect[i].y = 0;
	}

	check = 0;
	nextBlockMdoel = 0;
	currentBlockModel = 0;
	curPosX = 0;
	curPosX = 0;
}


//블록스타트 위치를 지정
void InitNewBlockPos(int x, int y){

	if (x < 0 || y < 0) //포인트가 음수면 함수 종료
		return;

	curPosX = x;
	curPosY = y;

	SetCurrentCursorPos(x, y);

	check = 0;
	
}


//블록이 떨어질때 속도조절
void SysDelay(){
	if (check == 1)
		return;
	
	//떨어지는 순간에도 블록을 바꿀수있도록 함수구현
	for (int i = 0; i < 10000; i++)
			ChangeBlock();

}


//블록의 테두리 지점을 저장(블록 바뀔때마다 함수호출)
void MaxDirect(){

	int y, x;
	int i = 0;



	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (blockModel[currentBlockModel][y][x] == 1){
				maxDirect[i].x = x * 2;
				maxDirect[i].y = y;
				i++;
			}

}


//블록 랜덤 선택
void ChooseBlock(){
	currentBlockModel = nextBlockMdoel;
	MaxDirect();
	NextBlock();
}


//블록 미리보기에 띄어놓을 블록선택(다음에 출력될 블록)
void NextBlock(){
	srand((unsigned int)time(NULL));
	nextBlockMdoel = (rand() % NUM_OF_BLCOK_MODEL) * 4;
}


//현재 블록번호 얻기
int GetCurrentBlockIdx(){
	return currentBlockModel;
}


//다음 블록번호 얻기
int GetNextBlockIdx(){
	return nextBlockMdoel;
}


//현재 블록 콘솔창에 출력
void ShowBlock(char blockInfo[][4]){
	int y, x;

	Point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

			if (blockInfo[y][x] == 1)
				printf("■");
		}
	SetCurrentCursorPos(curPos.x, curPos.y);
}


//현재 블록 콘솔창으로부터 지움
void DeleteBlock(char blockInfo[][4]){
	int y, x;

	Point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

			if (blockInfo[y][x] == 1)
				printf(" ");
		}

	SetCurrentCursorPos(curPos.x, curPos.y);
}


//블록이 떨어지는것을 구현하는 함수
void BlockDown(){
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);//블록을 지우고
	curPosY += 1;// Y 좌표를 한칸 증가시킨다음

	SetCurrentCursorPos(curPosX, curPosY);//커서의 위치를 옮기고
	ShowBlock(blockModel[GetCurrentBlockIdx()]);// 블록을 출력
}


//블록의 모양을 변환시키는 함수
void ChangeBlock(){
	int tempModel;

	if (_kbhit() == 1){//키가 눌리는 것이 감지되면 작동
		DeleteBlock(blockModel[GetCurrentBlockIdx()]);//허상이 출력되는것을 막기위해 블록을 미리 지움
		
		switch (GetCurrentKey()){
		case LEFT:
			if (LeftBlockRock() || LeftBlockCollision()) //벽에 부딫히거나 블록에 부딫히면 못움직임
				break;
			curPosX -= 2;
			break;

		case RIGHT:
			if (RightBlockRock() || RightBlockCollision())//벽에 부딫히거나 블록에 부딫히면 못움직임
				break;
			curPosX += 2;
			break;

		case UP:
			tempModel = currentBlockModel; //회전이 되지 않을것을 대비해 우선 현재 블록을 변수에 저장해둠
			currentBlockModel += 1; //모형 변환

			if (currentBlockModel % 4 == 0) // 만약 마지막 모형이라면 처음 모형으로 되돌아감
				currentBlockModel -= 4;

			MaxDirect();//변환된 모형에 의해 테두리 포인트를 다시 지정

			//변환된 모형이 MaxDirect에 저장된 포인트와 충돌되거나 기타 요소에 의해 충돌된다면 변환 취소
			if (LeftBlockCollision() || RightBlockCollision() || DownBlockCollision() || LeftRotateCollision() || RightRotateCollision())
				currentBlockModel = tempModel;

			MaxDirect();
			break;

		case DOWN:
			check = 1;//SysDelay 값 무효화
			break;
		}

		ShowBlock(blockModel[GetCurrentBlockIdx()]);

	}
}


int LeftBlockRock(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			if (blockModel[currentBlockModel][y][x] == 1)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX - 2 == GBOARD_ORIGIN_X)
							return TRUE;
					

		}

	return FALSE;
}


int RightBlockRock(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			if (blockModel[currentBlockModel][y][x] == 1)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX == GBOARD_ORIGIN_X + GBOARD_WIDTH * 2)
							return TRUE;	

		}

	return FALSE;

}


int LeftRotateCollision(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (blockModel[currentBlockModel][y][x] == 1)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX == GBOARD_ORIGIN_X)
							return TRUE;


		

	return FALSE;
}


int RightRotateCollision(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			if (blockModel[currentBlockModel][y][x] == 1)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX == GBOARD_ORIGIN_X + (GBOARD_WIDTH +1)*2)
							return TRUE;

		}

	return FALSE;

}


int LeftBlockCollision(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			if (blockModel[currentBlockModel][y][x] == 1)
				for (int i = 0; i < 200; i++)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX - 2 == savePoint[i].x && maxDirect[j].y + curPosY == savePoint[i].y)
							return TRUE;
					

		}

	return FALSE;
}


int RightBlockCollision(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			if (blockModel[currentBlockModel][y][x] == 1)
				for (int i = 0; i < 200; i++)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX + 2 == savePoint[i].x && maxDirect[j].y + curPosY == savePoint[i].y)
							return TRUE;


		}

	return FALSE;
}


int DownBlockCollision(){
	int x, y;

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			if (blockModel[currentBlockModel][y][x] == 1){
				for (int i = 0; i < 200; i++)
					for (int j = 0; j < 4; j++)
						if (maxDirect[j].x + curPosX == savePoint[i].x && maxDirect[j].y + curPosY + 1 == savePoint[i].y){
							return TRUE;
						}

				if (curPosY + y +1 == GBOARD_HEIGHT + GBOARD_ORIGIN_Y)
					return TRUE;


			}

		}

	return FALSE;
}


void SavePoint(Point maxDirect){
	for (int i = 0; i < 200; i++)
		if (savePoint[i].x == 0){
			savePoint[i].x = maxDirect.x + curPosX;
			savePoint[i].y = maxDirect.y + curPosY;
			return;
		}
}


int BlockStack(){
	return DownBlockCollision();
}


void BlockStop(){
	check = 0;
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);

	for (int i = 0; i < 4; i++)
		SavePoint(maxDirect[i]);

}


void DeleteLine(int line){
	Point curPos;

		for (int i = 0; i < 200; i++){
			if (savePoint[i].y == line){
				curPos.x = savePoint[i].x;
				curPos.y = savePoint[i].y;

				SetCurrentCursorPos(curPos.x, curPos.y);
				printf(" ");

				savePoint[i].x = 0;
				savePoint[i].y = 0;
			}
				
		}

		Sleep(200);

		for (int i = 0; i < 200; i++){
			if (savePoint[i].x != 0){
				curPos.x = savePoint[i].x;
				curPos.y = savePoint[i].y;
				SetCurrentCursorPos(curPos.x, curPos.y);
				printf(" ");
			}
		}

		for (int i = 0; i < 200; i++)
			if (savePoint[i].x != 0 && savePoint[i].y < line)
				savePoint[i].y += 1;

		for (int i = 0; i < 200; i++){
			if (savePoint[i].x != 0){
				curPos.x = savePoint[i].x;
				curPos.y = savePoint[i].y;
				SetCurrentCursorPos(curPos.x, curPos.y);
				printf("■");
			}
		}

	
}


void BlockLineComplete(){
	int comboCheck = 0;
	int check = 0;
	int height;

	for(height = 0; height <= GBOARD_ORIGIN_Y + GBOARD_HEIGHT; height++){
		
		for (int i = 0; i < 200; i++)
			if (savePoint[i].x != 0 && savePoint[i].y == height)
				check += 1;
		

		if (check == 10){
			comboCheck += 1;
			DeleteLine(height);
			ScorePlus();
		}
		
		check = 0;


	}

	//연속적으로 줄을 제거하면 점수추가
	for (int i = 1; i <= comboCheck/2; i++)
		ScorePlus();

}


int GameEndCheck(){
	for (int i = 0; i < 200; i++)
		if (savePoint[i].x != 0 && savePoint[i].y == GBOARD_ORIGIN_Y + 1)
			return TRUE;

	return FALSE;
}