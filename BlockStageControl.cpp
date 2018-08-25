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

//������ �����ϱ����� ������ ������ �ʱ�ȭ
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


//��Ͻ�ŸƮ ��ġ�� ����
void InitNewBlockPos(int x, int y){

	if (x < 0 || y < 0) //����Ʈ�� ������ �Լ� ����
		return;

	curPosX = x;
	curPosY = y;

	SetCurrentCursorPos(x, y);

	check = 0;
	
}


//����� �������� �ӵ�����
void SysDelay(){
	if (check == 1)
		return;
	
	//�������� �������� ����� �ٲܼ��ֵ��� �Լ�����
	for (int i = 0; i < 10000; i++)
			ChangeBlock();

}


//����� �׵θ� ������ ����(��� �ٲ𶧸��� �Լ�ȣ��)
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


//��� ���� ����
void ChooseBlock(){
	currentBlockModel = nextBlockMdoel;
	MaxDirect();
	NextBlock();
}


//��� �̸����⿡ ������ ��ϼ���(������ ��µ� ���)
void NextBlock(){
	srand((unsigned int)time(NULL));
	nextBlockMdoel = (rand() % NUM_OF_BLCOK_MODEL) * 4;
}


//���� ��Ϲ�ȣ ���
int GetCurrentBlockIdx(){
	return currentBlockModel;
}


//���� ��Ϲ�ȣ ���
int GetNextBlockIdx(){
	return nextBlockMdoel;
}


//���� ��� �ܼ�â�� ���
void ShowBlock(char blockInfo[][4]){
	int y, x;

	Point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++){
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

			if (blockInfo[y][x] == 1)
				printf("��");
		}
	SetCurrentCursorPos(curPos.x, curPos.y);
}


//���� ��� �ܼ�â���κ��� ����
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


//����� �������°��� �����ϴ� �Լ�
void BlockDown(){
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);//����� �����
	curPosY += 1;// Y ��ǥ�� ��ĭ ������Ų����

	SetCurrentCursorPos(curPosX, curPosY);//Ŀ���� ��ġ�� �ű��
	ShowBlock(blockModel[GetCurrentBlockIdx()]);// ����� ���
}


//����� ����� ��ȯ��Ű�� �Լ�
void ChangeBlock(){
	int tempModel;

	if (_kbhit() == 1){//Ű�� ������ ���� �����Ǹ� �۵�
		DeleteBlock(blockModel[GetCurrentBlockIdx()]);//����� ��µǴ°��� �������� ����� �̸� ����
		
		switch (GetCurrentKey()){
		case LEFT:
			if (LeftBlockRock() || LeftBlockCollision()) //���� �΋H���ų� ��Ͽ� �΋H���� ��������
				break;
			curPosX -= 2;
			break;

		case RIGHT:
			if (RightBlockRock() || RightBlockCollision())//���� �΋H���ų� ��Ͽ� �΋H���� ��������
				break;
			curPosX += 2;
			break;

		case UP:
			tempModel = currentBlockModel; //ȸ���� ���� �������� ����� �켱 ���� ����� ������ �����ص�
			currentBlockModel += 1; //���� ��ȯ

			if (currentBlockModel % 4 == 0) // ���� ������ �����̶�� ó�� �������� �ǵ��ư�
				currentBlockModel -= 4;

			MaxDirect();//��ȯ�� ������ ���� �׵θ� ����Ʈ�� �ٽ� ����

			//��ȯ�� ������ MaxDirect�� ����� ����Ʈ�� �浹�ǰų� ��Ÿ ��ҿ� ���� �浹�ȴٸ� ��ȯ ���
			if (LeftBlockCollision() || RightBlockCollision() || DownBlockCollision() || LeftRotateCollision() || RightRotateCollision())
				currentBlockModel = tempModel;

			MaxDirect();
			break;

		case DOWN:
			check = 1;//SysDelay �� ��ȿȭ
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
				printf("��");
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

	//���������� ���� �����ϸ� �����߰�
	for (int i = 1; i <= comboCheck/2; i++)
		ScorePlus();

}


int GameEndCheck(){
	for (int i = 0; i < 200; i++)
		if (savePoint[i].x != 0 && savePoint[i].y == GBOARD_ORIGIN_Y + 1)
			return TRUE;

	return FALSE;
}